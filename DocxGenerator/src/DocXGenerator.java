import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.poi.xwpf.converter.pdf.PdfConverter;
import org.apache.poi.xwpf.converter.pdf.PdfOptions;
import org.apache.poi.xwpf.usermodel.XWPFDocument;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import fr.opensagres.xdocreport.converter.ConverterTypeTo;
import fr.opensagres.xdocreport.converter.ConverterTypeVia;
import fr.opensagres.xdocreport.converter.Options;
import fr.opensagres.xdocreport.core.XDocReportException;
import fr.opensagres.xdocreport.document.IXDocReport;
import fr.opensagres.xdocreport.document.XDocReport;
import fr.opensagres.xdocreport.document.images.ClassPathImageProvider;
import fr.opensagres.xdocreport.document.images.FileImageProvider;
import fr.opensagres.xdocreport.document.images.IImageProvider;
import fr.opensagres.xdocreport.document.registry.XDocReportRegistry;
import fr.opensagres.xdocreport.template.IContext;
import fr.opensagres.xdocreport.template.TemplateEngineKind;
import fr.opensagres.xdocreport.template.formatter.FieldsMetadata;

public class DocXGenerator {

	private static IContext contextMap;
	private static FieldsMetadata metadata;
	private static IXDocReport report;

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		File template, output;
		boolean pdf = false;

		// check the arguments "Usage: java DocXGenerator templateFilePath outputFilePath [-pdf]"
		if (args.length>=2 && args.length < 4) {
			template = new File(args[0]);
			if (!template.exists())
			{
				System.out.println("Error: " +args[0]+ "does not exist.");
				return;
			}
			output = new File(args[1]);
			pdf = (args.length==3) && args[2].equals("-pdf");
		} else {
			System.out.println("Usage: java DocXGenerator templateFilePath outputFilePath [-pdf]");
			return;
		}
		try
		{ 
			// initialize the input with the standard input
			InputStreamReader reader=new InputStreamReader(System.in); 
			BufferedReader input=new BufferedReader(reader); 
			
			// initialize of the JSON Parser with the input
			JSONParser parser = new JSONParser();
			JSONObject json = (JSONObject) parser.parse(input);

			// Initialize the template file and create the report object
			InputStream in = new FileInputStream(template);
			report = XDocReportRegistry.getRegistry().loadReport(in, TemplateEngineKind.Velocity);

			// create the FieldsMetadata
			metadata = new FieldsMetadata();

			// create the report context
			contextMap = report.createContext();

			//add the data from the JSON to the report context
			computeText((JSONObject) json.get("text"));
			computeImages((JSONObject) json.get("images"));
			computeList((JSONObject) json.get("list"));

			// link the FieldsMetaData to the report
			report.setFieldsMetadata(metadata);

			// generate the output file
			if (pdf)
				generatePdf(output);
			else
				generateDocx(output);

		} catch (IOException e) {
			e.printStackTrace();
		} catch (XDocReportException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Add the text data from the JSON to the report's context
	 * @param textObject
	 */
	private static void computeText(JSONObject textObject)
	{
		// iterate on all the simple text
		Iterator<?> iter = textObject.entrySet().iterator();
		while(iter.hasNext()){
			Map.Entry entry = (Map.Entry)iter.next();
			// add the text to the report's context
			contextMap.put(entry.getKey().toString(), entry.getValue().toString());
		}  
	}

	/**
	 * Initialize the FieldsMetaData for all images,
	 * create them with the paths from the JSON and add it to the report's context.
	 * @param imagesObject
	 */
	private static void computeImages(JSONObject imagesObject)
	{
		// iterate on all images
		Iterator<?> iter = imagesObject.entrySet().iterator();
		while(iter.hasNext()){
			Map.Entry entry = (Map.Entry)iter.next();
			// set the FieldsMetaData
			metadata.addFieldAsImage(entry.getKey().toString());
			// create the image
			IImageProvider img = new FileImageProvider(new File(entry.getValue().toString()));
			img.setUseImageSize(true);
			// add it to the report's context
			contextMap.put(entry.getKey().toString(), img);
		}  
	}

	/**
	 * Initialize the FieldsMetaData with the key of the JSON data
	 * and add the list to the report's context.
	 * @param listObject
	 */
	private static void computeList(JSONObject listObject)
	{
		// iterate on all the list
		Iterator<?> iter = listObject.entrySet().iterator();
		while(iter.hasNext()){
			// Get the key and the array
			Map.Entry entry = (Map.Entry)iter.next();
			String key = entry.getKey().toString();
			JSONArray array = (JSONArray) entry.getValue();

			//get the FieldsMetaData, searching for all different keys on the Map
			HashSet<String> metaData = new HashSet<String>();
			Iterator<?> iterArray = array.iterator();
			while(iterArray.hasNext()){
				JSONObject map = (JSONObject) iterArray.next();
				Iterator<?> iterMap = map.entrySet().iterator();
				while(iterMap.hasNext()){
					Map.Entry entryMap = (Map.Entry)iterMap.next();	
					metaData.add(entryMap.getKey().toString());
				}
			}
			// set the FieldsMetaData
			Iterator<?> iterMetaData = metaData.iterator();
			while(iterMetaData.hasNext()){
				metadata.addFieldAsList(key+"."+iterMetaData.next().toString());				
			}
			
			// add the array to the report's context
			contextMap.put(key, array);
		} 
	}

	/**
	 * Generate the DOCX report with the data in the context.
	 * @param outputFile The file which has to be written
	 * @throws XDocReportException
	 * @throws IOException
	 */
	private static void generateDocx(File outputFile) throws XDocReportException, IOException
	{
		OutputStream out = new FileOutputStream(outputFile);
		report.process(contextMap, out);
	}

	/**
	 * Generate the PDF report with the data in the context.
	 * @param outputFile The file which has to be written
	 * @throws IOException
	 * @throws XDocReportException
	 */
	private static void generatePdf(File outputFile) throws IOException, XDocReportException
	{
		OutputStream out = new FileOutputStream(outputFile);
		Options options = Options.getTo(ConverterTypeTo.PDF).via(ConverterTypeVia.XWPF);
		report.convert(contextMap, options, out);
	}
}
