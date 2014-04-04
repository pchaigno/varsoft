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
