package tests;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import org.json.simple.parser.ParseException;

import fr.opensagres.xdocreport.core.XDocReportException;
import generator.DocXGenerator;
import junit.framework.TestCase;

public class TestDocXGenerator extends TestCase {
	
	public static void testStatisticsReport() throws XDocReportException, IOException, ParseException {
		File json = new File("resources/test.json");
		BufferedReader input = new BufferedReader(new FileReader(json));
		File template = new File("resources/test.docx");
		String outputPath = "resources/test_result";
		DocXGenerator.generate(input, template, outputPath);

		File docxFile = new File(outputPath+".docx");
		File pdfFile = new File(outputPath+".pdf");
		assertTrue(docxFile.isFile());
		assertTrue(pdfFile.isFile());

		assertTrue(docxFile.delete());
		assertTrue(pdfFile.delete());
	}
}
