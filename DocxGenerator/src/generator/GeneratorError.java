package generator;

public enum GeneratorError {
	NO_ERROR(0), PARAMETER_ERROR(1), JSON_ERROR(2), TEMPLATE_ERROR(3),
	CONTEXT_ERROR(4), DOCX_GENERATION_ERROR(5), PDF_CONVERTION_ERROR(6),
	PDF_GENERATION_ERROR(7), IO_ERROR(8), TEMPLATE_NOT_FOUND(9);
	
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
