/* uc65 - Micro Code for 6502/NES
 * Copyright (C) 2013  Norman B. Lancaster
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package com.gmail.qbradq.uc65;

/**
 * Token type codes.
 */
public enum TokenType {
	// An invalid token
	INVALID,
	
	// Variable tokens
	IDENTIFIER,
	NUMBER,
	QUOTEDSTRING,
	
	// Keywords
	ROM,
	RAM,
	END,
	SUB,
	IF,
	ELSE,
	WHILE,
	LOOP,
	WHEN,
	BREAK,
	CONTINUE,
	RETURN,
	AS,
	CONSTANT,
	ASM,
	TYPE,
	TABLE,
	FILE,
	OF,
	IMPORT,
	BINFILE,
	
	// Modifiers
	EXPORT,
	FAST,
	
	// Types
	BYTE,
	WORD,
	LONG,
	DWORD,
	PORT,
	ADDRESS,
	
	// Operators
	ASSIGN,
	ADD,
	SUBTRACT,
	SHIFTLEFT,
	SHIFTRIGHT,
	AND,
	OR,
	EOR,
	ADDEQUAL,
	SUBEQUAL,
	SHIFTLEFTEQUAL,
	SHIFTRIGHTEQUAL,
	ANDEQUAL,
	OREQUAL,
	EOREQUAL,
	
	// Conditionals
	EQUALS,
	NOTEQUALS,
	LESS,
	GREATER,
	LESSOREQUAL,
	GREATEROREQUAL,
	
	// Seperators
	COMMA,
	IDXOPEN,
	IDXCLOSE,
	DEREFOPEN,
	DEREFCLOSE,
	AT,
}
