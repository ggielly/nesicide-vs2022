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

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Abstraction of a line of source code.
 */
public class SourceLine {
	public static Queue<SourceLine> loadAll(String path, BufferedReader reader) throws IOException {
		Queue<SourceLine> ret = new LinkedList<SourceLine>();
		int lineNumber = 0;
		
		String line;
		while((line = reader.readLine()) != null) {
			++lineNumber;
			
			// Strip comments and trim whitespace
			line = line.replaceAll(";.*$", "");
			line = line.trim();
			
			// Ignore empty lines
			if(line.isEmpty()) {
				continue;
			}
			
			ret.add(new SourceLine(path, lineNumber, line));
		}
		
		return ret;
	}
	
	private String path;
	private int line;
	private String text;
	private Queue<Token> tokens = new LinkedList<Token>();
	private boolean verbatim = true;
	
	private SourceLine(String path, int line, String text) {
		this.path = path;
		this.line = line;
		this.text = text;
	}
	
	/**
	 * @return True if this source line should be emitted to the output file
	 * verbatim.
	 */
	public boolean isVerbatim() {
		return verbatim;
	}
	
	/**
	 * @return True if the line has no more tokens, false otherwise.
	 */
	public boolean isEmpty() {
		return tokens.isEmpty();
	}
	
	/**
	 * @return The path of the source file this line comes from.
	 */
	public String getPath() {
		return path;
	}
	
	/**
	 * @return The line number of this source line.
	 */
	public int getLine() {
		return line;
	}
	
	/**
	 * @return The text of the source line.
	 */
	public String getText() {
		return text;
	}
	
	/**
	 * @return A copy of the queue of tokens in the line, useful for non-
	 * destructive inspection
	 */
	public Queue<Token> getTokens() {
		return new LinkedList<Token>(tokens);
	}
	
	/**
	 * Parses all tokens and reports errors to the compiler.
	 * @param compiler The compiler to report errors to.
	 */
	public void parse(Uc65 compiler) {
		verbatim = false;
		tokens = Token.parse(text);
		for(Token t : tokens) {
			if(t.isType(TokenType.INVALID)) {
				compiler.error(String.format("Invalid token \"%s\"", t.getText()), this);
			}
		}
	}
	
	/**
	 * @param type The token type to look for.
	 * @return True if this source line contains a token of the given type,
	 * false otherwise.
	 */
	public boolean contains(TokenType type) {
		for(Token t : tokens) {
			if(t.isType(type)) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * @param type The token type to look for.
	 * @return True if this source line starts with a token of this type, false
	 * otherwise.
	 */
	public boolean startsWith(TokenType type) {
		return !tokens.isEmpty() && tokens.peek().getType() == type;
	}
	
	/**
	 * @return The next token in the line, or null if the line is empty.
	 */
	public Token poll() {
		return tokens.poll();
	}
	
	/**
	 * @return The next token in the line, or null if the line is empty, but
	 * does not remove the token from the line.
	 */
	public Token peek() {
		return tokens.peek();
	}
}
