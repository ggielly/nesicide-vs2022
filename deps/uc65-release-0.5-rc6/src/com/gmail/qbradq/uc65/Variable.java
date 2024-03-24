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

import java.util.EnumMap;
import java.util.Map;

/**
 * An abstraction of a variable definition.
 */
public class Variable {
	private static final Map<TokenType, Integer> typeSizes = new EnumMap<TokenType, Integer>(TokenType.class);
	static {
		typeSizes.put(TokenType.BYTE, 1);
		typeSizes.put(TokenType.WORD, 2);
		typeSizes.put(TokenType.LONG, 3);
		typeSizes.put(TokenType.DWORD, 4);
		typeSizes.put(TokenType.PORT, 1);
		typeSizes.put(TokenType.ADDRESS, 2);
	}
	
	/**
	 * @param t The type to test.
	 * @return True if the given TokenType is a type specifier.
	 */
	public static boolean isType(TokenType t) {
		return typeSizes.containsKey(t);
	}
	
	/**
	 * @param t The type to test.
	 * @return The number of bytes to use for a variable of the given type, or
	 * zero if the TokenType given is not a valid type specifier.
	 */
	public static int sizeForType(TokenType t) {
		if(typeSizes.containsKey(t)) {
			return typeSizes.get(t);
		}
		return 0;
	}
	
	protected String name;
	protected int width;
	protected int length;
	protected TokenType type;
	protected int address;
	protected SourceLine line;
	protected boolean generatable;
	protected int bank;
	
	/**
	 * Construct a new variable definition.
	 * @param line The source line the variable was defined on.
	 * @param name The full name of the variable including module scope.
	 * @param type The type specifier TokenType.
	 * @param length The length of the array.
	 * @param address The address of the variable, only valid for port type.
	 * @param generateable If true, this variable will generate labels.
	 * @param bank The memory bank to place the variable in.
	 */
	public Variable(SourceLine line, String name, TokenType type, int length,
		int address, boolean generatable, int bank) {
		this.line = line;
		this.name = name;
		this.width = sizeForType(type);
		this.length = length;
		this.type = type;
		this.address = address;
		this.generatable = generatable;
		this.bank = bank;
		if(type == TokenType.ADDRESS &&
			!isReadOnly()) {
			this.bank = 0;
		}
	}
	
	/**
	 * @return The memory bank to place the variable in.
	 */
	public int getBank() {
		return bank;
	}
	
	/**
	 * @return The address associated with a port variable.
	 */
	public int getAddress() {
		return address;
	}
	
	/**
	 * @return True if the variable is volatile, false otherwise.
	 */
	public boolean isVolatile() {
		return type == TokenType.PORT;
	}
	
	/**
	 * @return True if the variable cannot be written to.
	 */
	public boolean isReadOnly() {
		return false;
	}
	
	/**
	 * Generates variable code for this variable.
	 * @param extern A flag to say if the variable should be exported.
	 * @param imported A flag to say if this variable was imported from another
	 *        translation unit.
	 * @param gen The CodeGenerator object to use.
	 */
	public void generateCode(boolean extern, boolean imported,
		CodeGenerator gen) {
		
		if(!generatable) {
			return;
		}
		
		if(width > 1) {
			if(imported) {
				gen.emitImport(gen.labelNameFrom(name),
					bank == 0 && !isReadOnly());
			} else {
				gen.emitVariable(line, gen.labelNameFrom(name), 0, extern, bank,
					false, null);
			}
			for(int i = 0; i < width; ++i) {
				if(imported) {
					gen.emitImport(gen.labelNameFrom(getNameForByte(i)),
						bank == 0  && !isReadOnly());
				} else {
					gen.emitVariable(line, gen.labelNameFrom(getNameForByte(i)),
						length, extern, bank, false, null);
				}
			}
		} else {
			if(imported) {
				gen.emitImport(gen.labelNameFrom(name),
					bank == 0 && !isReadOnly());
			} else {
				gen.emitVariable(line, gen.labelNameFrom(name), length, extern,
					bank, false, null);
			}
		}
	}
	
	/**
	 * @return The name of the variable.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * @return The byte width of the variable.
	 */
	public int getWidth() {
		return width;
	}
	
	/**
	 * @return The length of the array.
	 */
	public int getLength() {
		return length;
	}
	
	/**
	 * @return The type this variable was defined with.
	 */
	public TokenType getType() {
		return type;
	}
	
	/**
	 * @param i The byte number to reference.
	 * @return The assembly label name for this byte of the variable.
	 */
	public String getNameForByte(int i) {
		if(width == 1) {
			return name;
		} else {
			char c = (char)('a' + i);
			return name + "." + c;
		}
	}
}
