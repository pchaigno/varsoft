import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

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

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try
		{
			// initialize of the JSON Parser with the json file
			JSONParser parser = new JSONParser();
			JSONObject obj = (JSONObject) parser.parse(new FileReader("test.json"));

			// Initialize the template file
			InputStream in = new FileInputStream( new File( "test.docx" ) );
			IXDocReport report = XDocReportRegistry.getRegistry().loadReport(in, TemplateEngineKind.Velocity);

			// create the FieldsMetadata
			metadata = new FieldsMetadata();

			// create the report context
			contextMap = report.createContext();

			//add the data from the JSON to the report context
			computeText((JSONObject) obj.get("text"));
			computeImages((JSONObject) obj.get("images"));
			computeList((JSONObject) obj.get("list"));

			report.setFieldsMetadata(metadata);

			// generate the output file
			OutputStream out = new FileOutputStream(new File("report.docx"));
			report.process(contextMap, out);

		} catch (IOException e) {
			e.printStackTrace();
		} catch (XDocReportException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
	}

	private static void computeText(JSONObject textObject)
	{
		Iterator iter = textObject.entrySet().iterator();
		while(iter.hasNext()){
			Map.Entry entry = (Map.Entry)iter.next();
			contextMap.put(entry.getKey().toString(), entry.getValue().toString());
			System.out.println(entry.getKey() + "=>" + entry.getValue());
		}  
	}

	private static void computeImages(JSONObject imagesObject)
	{
		Iterator iter = imagesObject.entrySet().iterator();
		while(iter.hasNext()){
			Map.Entry entry = (Map.Entry)iter.next();
			metadata.addFieldAsImage(entry.getKey().toString());
			IImageProvider img = new FileImageProvider(new File(entry.getValue().toString()));
			img.setUseImageSize(true);
			contextMap.put(entry.getKey().toString(), img);
			System.out.println(entry.getKey() + "=>" + entry.getValue());
		}  
	}

	private static void computeList(JSONObject listObject)
	{
		Iterator iter = listObject.entrySet().iterator();
		while(iter.hasNext()){
			Map.Entry entry = (Map.Entry)iter.next();
			String key = entry.getKey().toString();
			JSONArray array = (JSONArray) entry.getValue();
			//System.out.println(key + "=>" + array);
			//get the fieldmetadata:
			HashSet metaData = new HashSet();
			Iterator iterArray = array.iterator();
			while(iterArray.hasNext()){
				JSONObject map = (JSONObject) iterArray.next();

				Iterator iterMap = map.entrySet().iterator();
				while(iterMap.hasNext()){
					Map.Entry entryMap = (Map.Entry)iterMap.next();	
					metaData.add(entryMap.getKey());
				}
			}

			Iterator iterMetaData = metaData.iterator();
			while(iterMetaData.hasNext()){
				metadata.addFieldAsList(key+"."+iterMetaData.next().toString());				
			}
			contextMap.put(key, array);
			
		} 
	}
}
