package generator;

public enum GeneratorError {
	NO_ERROR(0), // No error detected.
	PARAMETER_ERROR(1), // Incorrect parameters for the program.
	JSON_ERROR(2), // Invalid JSON
	TEMPLATE_ERROR(3), // Error while reading the template file. 
	CONTEXT_ERROR(4), // Error while creating the context for the report.
	DOCX_GENERATION_ERROR(5), // Error from docxreport about the generation of the DOCX.
	PDF_CONVERTION_ERROR(6), // Error from docxreport about the convertion to PDF.
	PDF_GENERATION_ERROR(7), // Error from docxreport about the generation of the PDF.
	IO_ERROR(8), // In/Out exception: file which can't be opened, written or read. 
	TEMPLATE_NOT_FOUND(9), // If the template file can't be found.
	TEXT_MISSING(10), // If the text element in the JSON is missing.
	IMAGES_MISSING(11), // If the images element in the JSON is missing.
	LIST_MISSING(12); // If the list element in the JSON is missing.
	
	private int code;
	
	/**
	 * Enum constructor
	 * @param code The error code.
	 */
	private GeneratorError(int code) {
		this.code = code;
	}
	
	/**
	 * Accessor to code.
	 * @return The error code.
	 */
	public int getCode() {
		return this.code;
	}
}
