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
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Represents a table of data as a series of anonymous constant values
 */
public class AnonymousDataTable {
	public class Column {
		private int length;
		private List<Reference> values = new LinkedList<Reference>();
		
		/**
		 * @return The length in bytes of the data values
		 */
		public int getLength() {
			return length;
		}
		
		/**
		 * @return An unmodifiable list of value references for the column
		 */
		public List<Reference> getValues() {
			return Collections.unmodifiableList(values);
		}
		
		/**
		 * @return The number of value references in the column
		 */
		public int getCount() {
			return values.size();
		}
		
		/** Construct a new column with the given value byte length.
		 * 
		 * @param length 
		 */
		public Column(int length) {
			this.length = length;
		}
		
		/** Add a reference with the given value to the column.
		 * 
		 * @param value The value of the reference
		 * @return false if the given value is too wide for the column, true
		 * otherwise
		 */
		public boolean addValue(int value) {
			Reference r = new Reference(value);
			if(r.getWidth() > length) {
				return false;
			}
			values.add(r);
			return true;
		}
	}
	
	private Map<String, Column> columns = new HashMap<String, Column>();
	private Set<String> columnsThisRow = new HashSet<String>();
	
	/**
	 * @return An unmodifiable map of the columns in the table
	 */
	public Map<String, Column> getColumns() {
		return Collections.unmodifiableMap(columns);
	}
	
	/**
	 * @return The number of columns in the table
	 */
	public int getCount() {
		return columns.size();
	}
	
	/**
	 * @return true if it is still possible to add a column to the table, false
	 * otherwise
	 */
	public boolean canAddColumn() {
		for(Column c : columns.values()) {
			if(c.getCount() != 0) {
				return false;
			}
		}
		return true;
	}
	
	/** Convenience method to get the data list from a column by name.
	 * 
	 * @param name The name of the column
	 * @return The list of reference from the column, or null of the named
	 *         column is not in the table.
	 */
	public List<Reference> getColumnData(String name) {
		if(!columns.containsKey(name)) {
			return null;
		}
		return columns.get(name).getValues();
	}
	
	/** Construct a new AnonymousDataTable
	 */
	public AnonymousDataTable() {
	}
	
	/** Adds a new column to the table with the given byte length
	 * 
	 * @param name The name of the column
	 * @param length The byte length of values in the column
	 * @return false if columns may not be added or a duplicate, true otherwise
	 */
	public boolean addColumn(String name, int length) {
		if(!canAddColumn()) {
			return false;
		}
		columns.put(name, new Column(length));
		return true;
	}
	
	/** Add a value to the current row
	 * 
	 * @param column The name of the column
	 * @param value The value for the column
	 * @return false if the given value is too wide for the column, if the
	 * column is not valid, or if the column already has a value for this row.
	 */
	public boolean addValue(String column, int value) {
		Column c = columns.get(column);
		if(c == null) {
			return false;
		}
		
		if(columnsThisRow.contains(column)) {
			return false;
		}
		columnsThisRow.add(column);
		
		return c.addValue(value);
	}
	
	/** Call after adding all values for a row.
	 * 
	 * @return A set of all columns that did not receive a value
	 */
	public Set<String> endRow() {
		Set<String> ret = new HashSet<String>();
		for(String name : columns.keySet()) {
			if(!columnsThisRow.contains(name)) {
				ret.add(name);
			}
		}
		columnsThisRow.clear();
		
		return ret;
	}
}
