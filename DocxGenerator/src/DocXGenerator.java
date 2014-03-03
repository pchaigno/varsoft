import java.io.*;
import java.util.HashMap;
import java.util.Map;

import fr.opensagres.xdocreport.core.XDocReportException;
import fr.opensagres.xdocreport.document.XDocReport;
import fr.opensagres.xdocreport.template.TemplateEngineKind;


public class DocXGenerator {

	private static InputStream in=null;
	private static OutputStream out=null;
	private static Map<String, Object> contextMap;
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		openTemplate(args[0]);

		contextMap = new HashMap<String, Object>();
		for(int i=2;i<args.length;i++)
			contextMap.put( "var"+(i-1), args[i]);
		
		generateReport(args[1]);
	}
	
	private static void openTemplate(String template)
	{
		try {
			in = new FileInputStream(new File(template));
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
	}
	
	private static void generateReport(String outputFile)
	{
		try {
			out = new FileOutputStream(new File(outputFile));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		try {
			XDocReport.generateReport( in, TemplateEngineKind.Velocity.name(), null, contextMap, out );
		} catch (XDocReportException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
