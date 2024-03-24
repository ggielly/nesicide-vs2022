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

import java.util.List;

/**
 * Represents a read-only variable with initial data.
 */
public class ReadOnlyVariable extends Variable {
	private byte[][] data;
	
	/** Construct the read-only variable with the given parameters and data.
	 * 
	 * @param line The source line the variable was defined on.
	 * @param name The name of the variable
	 * @param type The built-in type of the variable
	 * @param data A list of constant references that defines both the length
	 *             of the variable's array as well as the initial data.
	 * @param generatable If true code will be generated for this variable.
	 * @param bank The memory bank to place the variable in.
	 */
	public ReadOnlyVariable(SourceLine line, String name, TokenType type,
		List<Reference> data, boolean generatable, int bank) {
		super(line, name, type, data.size(), 0, generatable, bank);
		
		// Prep the byte arrays
		this.data = new byte[getWidth()][data.size()];
		for(int iByte = 0; iByte < getWidth(); ++iByte) {
			for(int i = 0; i < data.size(); ++i) {
				this.data[iByte][i] = data.get(i).getByte(iByte);
			}
		}
	}
	
	private ReadOnlyVariable(SourceLine line, String name, TokenType type,
		int length, boolean generatable, int bank) {
		super(line, name, type, length, 0, generatable, bank);
	}
	
	/** Factory method to construct a new ReadOnlyVariable for a buffer of
	 * bytes.
	 * 
	 * @param line The source line the variable was defined on.
	 * @param name The name of the variable
	 * @param buffer The data buffer
	 * @param generatable If true, code will be generated for this variable
	 * @return The new ReadOnlyVariable object
	 */
	public static ReadOnlyVariable forByteBuffer(SourceLine line, String name,
		byte[] buffer, boolean generatable, int bank) {
		ReadOnlyVariable ret = new ReadOnlyVariable(line, name, TokenType.BYTE,
			buffer.length, generatable, bank);
		ret.data = new byte[1][buffer.length];
		ret.data[0] = buffer;
		return ret;
	}
	
	/**
	 * @return True if this variable may not be written to.
	 */
	@Override
	public boolean isReadOnly() {
		return true;
	}
	
	/**
	 * Generates variable code for this variable.
	 * @param line The source line the variable was defined on.
	 * @param extern A flag to say if the variable should be exported.
	 * @param imported A flag to say if this variable was imported from another
	 *        translation unit.
	 * @param gen The CodeGenerator object to use.
	 */
	@Override
	public void generateCode(boolean extern, boolean imported,
		CodeGenerator gen) {
		
		if(!generatable) {
			return;
		}
		
		// The default implementation handles imports fine
		if(imported) {
			super.generateCode(extern, imported, gen);
			return;
		}
		
		// Output the variables
		if(width > 1) {
			byte[] empty = new byte[0];
			gen.emitVariable(line, gen.labelNameFrom(name), 0, extern, bank,
				true, empty);
			for(int i = 0; i < width; ++i) {
				gen.emitVariable(line, gen.labelNameFrom(getNameForByte(i)),
					length, extern, bank, true, data[i]);
			}
		} else {
			gen.emitVariable(line, gen.labelNameFrom(name), length, extern,
				bank, true, data[0]);
		}
	}
}
