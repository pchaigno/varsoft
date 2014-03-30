package generator;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import fr.opensagres.xdocreport.converter.ConverterTypeTo;
import fr.opensagres.xdocreport.converter.ConverterTypeVia;
import fr.opensagres.xdocreport.converter.Options;
import fr.opensagres.xdocreport.converter.XDocConverterException;
import fr.opensagres.xdocreport.core.XDocReportException;
import fr.opensagres.xdocreport.document.IXDocReport;
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

		File template = null;
		String outputPath = null;

		// check the arguments "Usage: java DocXGenerator templateFilePath outputFilePath"
		if (args.length>=2 && args.length < 3) {
			template = new File(args[0]);
			if (!template.exists())
			{
				System.out.println("Error: " +args[0]+ "does not exist.");
				System.exit(GeneratorError.TEMPLATE_NOT_FOUND.getCode());
			}
			outputPath = args[1];
		} else {
			System.out.println("Usage: java DocXGenerator templateFilePath outputFilePath");
			System.exit(GeneratorError.PARAMETER_ERROR.getCode());
		}
		
		GeneratorError result = GeneratorError.NO_ERROR;
		try
		{ 
			// initialize the input with the standard input
			InputStreamReader reader=new InputStreamReader(System.in); 
			BufferedReader input=new BufferedReader(reader); 
			
			result = generate(input, template, outputPath);

		} catch (IOException e) {
			e.printStackTrace();
			System.exit(GeneratorError.IO_ERROR.getCode());
		}
		System.exit(result.getCode());
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
	 * Generates the DOCX and PDF reports with the data in the context.
	 * @param input The input stream.
	 * @param template The template DOCX file.
	 * @param outputPath The path to the file which has to be written (without the extension).
	 * @return An error code or 0 if all went well.
	 * @throws XDocReportException
	 * @throws IOException
	 * @throws ParseException
	 */
	public static GeneratorError generate(BufferedReader input, File template, String outputPath) throws IOException {
		// initialize of the JSON Parser with the input
		JSONParser parser = new JSONParser();
		JSONObject json = null;
		try {
			json = (JSONObject) parser.parse(input);
		} catch(ParseException e) {
			e.printStackTrace();
			return GeneratorError.JSON_ERROR;
		}

		// Initialize the template file and create the report object
		InputStream in = new FileInputStream(template);
		try {
			report = XDocReportRegistry.getRegistry().loadReport(in, TemplateEngineKind.Velocity);
		} catch (XDocReportException e) {
			e.printStackTrace();
			return GeneratorError.TEMPLATE_ERROR;
		}

		// create the FieldsMetadata
		metadata = new FieldsMetadata();

		// create the report context
		try {
			contextMap = report.createContext();
		} catch (XDocReportException e) {
			e.printStackTrace();
			return GeneratorError.CONTEXT_ERROR;
		}

		//add the data from the JSON to the report context
		computeText((JSONObject) json.get("text"));
		computeImages((JSONObject) json.get("images"));
		computeList((JSONObject) json.get("list"));

		// link the FieldsMetaData to the report
		report.setFieldsMetadata(metadata);

		// generate the output file
		GeneratorError errorCode = generateDocx(outputPath);
		if(errorCode != GeneratorError.NO_ERROR) {
			return errorCode;
		}
		errorCode = generatePdf(outputPath);
		if(errorCode != GeneratorError.NO_ERROR) {
			return errorCode;
		}
		
		return GeneratorError.NO_ERROR;
	}

	/**
	 * Generate the DOCX report with the data in the context.
	 * @param outputFile The path to the file which has to be written (without the extension).
	 * @reutrn An error code or 0 if all went well.
	 * @throws XDocReportException
	 * @throws IOException
	 */
	private static GeneratorError generateDocx(String outputPath) throws IOException {
		File outputFile = new File(outputPath+".docx");
		OutputStream out = new FileOutputStream(outputFile);
		try {
			report.process(contextMap, out);
		} catch (XDocReportException e) {
			e.printStackTrace();
			return GeneratorError.DOCX_GENERATION_ERROR;
		}
		return GeneratorError.NO_ERROR;
	}

	/**
	 * Generate the PDF report with the data in the context.
	 * @param outputFile The path to the file which has to be written (without the extension).
	 * @return An error code or 0 if all went well.
	 * @throws IOException
	 * @throws XDocReportException
	 */
	private static GeneratorError generatePdf(String outputPath) throws IOException {
		File outputFile = new File(outputPath+".pdf");
		OutputStream out = new FileOutputStream(outputFile);
		Options options = Options.getTo(ConverterTypeTo.PDF).via(ConverterTypeVia.XWPF);
		try {
			report.convert(contextMap, options, out);
		} catch (XDocConverterException e) {
			e.printStackTrace();
			return GeneratorError.PDF_CONVERTION_ERROR;
		} catch (XDocReportException e) {
			e.printStackTrace();
			return GeneratorError.PDF_GENERATION_ERROR;
		}
		return GeneratorError.NO_ERROR;
	}
}
