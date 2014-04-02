package generator;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.apache.commons.io.IOUtils;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

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
				System.out.println("Error: "+args[0]+" does not exist.");
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
			String jsonText = IOUtils.toString(System.in, "UTF-8");
			
			result = generate(jsonText, template, outputPath);

		} catch (IOException e) {
			System.err.println("Error: "+e.getMessage());
			System.exit(GeneratorError.IO_ERROR.getCode());
		}
		System.exit(result.getCode());
	}

	/**
	 * Add the text data from the JSON to the report's context
	 * @param textObject The JSON text object
	 */
	private static void computeText(JSONObject textObject) {
		// iterate on all the simple text
		Iterator<?> it = textObject.keys();
		while(it.hasNext()) {
			String key = it.next().toString();
			// add the text to the report's context
			contextMap.put(key, textObject.getString(key));
		}
	}

	/**
	 * Initialize the FieldsMetaData for all images,
	 * create them with the paths from the JSON and add it to the report's context.
	 * @param imagesObject The JSON images object.
	 */
	private static void computeImages(JSONObject imagesObject) {
		// iterate on all images
		Iterator<?> it = imagesObject.keys();
		while(it.hasNext()) {
			String key = it.next().toString();
			// set the FieldsMetaData
			metadata.addFieldAsImage(key);
			// create the image
			IImageProvider img = new FileImageProvider(new File(imagesObject.getString(key)));
			img.setUseImageSize(true);
			// add it to the report's context
			contextMap.put(key, img);
		}
	}

	/**
	 * Initialize the FieldsMetaData with the key of the JSON data
	 * and add the list to the report's context.
	 * @param listObject
	 */
	private static void computeList(JSONObject listObject) {
		// iterate on all the list
		Iterator<?> it = listObject.keys();
		while(it.hasNext()) {
			// Get the key and the array
			String key = it.next().toString();
			JSONArray jsonArray = listObject.getJSONArray(key);

			//get the FieldsMetaData, searching for all different keys on the Map
			Set<String> fields = new HashSet<String>();
			for(int i=0; i<jsonArray.length(); i++) {
				JSONObject map = jsonArray.getJSONObject(i);
				Iterator<?> itMap = map.keys();
				while(itMap.hasNext()) {
					fields.add(key+"."+itMap.next().toString());
				}
			}
			
			// set the FieldsMetaData
			for(String field: fields) {
				metadata.addFieldAsList(field);
			}
			
			// add the array to the report's context
			ArrayList<Map<String, String>> array = new ArrayList<Map<String, String>>();
			for(int i=0; i<jsonArray.length(); i++) {
			    JSONObject jsonMap = jsonArray.getJSONObject(i);
			    Map<String, String> map = new HashMap<String, String>();
			    Iterator<?> itMap = jsonMap.keys();
			    while(itMap.hasNext()) {
			        String jsonKey = itMap.next().toString();
			        map.put(jsonKey, jsonMap.getString(jsonKey));
			    }
			    array.add(map);
			}
			contextMap.put(key, array);
		} 
	}
	
	/**
	 * Generates the DOCX and PDF reports with the data in the context.
	 * @param jsonText The JSON text.
	 * @param template The template DOCX file.
	 * @param outputPath The path to the file which has to be written (without the extension).
	 * @return An error code or 0 if all went well.
	 * @throws XDocReportException
	 * @throws IOException
	 * @throws ParseException
	 */
	public static GeneratorError generate(String jsonText, File template, String outputPath) throws IOException {
		// initialize of the JSON Parser with the input
		JSONObject json;
		try {
			json = new JSONObject(jsonText);
		} catch(JSONException e) {
			System.err.println("Error while parsing the JSON file:");
			System.err.println(e.getMessage());
			System.err.println();
			return GeneratorError.JSON_ERROR;
		}

		// Initialize the template file and create the report object
		InputStream in = new FileInputStream(template);
		try {
			report = XDocReportRegistry.getRegistry().loadReport(in, TemplateEngineKind.Velocity);
		} catch (XDocReportException e) {
			System.err.println("Error with the template file:");
			System.err.println(e.getMessage());
			return GeneratorError.TEMPLATE_ERROR;
		}

		// create the FieldsMetadata
		metadata = new FieldsMetadata();

		// create the report context
		try {
			contextMap = report.createContext();
		} catch (XDocReportException e) {
			System.err.println("Error while creating the context:");
			System.err.println(e.getMessage());
			return GeneratorError.CONTEXT_ERROR;
		}

		//add the data from the JSON to the report context
		JSONObject textObject = null;
		try {
			textObject = json.getJSONObject("text");
		} catch(JSONException e) {
			System.err.println("Text element missing in JSON.");
			return GeneratorError.TEXT_MISSING;
		}
		computeText(textObject);
		JSONObject imagesObject = null;
		try {
			imagesObject = json.getJSONObject("images");
		} catch(JSONException e) {
			System.err.println("Images element missing in JSON.");
			return GeneratorError.IMAGES_MISSING;
		}
		computeImages(imagesObject);
		JSONObject listObject = null;
		try {
			listObject = json.getJSONObject("list");
		} catch(JSONException e) {
			System.err.println("List element missing in JSON.");
			return GeneratorError.LIST_MISSING;
		}
		computeList(listObject);

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
			System.err.println("Error while generating the DOCX file:");
			System.err.println(e.getMessage());
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
			System.err.println("Error while converting the PDF:");
			System.err.println(e.getMessage());
			return GeneratorError.PDF_CONVERTION_ERROR;
		} catch (XDocReportException e) {
			System.err.println("Error while generating the PDF:");
			System.err.println(e.getMessage());
			return GeneratorError.PDF_GENERATION_ERROR;
		}
		return GeneratorError.NO_ERROR;
	}
}
