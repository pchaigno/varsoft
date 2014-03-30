package tests;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import org.apache.commons.io.IOUtils;

import generator.DocXGenerator;
import generator.GeneratorError;
import junit.framework.TestCase;

public class TestDocXGenerator extends TestCase {
	
	public static void testStatisticsReport() throws IOException {
		FileInputStream jsonInput = new FileInputStream("resources/test.json");
		String jsonText = IOUtils.toString(jsonInput);
		File template = new File("resources/test.docx");
		String outputPath = "resources/test_result";
		assertEquals(GeneratorError.NO_ERROR, DocXGenerator.generate(jsonText, template, outputPath));

		File docxFile = new File(outputPath+".docx");
		File pdfFile = new File(outputPath+".pdf");
		assertTrue(docxFile.isFile());
		assertTrue(pdfFile.isFile());

		assertTrue(docxFile.delete());
		assertTrue(pdfFile.delete());
	}
	
	public static void testErroredJSON() throws IOException {
		FileInputStream jsonInput = new FileInputStream("resources/errored.json");
		String jsonText = IOUtils.toString(jsonInput);
		File template = new File("resources/test.docx");
		String outputPath = "resources/errored_result";
		assertEquals(GeneratorError.JSON_ERROR, DocXGenerator.generate(jsonText, template, outputPath));
	}
}
