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
import java.util.HashMap;
import java.util.Map;

/**
 * Represents a composite type definition.
 */
public class CompositeType {
	/**
	 * Represents a member declaration within a composite type. 
	 */
	public class Member {
		private String name;
		private TokenType type;
		private int length;
		
		/**
		 * @return The name of the member
		 */
		public String getName() {
			return name;
		}
		
		/**
		 * @return The TokenType of the type specifier
		 */
		public TokenType getType() {
			return type;
		}
		
		/**
		 * @return The length of the type in bytes
		 */
		public int getLength() {
			return length;
		}
		
		/** Construct a new Member with the given parameters.
		 * 
		 * @param name The name of the member
		 * @param type The TokenType of the type specifier
		 * @param length The length of the type in bytes
		 */
		public Member(String name, TokenType type, int length) {
			this.name = name;
			this.type = type;
			this.length = length;
		}
	}
	
	private String name;
	private Map<String, Member> members = new HashMap<String, Member>();
	
	/**
	 * @return The name of the composite type
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * @return An unmodifiable map of the members of this type
	 */
	public Map<String, Member> getMembers() {
		return Collections.unmodifiableMap(members);
	}
	
	/** Construct a new CompositeType with the given name.
	 * 
	 * @param name The name of the type
	 */
	public CompositeType(String name) {
		this.name = name;
	}
	
	/** Add a member variable to the type with the specified parameters.
	 * 
	 * @param name The name of the member
	 * @param type The TokenType of the member's type
	 * @param length The length of the member's type in bytes
	 * @return false if the type already contains a member with the given name,
	 * true otherwise
	 */
	public boolean addMember(String name, TokenType type, int length) {
		if(members.containsKey(name)) {
			return false;
		}
		members.put(name,  new Member(name, type, length));
		return true;
	}
}
