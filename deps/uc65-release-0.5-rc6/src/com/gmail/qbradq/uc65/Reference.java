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
 * Abstraction of a reference or constant value.
 */
public class Reference {
	private Variable var = null;
	private boolean addressOf = false;
	private boolean dereference = false;
	private int derefWidth = 0;
	private int value = 0;
	private Reference offset = null;
	
	/**
	 * @return True if this reference is dereferencing an address stored in a
	 *         variable, false otherwise.
	 */
	public boolean isDereference() {
		return dereference;
	}
	
	/**
	 * @return True if this reference refers to a variable's address, false
	 *         otherwise.
	 */
	public boolean isAddressReference() {
		return addressOf;
	}
	
	/**
	 * Construct a constant value reference.
	 * @param value The value of the reference.
	 */
	public Reference(int value) {
		this.value = value;
	}
	
	/**
	 * Construct a variable reference.
	 * @param var The variable to reference.
	 * @param addressOf If true, this references the address of the given
	 *        variable.
	 * @param dereference If true, this references a value at the address held
	 *        in the variable.
	 */
	public Reference(Variable var, boolean addressOf, boolean dereference,
		int derefWidth) {
		this.var = var;
		this.addressOf = addressOf;
		this.dereference = dereference;
		this.derefWidth = derefWidth;
	}
	
	/**
	 * @return True if the reference is a constant value, false otherwise.
	 */
	public boolean isConstant() {
		return var == null;
	}
	
	/**
	 * @return The constant value associated with this reference.
	 */
	public int getValue() {
		return value;
	}
	
	/**
	 * @return The effective array length of the reference.
	 */
	public int getLength() {
		if(var != null && !addressOf) {
			return var.getLength();
		}
		return 1;
	}
	
	/**
	 * @return The in-memory width of the variable reference, or the required
	 * byte width of a constant.
	 */
	public int getWidth() {
		if(dereference) {
			return derefWidth;
		}
		if(var != null) {
			return addressOf ? 2 : var.getWidth();
		}
		if((value & 0xffffff00) == 0) {
			return 1;
		} else if((value & 0xffff0000) == 0) {
			return 2;
		} else if((value & 0xff000000) == 0) {
			return 3;
		}
		return 4;
	}
	
	/** Return the byte from the given position for a constant value.
	 * 
	 * @param i The byte number, zero-based
	 * @return The data byte
	 */
	public byte getByte(int i) {
		switch(i) {
			case 0: return (byte)((value & 0x000000ff));
			case 1: return (byte)((value & 0x0000ff00) >> 8);
			case 2: return (byte)((value & 0x00ff0000) >> 16);
			case 3: return (byte)((value & 0xff000000) >> 24);
		}
		return (byte)0;
	}
	
	/**
	 * @return The array offset.
	 */
	public Reference getOffset() {
		return offset;
	}
	
	/**
	 * @param offset Set the array offset.
	 */
	public void setOffset(Reference offset) {
		this.offset = offset;
		if(offset.getWidth() != 1) {
			System.out.println("Something went wrong, recievied a " +
				"multi-byte offset for a reference.");
		}
	}
	
	/**
	 * Generate an operation that addresses a given byte of this reference.
	 * @param op The operation mnemonic.
	 * @param romBank The rom bank to place the operation in.
	 * @param i The byte index of the reference.
	 * @param gen The CodeGenerator object to use.
	 */
	public void emitOpForByte(Operation op, int i, int romBank, 
			CodeGenerator gen) {
		int width = getWidth();
		
		// Out-of-Bounds operations
		if(i >= width) {
			if(CodeGenerator.isReadOp(op)) {
				gen.emitOpCode(op, AddressMode.IMMEDIATE, romBank, null,
					(byte)0, false);
			}
			// Ignore out-of-bound write operations
		} else if(CodeGenerator.isReadOp(op)) {
			if(isConstant()) {
				int mask = 0xff << (i * 8);
				int v = value & mask;
				v = v >> (i * 8);
				gen.emitOpCode(op, AddressMode.IMMEDIATE, romBank, null,
					(byte)v, false);
			} else {
				emitAddressOpForByte(op, i, romBank, gen);
			}
		} else if(CodeGenerator.isWriteOp(op)) {
			if(isConstant()) {
				// This is bad
				System.out.println("Somthing went wrong, trying to write to " +
					"a constant");
			} else if(addressOf) {
				// Also very bad
				System.out.println("Something went wrong, trying to write to " +
					"an address");
			} else {
				emitAddressOpForByte(op, i, romBank, gen);
			}
		} else {
			// This is also bad
			System.out.println("Something went wrong, trying to emit a " +
				"non-read/write op code for a reference");
		}
	}
	
	private void emitAddressOpForByte(Operation op, int i, int romBank,
			CodeGenerator gen) {
		String label = gen.labelNameFrom(var.getNameForByte(i));
		// Handle dereferences specially
		if(dereference) {
			if(offset == null) {
				offset = new Reference(0);
			}
			if(!offset.isConstant()) {
				System.out.println("Something went wrong, trying to emit a " +
					"non-constant pointer offset");
			}
			int ofs = offset.getByte(0) + i;
			if(ofs > 255) {
				System.out.println("Something went wrong, trying to emit " +
					"a pointer offset greater than 255");
			}
			gen.emitOpCode(Operation.LDY, AddressMode.IMMEDIATE, romBank,
				null, (byte)ofs, false);
			gen.emitOpCode(op, AddressMode.INDIRECTY, romBank,
				gen.labelNameFrom(var.getName()), (byte)0, var.isVolatile());
		} else if(offset != null) {
			if(addressOf) {
				// Also very bad
				System.out.println("Something went wrong, " +
					"trying to read an indexed address reference");
			}
			if(offset.isConstant()) {
				label += "+" + offset.getValue();
				gen.emitOpCode(op, AddressMode.ADDRESS, romBank, label,
					(byte)0, var.isVolatile());
			} else {
				offset.emitOpForByte(Operation.LDX, 0, romBank, gen);
				gen.emitOpCode(op, AddressMode.ADDRESSX, romBank, label,
					(byte)0, var.isVolatile());
			}
		} else {
			if(addressOf) {
				if(i == 0) {
					gen.emitOpCode(op, AddressMode.LABELLO, romBank,
						var.getName(), (byte)0, var.isVolatile());
				} else if(i == 1) {
					gen.emitOpCode(op, AddressMode.LABELHI, romBank,
						var.getName(), (byte)0, var.isVolatile());
				} else {
					// Also very wrong
					System.out.println("Something went wrong, trying to " +
						"reference 2nd or greater byte of address");
				}
			} else {
				gen.emitOpCode(op, AddressMode.ADDRESS, romBank, label,
					(byte)0, var.isVolatile());
			}
		}
	}
}
