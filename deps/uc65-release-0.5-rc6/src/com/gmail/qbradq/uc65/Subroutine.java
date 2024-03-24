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

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

/**
 * A representation of a subroutine.
 */
public class Subroutine {
	private String name;
	private List<Variable> parameters = new LinkedList<Variable>();
	private boolean interrupt = false;
	private boolean extern = false;
	private Variable returnVariable = null;
	
	/**
	 * @return The return variable for this subroutine, or null.
	 */
	public Variable getReturnVariable() {
		return returnVariable;
	}
	
	/**
	 * Sets the return variable for this subroutine.
	 * @param v The new return variable.
	 */
	public void setReturnVariable(Variable v) {
		returnVariable = v;
	}
	
	/**
	 * @return True if this subroutine should be visible to other translation
	 * units, false otherwise.
	 */
	public boolean isExtern() {
		return extern;
	}
	
	/**
	 * @return True if this subroutine handles an interrupt, false otherwise.
	 */
	public boolean isInterrupt() {
		return interrupt;
	}
	
	/**
	 * @return The name of the subroutine.
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * @return An unmodifiable list of the parameter variables.
	 */
	public List<Variable> getParameters() {
		return Collections.unmodifiableList(parameters);
	}
	
	/**
	 * Adds a parameter variable to the list of parameters.
	 * @param v The parameter variable to add.
	 */
	public void addParameter(Variable v) {
		parameters.add(v);
	}
	
	/**
	 * Constructs a subroutine.
	 * @param name The name of the subroutine.
	 * @param interrupt Flag to say if this subroutine handles an interrupt.
	 * @param extern Flag to say if this subroutine should be visible from other
	 * translation units.
	 */
	public Subroutine(String name, boolean interrupt, boolean extern) {
		this.name = name;
		this.interrupt = interrupt;
		this.extern = extern;
	}
	
	/**
	 * Generates the starting code for this subroutine.
	 * @param romBank The rom bank to generate code in.
	 * @param gen The code generator to use.
	 */
	public void generateStartCode(int romBank, CodeGenerator gen) {
		if(interrupt) {
			gen.emitOpCode(Operation.PHA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.TXA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.PHA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.TYA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.PHA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
		} else if(name.equals("main")) {
			gen.emitOpCode(Operation.SEI, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.CLD, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.LDX, AddressMode.IMMEDIATE, romBank, null, (byte)255, false);
			gen.emitOpCode(Operation.TXS, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
		}
	}
	
	/**
	 * Generates the code used to return from the subroutine.
	 * @param romBank The rom bank to generate code in.
	 * @param gen The code generator to use.
	 */
	public void generateReturn(int romBank, CodeGenerator gen) {
		if(interrupt) {
			gen.emitOpCode(Operation.PLA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.TAY, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.PLA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.TAX, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.PLA, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
			gen.emitOpCode(Operation.RTI, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
		} else if(name.equals("main")) {
			gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, name, (byte)0, false);
		} else {
			gen.emitOpCode(Operation.RTS, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
		}		
	}
}
