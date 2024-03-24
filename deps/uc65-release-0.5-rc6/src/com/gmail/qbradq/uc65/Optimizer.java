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

import java.util.EnumSet;
import java.util.Set;

/**
 * Implements a 6502 machine code optimizer using a state machine representation
 * of the software.
 */
public class Optimizer {
	/**
	 * Representation of a software instruction. 
]	 */
	public static class Instruction {
		/** The operation of the instruction */
		public Operation op;
		/** The addressing mode of the instruction */
		public AddressMode mode;
		/** The label the instruction applies to, if any */
		public String ref;
		/** The immediate value of the instruction, if any */
		public byte value;
		
		/** Constructs an instruction representation from the parameters given.
		 * 
		 * @param op The operation of the instruction.
		 * @param mode The addressing mode of the instruction.
		 * @param ref The label reference if any.
		 * @param value The immediate value if any.
		 */
		public static Instruction create(Operation op, AddressMode mode,
			String ref, byte value) {
			Instruction ret = new Instruction();
			ret.op = op;
			ret.mode = mode;
			ret.ref = ref;
			ret.value = value;
			return ret;
		}
	}
		
	private static class RegisterValue {
		private AddressMode mode;
		private String ref;
		private int value;
		private RegisterValue x;
		private RegisterValue y;
		
		public RegisterValue(AddressMode mode, String ref, int value,
			RegisterValue x, RegisterValue y) {
			this.mode = mode;
			this.ref = ref;
			this.value = value;
			this.x = x;
			this.y = y;
		}
		
		public boolean isEquivalent(RegisterValue r) {
			if(mode == null || r.mode == null) {
				return false;
			}
			if(mode != r.mode || value != r.value) {
				return false;
			}
			if(ref == null && r.ref != null) {
				return false;
			}
			if(r.ref == null && ref != null) {
				return false;
			}
			if(ref != null && !ref.equals(r.ref)) {
				return false;
			}
			if(mode == AddressMode.ADDRESSX && !x.isEquivalent(r.x)) {
				return false;
			}
			if(mode == AddressMode.ADDRESSY && !y.isEquivalent(r.y)) {
				return false;
			}
			// We don't do pointer tracking
			if(mode == AddressMode.INDIRECT || mode == AddressMode.INDIRECTX ||
				mode == AddressMode.INDIRECTY) {
				return false;
			}
			return true;
		}
		
		public boolean doesReference(String ref) {
			if(ref == null) {
				return false;
			}
			if(mode == AddressMode.ADDRESS ||
					mode == AddressMode.ADDRESSX ||
					mode == AddressMode.ADDRESSY) {
					return ref.compareTo(ref) == 0;
				}
			// We don't do pointer tracking, and all other cases are false
			return false;
		}
		
		public boolean isIncrementEquivalent(RegisterValue r) {
			if(mode != AddressMode.IMMEDIATE ||
				r.mode != AddressMode.IMMEDIATE) {
				return false;
			}
			return value == r.value - 1;
		}
		
		public boolean isDecrementEquivalent(RegisterValue r) {
			if(mode != AddressMode.IMMEDIATE ||
				r.mode != AddressMode.IMMEDIATE) {
				return false;
			}
			return value == r.value + 1;
		}
	}
	
	private static final Set<Operation> invalidatesAImplied = EnumSet.of(
		Operation.ASL,
		Operation.LSR,
		Operation.ROL,
		Operation.ROR
	);
	private static final Set<Operation> invalidatesA = EnumSet.of(
		Operation.ADC,
		Operation.AND,
		Operation.EOR,
		Operation.ORA,
		Operation.PLA,
		Operation.SBC
	);
	private static final Set<Operation> invalidatesX = EnumSet.of(
		Operation.DEX,
		Operation.INX,
		Operation.TSX
	);
	private static final Set<Operation> invalidatesY = EnumSet.of(
		Operation.DEY,
		Operation.INY
	);

	
	private static final RegisterValue unknown =
		new RegisterValue(null, null, 0, null, null);
	private RegisterValue x = unknown;
	private RegisterValue y = unknown;
	private RegisterValue a = unknown;
	
	/**
	 * Resets the optimizer.
	 * 
	 * Call this every time the state of the machine leaves a known state, such
	 * as after a jump or branch.
	 */
	public void reset() {
		x = y = a = unknown;
	}
	
	/**
	 * Call for every machine instruction emitted.
	 * 
	 * @param i The instruction that is being emitted.
	 * @return An equivalent instruction. The code generator may emit this
	 *         instruction with no logical impact to the software. If null is
	 *         returned, the code generator may emit no instruction at all
	 *         without logical impact to the software. The object returned may
	 *         be the parameter i. The parameter i will never be altered.
	 */
	public Instruction instruction(Instruction i) {
		switch(i.op) {
			case TAX:
				if(x.isEquivalent(a)) {
					return null;
				}
				x = a;
				break;
			case TAY:
				if(y.isEquivalent(a)) {
					return null;
				}
				y = a;
				break;
			case TXA:
				if(a.isEquivalent(x)) {
					return null;
				}
				a = x;
				break;
			case TYA:
				if(a.isEquivalent(y)) {
					return null;
				}
				a = y;
				break;
			case LDA:
				RegisterValue newA = new RegisterValue(i.mode, i.ref, i.value,
					x, y);
				if(a.isEquivalent(newA)) {
					return null;
				}
				a = new RegisterValue(i.mode, i.ref, i.value, x, y);
				break;
			case LDX:
				RegisterValue newX = new RegisterValue(i.mode, i.ref, i.value,
					x, y);
				if(x.isEquivalent(newX)) {
					return null;
				}
				if(x.isIncrementEquivalent(newX)) {
					x = new RegisterValue(i.mode, i.ref, i.value, x, y);
					return Instruction.create(Operation.INX,
						AddressMode.IMPLICIT, null, (byte)0);
				}
				if(x.isDecrementEquivalent(newX)) {
					x = new RegisterValue(i.mode, i.ref, i.value, x, y);
					return Instruction.create(Operation.DEX,
						AddressMode.IMPLICIT, null, (byte)0);
				}
				x = new RegisterValue(i.mode, i.ref, i.value, x, y);
				break;
			case LDY:
				RegisterValue newY = new RegisterValue(i.mode, i.ref, i.value,
					x, y);
				if(y.isEquivalent(newY)) {
					return null;
				}
				if(y.isIncrementEquivalent(newY)) {
					y = new RegisterValue(i.mode, i.ref, i.value, x, y);
					return Instruction.create(Operation.INY,
						AddressMode.IMPLICIT, null, (byte)0);
				}
				if(y.isDecrementEquivalent(newY)) {
					y = new RegisterValue(i.mode, i.ref, i.value, x, y);
					return Instruction.create(Operation.DEY,
						AddressMode.IMPLICIT, null, (byte)0);
				}
				y = new RegisterValue(i.mode, i.ref, i.value, x, y);
				break;
			case STA:
				if(x.doesReference(i.ref)) {
					x = unknown;
				}
				if(y.doesReference(i.ref)) {
					y = unknown;
				}
				break;
			case STX:
				if(a.doesReference(i.ref)) {
					a = unknown;
				}
				if(y.doesReference(i.ref)) {
					y = unknown;
				}
				break;
			case STY:
				if(a.doesReference(i.ref)) {
					a = unknown;
				}
				if(x.doesReference(i.ref)) {
					x = unknown;
				}
				break;
			case INC:
			case DEC:
				if(a.doesReference(i.ref)) {
					a = unknown;
				}
				if(x.doesReference(i.ref)) {
					x = unknown;
				}
				if(y.doesReference(i.ref)) {
					y = unknown;
				}
				break;
			default:
				if(i.mode == AddressMode.IMPLICIT &&
					invalidatesAImplied.contains(i.op)) {
					a = unknown;
				}
				if(invalidatesA.contains(i.op)) {
					a = unknown;
				}
				if(invalidatesX.contains(i.op)) {
					x = unknown;
				}
				if(invalidatesY.contains(i.op)) {
					y = unknown;
				}
				break;
		}
		return i;
	}
}
