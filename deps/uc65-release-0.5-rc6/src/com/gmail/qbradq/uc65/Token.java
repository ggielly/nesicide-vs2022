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

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

/**
 * A representation of a single source code element.
 */
public class Token {
	private static Set<Character> singleOpChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'[', ']', ',', '(', ')', '@'
	}));
	private static Set<Character> quoteChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'\'', '"'
	}));
	private static Set<Character> opChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'=', '+', '-', '<', '>', '&', '|', '^', '!'
	}));
	private static Set<Character> numStartChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'$', '%', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	}));
	private static Set<Character> numChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'x', 'b', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'
	}));
	private static Set<Character> wordStartChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'_','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	}));
	private static Set<Character> wordChars = new HashSet<Character>(Arrays.asList(new Character[]{
		'_','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','.'
	}));
	private static Set<Character> seperators = new HashSet<Character>(Arrays.asList(new Character[]{
		' ', '\t'
	}));
	private static final Map<String, TokenType> tokenMap = new HashMap<String, TokenType>();
	private static final Map<TokenType, String> tokenNames = new HashMap<TokenType, String>();
	static {
		tokenMap.put("rom", TokenType.ROM);
		tokenMap.put("ram", TokenType.RAM);
		tokenMap.put("end", TokenType.END);
		tokenMap.put("sub", TokenType.SUB);
		tokenMap.put("if", TokenType.IF);
		tokenMap.put("else", TokenType.ELSE);
		tokenMap.put("while", TokenType.WHILE);
		tokenMap.put("loop", TokenType.LOOP);
		tokenMap.put("when", TokenType.WHEN);
		tokenMap.put("break", TokenType.BREAK);
		tokenMap.put("continue", TokenType.CONTINUE);
		tokenMap.put("return", TokenType.RETURN);
		tokenMap.put("as", TokenType.AS);
		tokenMap.put("constant", TokenType.CONSTANT);
		tokenMap.put("asm", TokenType.ASM);
		tokenMap.put("type", TokenType.TYPE);
		tokenMap.put("table", TokenType.TABLE);
		tokenMap.put("file", TokenType.FILE);
		tokenMap.put("of", TokenType.OF);
		tokenMap.put("import", TokenType.IMPORT);
		tokenMap.put("binfile", TokenType.BINFILE);
		
		tokenMap.put("export", TokenType.EXPORT);
		tokenMap.put("fast", TokenType.FAST);
		
		tokenMap.put("byte", TokenType.BYTE);
		tokenMap.put("word", TokenType.WORD);
		tokenMap.put("long", TokenType.LONG);
		tokenMap.put("dword", TokenType.DWORD);
		tokenMap.put("port", TokenType.PORT);
		tokenMap.put("address", TokenType.ADDRESS);
		
		tokenMap.put("=", TokenType.ASSIGN);
		tokenMap.put("+", TokenType.ADD);
		tokenMap.put("-", TokenType.SUBTRACT);
		tokenMap.put("<<", TokenType.SHIFTLEFT);
		tokenMap.put(">>", TokenType.SHIFTRIGHT);
		tokenMap.put("&", TokenType.AND);
		tokenMap.put("|", TokenType.OR);
		tokenMap.put("^", TokenType.EOR);
		tokenMap.put("+=", TokenType.ADDEQUAL);
		tokenMap.put("-=", TokenType.SUBEQUAL);
		tokenMap.put("<<=", TokenType.SHIFTLEFTEQUAL);
		tokenMap.put(">>=", TokenType.SHIFTRIGHTEQUAL);
		tokenMap.put("&=", TokenType.ANDEQUAL);
		tokenMap.put("|=", TokenType.OREQUAL);
		tokenMap.put("^=", TokenType.EOREQUAL);
		
		tokenMap.put("==", TokenType.EQUALS);
		tokenMap.put("!=", TokenType.NOTEQUALS);
		tokenMap.put("<", TokenType.LESS);
		tokenMap.put(">", TokenType.GREATER);
		tokenMap.put("<=", TokenType.LESSOREQUAL);
		tokenMap.put(">=", TokenType.GREATEROREQUAL);
		
		tokenMap.put(",", TokenType.COMMA);
		tokenMap.put("[", TokenType.IDXOPEN);
		tokenMap.put("]", TokenType.IDXCLOSE);
		tokenMap.put("(", TokenType.DEREFOPEN);
		tokenMap.put(")", TokenType.DEREFCLOSE);
		tokenMap.put("@", TokenType.AT);
		
		for(String key : tokenMap.keySet()) {
			tokenNames.put(tokenMap.get(key), key);
		}
		tokenNames.put(TokenType.NUMBER, "number");
		tokenNames.put(TokenType.IDENTIFIER, "identifier");
		tokenNames.put(TokenType.QUOTEDSTRING, "quoted string");
		tokenNames.put(TokenType.INVALID, "invalid token");
	}
	
	private enum State {
		START,
		NUMBER,
		WORD,
		OP,
		QUOTE,
	}
	
	/**
	 * @param type The type to get the name of.
	 * @return The user-friendly string name for the given type.
	 */
	public static String nameForType(TokenType type) {
		return tokenNames.get(type);
	}
	
	/**
	 * @param text The text of the line to parse.
	 * @return The queue of tokens from a given source line.
	 */
	public static Queue<Token> parse(String text) {
		Queue<Token> ret = new LinkedList<Token>();
		
		text += " ";
		int idx = 0;
		State state = State.START;
		String value = "";
		Character quoteChar = ' ';
		while(true) {
			if(idx >= text.length()) {
				break;
			}
			Character c = text.charAt(idx++);
			
			switch(state) {
				case START:
					if(seperators.contains(c)) {
						// Ignore seperators
					} else if(singleOpChars.contains(c)) {
						value += c;
						ret.add(new Token(tokenMap.get(value), value));
						value = "";
					} else if(numStartChars.contains(c)) {
						value += c;
						state = State.NUMBER;
					} else if(wordStartChars.contains(c)) {
						value += c;
						state = State.WORD;
					} else if (opChars.contains(c)) {
						value += c;
						state = State.OP;
					} else if(quoteChars.contains(c)) {
						quoteChar = c;
						state = State.QUOTE;
					} else {
						// Invalid token
						ret.add(new Token(TokenType.INVALID, c.toString()));
					}
					break;
				case NUMBER:
					if(numChars.contains(c)) {
						value += c;
					} else {
						ret.add(new Token(TokenType.NUMBER, value));
						value = "";
						state = State.START;
						--idx;
					}
					break;
				case WORD:
					if(wordChars.contains(c)) {
						value += c;
					} else {
						if(tokenMap.containsKey(value)) {
							ret.add(new Token(tokenMap.get(value), value));
						} else {
							ret.add(new Token(TokenType.IDENTIFIER, value));
						}
						value = "";
						state = State.START;
						--idx;
					}
					break;
				case OP:
					if(opChars.contains(c)) {
						value += c;
					} else {
						if(tokenMap.containsKey(value)) {
							ret.add(new Token(tokenMap.get(value), value));
						} else {
							ret.add(new Token(TokenType.INVALID, value));
						}
						value = "";
						state = State.START;
						--idx;						
					}
					break;
				case QUOTE:
					if(c == quoteChar) {
						ret.add(new Token(TokenType.QUOTEDSTRING, value));
						value = "";
						state = State.START;
					} else {
						value += c;
					}
					break;
			}
		}
		
		return ret;
	}
	
	private TokenType type = TokenType.INVALID;
	private String text = "";
	
	/**
	 * Construct a token by hand.
	 * @param type The token's type.
	 * @param text The source text of the token.
	 */
	public Token(TokenType type, String text) {
		this.type = type;
		this.text = text;
	}
	
	/**
	 * @param type The type to compare to.
	 * @return True if this token's type matches the provided type, false
	 * otherwise.
	 */
	public boolean isType(TokenType type) {
		return this.type == type;
	}
	
	/**
	 * @return The source text of the token.
	 */
	public String getText() {
		return text;
	}
	
	/**
	 * @return The TokenType of this token.
	 */
	public TokenType getType() {
		return type;
	}
}
