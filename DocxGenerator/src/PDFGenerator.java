import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Map;

import fr.opensagres.xdocreport.converter.ConverterTypeTo;
import fr.opensagres.xdocreport.converter.ConverterTypeVia;
import fr.opensagres.xdocreport.converter.Options;
import fr.opensagres.xdocreport.core.XDocReportException;
import fr.opensagres.xdocreport.core.document.DocumentKind;
import fr.opensagres.xdocreport.document.XDocReport;
import fr.opensagres.xdocreport.template.TemplateEngineKind;
import fr.opensagres.xdocreport.template.formatter.FieldsMetadata;

/**
 * Test class
 * @author Benjamin
 *
 */
public class PDFGenerator {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// the 3 data used to load template report
		InputStream in=null;
		try {
			in = new FileInputStream( new File( "test.docx" ) );
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		String templateEngineKind = TemplateEngineKind.Velocity.name();
		FieldsMetadata metadata = null;

		// the context used to merge value with the template report
		Map<String, Object> contextMap = new HashMap<String, Object>();
		contextMap.put( "name", "world" );

		// generate report and convert it to PDF
		OutputStream out=null;
		try {
			out = new FileOutputStream( new File( "report.pdf" ) );
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Options options = Options.getTo(ConverterTypeTo.PDF).from(DocumentKind.DOCX);
		try {
			XDocReport.generateReportAndConvert(  in, templateEngineKind, metadata, contextMap, options, out );
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (XDocReportException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
