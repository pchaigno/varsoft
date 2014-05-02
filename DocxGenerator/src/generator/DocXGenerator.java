/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.
 *
 * DocXGenerator is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * DocXGenerator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
package generator;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;

import org.apache.commons.io.IOUtils;
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
	 * Entry point for the program.
	 * Usage: java DocXGenerator templateFilePath outputFilePath.
	 * Takes the variables as JSON on the standard input.
	 * @param args Arguments from the command line.
	 */
	public static void main(String[] args) {
		File template = null;
		String outputPath = null;

		// Checks the arguments "Usage: java DocXGenerator templateFilePath outputFilePath"
		if (args.length>=2 && args.length<3) {
			template = new File(args[0]);
			if (!template.exists())	{
				System.out.println("Error: "+args[0]+" does not exist.");
				System.exit(GeneratorError.TEMPLATE_NOT_FOUND.getCode());
			}
			outputPath = args[1];
		} else {
			System.out.println("Usage: java DocXGenerator templateFilePath outputFilePath");
			System.exit(GeneratorError.PARAMETER_ERROR.getCode());
		}
		
		GeneratorError result = GeneratorError.NO_ERROR;
		try {
			// Initializes the input with the standard input
			String jsonText = IOUtils.toString(System.in, "UTF-8");
			result = generate(jsonText, template, outputPath);
		} catch (IOException e) {
			System.err.println("Error: "+e.getMessage());
			System.exit(GeneratorError.IO_ERROR.getCode());
		}
		System.exit(result.getCode());
	}

	/**
	 * Adds the text data from the JSON to the report's context.
	 * @param textObject The JSON text object.
	 */
	@SuppressWarnings("rawtypes")
	private static void computeText(JSONObject textObject) {
		// iterate on all the simple text
		Iterator<?> iter = textObject.entrySet().iterator();
		while (iter.hasNext()) {
			Map.Entry entry = (Map.Entry)iter.next();
			// add the text to the report's context
			contextMap.put(entry.getKey().toString(), entry.getValue().toString());
		}
	}

	/**
	 * Initializes the FieldsMetaData for all images,
	 * creates them with the paths from the JSON and adds it to the report's context.
	 * @param imagesObject The JSON images object.
	 */
	@SuppressWarnings("rawtypes")
	private static void computeImages(JSONObject imagesObject) {
		// iterate on all images
		Iterator<?> iter = imagesObject.entrySet().iterator();
		while (iter.hasNext()) {
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
	 * Initializes the FieldsMetaData with the key of the JSON data
	 * and adds the list to the report's context.
	 * @param listObject The JSON list object.
	 */
	@SuppressWarnings("rawtypes")
	private static void computeList(JSONObject listObject) {
		// Iterates on all the list:
		Iterator<?> iter = listObject.entrySet().iterator();
		while (iter.hasNext()) {
			// Gets the key and the array:
			Map.Entry entry = (Map.Entry)iter.next();
			String key = entry.getKey().toString();
			JSONArray array = (JSONArray) entry.getValue();
	
			// Gets the FieldsMetaData, searching for all different keys on the Map:
			HashSet<String> metaData = new HashSet<String>();
			Iterator<?> iterArray = array.iterator();
			while (iterArray.hasNext()) {
				JSONObject map = (JSONObject) iterArray.next();
				Iterator<?> iterMap = map.entrySet().iterator();
				while (iterMap.hasNext()) {
					Map.Entry entryMap = (Map.Entry)iterMap.next();	
					metaData.add(entryMap.getKey().toString());
				}
			}
			
			// Sets the FieldsMetaData:
			Iterator<?> iterMetaData = metaData.iterator();
			while (iterMetaData.hasNext()) {
				metadata.addFieldAsList(key+"."+iterMetaData.next().toString());	
			}
	
			// Adds the array to the report's context.
			// array can be directly passed as a value for contextMap because it inherits from ArrayList.
			contextMap.put(key, array);
		} 
	}
	
	/**
	 * Generates the DOCX and PDF reports with the data in the context.
	 * @param jsonText The JSON text.
	 * @param template The template DOCX file.
	 * @param outputPath The path to the file which has to be written (without the extension).
	 * @return An error code or 0 if all went well.
	 * @throws IOException If the template or output file can't be opened or written.
	 */
	public static GeneratorError generate(String jsonText, File template, String outputPath) throws IOException {
		// Parses the JSON text:
		JSONObject json;
		try {
			JSONParser parser = new JSONParser();
			json = (JSONObject)parser.parse(jsonText);
		} catch(ParseException e) {
			System.err.println("Error while parsing the JSON file:");
			System.err.println(e.toString());
			return GeneratorError.JSON_ERROR;
		}

		// Initializes the template file and creates the report object:
		InputStream in = new FileInputStream(template);
		try {
			report = XDocReportRegistry.getRegistry().loadReport(in, TemplateEngineKind.Velocity);
		} catch (XDocReportException e) {
			System.err.println("Error with the template file:");
			System.err.println(e.getMessage());
			return GeneratorError.TEMPLATE_ERROR;
		}

		// Creates the FieldsMetadata.
		metadata = new FieldsMetadata();

		// Creates the report context:
		try {
			contextMap = report.createContext();
		} catch (XDocReportException e) {
			System.err.println("Error while creating the context:");
			System.err.println(e.getMessage());
			return GeneratorError.CONTEXT_ERROR;
		}

		// Adds the data from the JSON to the report context:
		JSONObject textObject = (JSONObject)json.get("text");
		if(textObject == null) {
			System.err.println("Text element missing in JSON.");
			return GeneratorError.TEXT_MISSING;
		}
		computeText(textObject);
		JSONObject imagesObject = (JSONObject)json.get("images");
		if(imagesObject == null) {
			System.err.println("Images element missing in JSON.");
			return GeneratorError.IMAGES_MISSING;
		}
		computeImages(imagesObject);
		JSONObject listObject = (JSONObject)json.get("list");
		if(listObject == null) {
			System.err.println("List element missing in JSON.");
			return GeneratorError.LIST_MISSING;
		}
		computeList(listObject);

		// Links the FieldsMetaData to the report.
		report.setFieldsMetadata(metadata);

		// Generates the output file:
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
	 * Generates the DOCX report with the data in the context.
	 * @param outputFile The path to the file which has to be written (without the extension).
	 * @return A generator error code or NO_ERROR if all went well.
	 * @see ErrorGenerator
	 * @throws IOException If the ouput file can't be opened or if it can't be written.
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
	 * Generates the PDF report with the data in the context.
	 * @param outputFile The path to the file which has to be written (without the extension).
	 * @return A generator error code or NO_ERROR if all went well.
	 * @see GeneratorError
	 * @throws IOException If the ouput file can't be opened or if it can't be written.
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
