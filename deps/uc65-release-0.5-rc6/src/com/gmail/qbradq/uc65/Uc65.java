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
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;
import java.util.Vector;

/**
 * uc65 compiler main class.
 */
public class Uc65 {
	// Global configuration block
	public static String sourcePath = null;
	public static String outPath = null;
	public static boolean emitDebugInfo = true;
	public static boolean emitSourceLines = false;
	public static Map<String, Integer> compilerConstants =
		new HashMap<String, Integer>();
	public static boolean autodeps = false;
	public static List<String> includePaths = new LinkedList<String>();
	
	private static void help() {
		System.out.println(
"Usage: uc65 [-dhsa] [-i path ...] [-c constant=value ...] [-o outfile] file");
		System.out.println("OPTIONS");
		System.out.println(
"  -a         Automatically build dependency information and write to outfile");
		System.out.println(
"             as a make rule");
		System.out.println(
"  -c name=v  Define a compile-time constant with name and value");
		System.out.println("  -d         Disable debug info output");
		System.out.println("  -h         Display this help text and exit");
		System.out.println("  -o outfile Output to the path outfile");
		System.out.println("  -s         Output source lines as comments");
		System.out.println(
"  -i path    Add path to the list of paths searched for import statements");
		System.out.println("ARGUMENTS");
		System.out.println("  file       The source file to compile");
		System.exit(1);
	}
	
	/**
	 * Main entry point for command line utility.
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		// Argument handling
		if(args.length == 0) {
			help();
		}
		Queue<String> argv = new LinkedList<String>(Arrays.asList(args));
		boolean getOutFile = false;
		boolean getImportPath = false;
		boolean getConstant = false;
		while(!argv.isEmpty()) {
			String arg = argv.poll();
			if(getOutFile) {
				outPath = arg;
				getOutFile = false;
			} else if(getImportPath) {
				includePaths.add(arg);
				getImportPath = false;
			} else if(getConstant) {
				String[] parts = arg.split("=");
				if(parts.length != 2) {
					help();
				}
				try {
					Integer v = Integer.parseInt(parts[1]);
					compilerConstants.put(parts[0], v);
				} catch(NumberFormatException e) {
					help();
				}
				getConstant = false;
			} else {
				if(!arg.startsWith("-")) {
					sourcePath = arg;
					break;
				}
				for(int i = 1; i < arg.length(); ++i) {
					char c = arg.charAt(i);
					switch(c) {
						case 'd':
							emitDebugInfo = false;
							break;
						case 's':
							emitSourceLines = true;
							break;
						case 'a':
							autodeps = true;
							break;
						case 'c':
							getConstant = true;
							if(i != arg.length() - 1) {
								help();
							}
							break;
						case 'o':
							getOutFile = true;
							if(i != arg.length() - 1) {
								help();
							}
							break;
						case 'i':
							getImportPath = true;
							if(i != arg.length() - 1) {
								help();
							}
							break;
						case 'h':
						default:
							help();
							break;
					}
				}
			}
		}
		if(!argv.isEmpty() || sourcePath == null || getOutFile) {
			help();
		}
		
		// Set up paths
		if(outPath == null) {
			outPath = sourcePath;
			if(outPath.contains(".")) {
				outPath = outPath.substring(0, outPath.lastIndexOf('.'));
			}
			if(autodeps) {
				outPath += ".dep";
			} else {
				outPath += ".s";
			}
		}
		File outFile = new File(outPath);
		File outDir = outFile.getParentFile();
		if(outDir != null && !outDir.exists()) {
			outDir.mkdirs();
		}
		
		File sourceFile = new File(sourcePath);
		Uc65 compiler = new Uc65(compilerConstants);
		if(autodeps) {
			compiler.buildDeps(sourceFile, outFile);
		} else {
			compiler.compile(sourceFile);
		}
		compiler.close();

		if(compiler.getNumberOfErrors() > 0) {
			System.out.println("Compilation failed");
			System.exit(1);
		}
		System.exit(0);
	}
	
	private int errors = 0;
	private int warnings = 0;
	private int romBank = 0;
	private int ramBank = 0;
	private CodeGenerator gen;
	private Map<String, Object> namespace = new HashMap<String, Object>();
	private Set<String> exportedNames = new HashSet<String>();
	private Set<String> importedNames = new HashSet<String>();
	private Queue<SourceLine> lines;
	private Subroutine currentSubroutine = null;
	private Stack<String> continueStack = new Stack<String>();
	private Stack<String> breakStack = new Stack<String>();
	private boolean lastStatementWasReturn = false;
	private boolean treatWarningsAsErrors = false;
	private Set<Integer> linesWithErrors = new HashSet<Integer>();
	private boolean importMode = false;
	private Set<String> canonicalPathsCompiled = new HashSet<String>();
	private String containingDirectory = null;
	
	private Uc65() {
	}
	
	private Uc65(Map<String, Integer> constants) {
		for(String key : constants.keySet()) {
			namespace.put(key, constants.get(key));
			exportedNames.add(key);
		}
	}
	
	private static Uc65 createImportCompiler(Uc65 parent) {
		Uc65 ret = new Uc65();
		ret.importMode = true;
		ret.canonicalPathsCompiled = parent.canonicalPathsCompiled;
		
		// Always include compiler constants
		for(String key : compilerConstants.keySet()) {
			ret.namespace.put(key, compilerConstants.get(key));
		}
		
		return ret;
	}
	
	private int getNumberOfErrors() {
		if(treatWarningsAsErrors) {
			return errors + warnings;
		} else {
			return errors;
		}
	}
	
	/**
	 * Report an error.
	 * @param msg The error message.
	 */
	public void error(String msg, SourceLine line) {
		if(line == null) {
			++errors;
			System.out.println(String.format("Error: %s", msg));
		} else if(!linesWithErrors.contains(line.getLine())) {
			++errors;
			linesWithErrors.add(line.getLine());
			System.out.println(String.format("%s(%d): Error: %s", line.getPath(), line.getLine(), msg));
		}
	}
	
	/**
	 * Report a warning.
	 * @param msg The warning message.
	 */
	public void warn(String msg, SourceLine line) {
		++warnings;
		if(line == null) {
			System.out.println(String.format("Warning: %s", msg));
		} else {
			System.out.println(String.format("%s(%d): Warning: %s", line.getPath(), line.getLine(), msg));
		}
	}
	
	private boolean loadSource(File source) {
		try {
			File dir = source.getCanonicalFile().getParentFile();
			if(dir == null) {
				error("Unable to determine parent directory of source file", null);
				return false;
			}
			containingDirectory = dir.getCanonicalPath();
		} catch(IOException e) {
			error("Unable to determine parent directory of source file", null);
			return false;			
		}
		
		String path = source.getPath();
		BufferedReader reader;
		
		// Load the source file
		try {
			canonicalPathsCompiled.add(source.getCanonicalPath());
			reader = new BufferedReader(new FileReader(source));
		} catch(FileNotFoundException e) {
			error("Unable to open file", null);
			return false;
		} catch(IOException e) {
			error("Unable to determine canonical file path", null);
			return false;
		}
		
		try {
			lines = SourceLine.loadAll(path, reader);
		} catch(IOException e) {
			error("Error reading file", null);
			return false;
		}
		
		boolean verbatim = false;
		for(SourceLine line : lines) {
			if(verbatim) {
				if(line.getText().matches("end\\s+asm")) {
					verbatim = false;
					line.parse(this);
				}
			} else {
				line.parse(this);
				if(line.startsWith(TokenType.ASM)) {
					verbatim = true;
				}
			}			
		}
		return errors == 0;
	}
	
	/** Build dependency list from a source file.
	 * 
	 * @param source The source file on disk.
	 */
	public void buildDeps(File source, File outFile) {
		if(!loadSource(source)) {
			return;
		}
		
		StringBuilder out = new StringBuilder();
		
		// Consume import lines until done
		out.append(String.format("%s :", sourcePath));
		while(true) {
			SourceLine line = lines.poll();
			if(line == null) {
				break;
			}
			
			if(line.isVerbatim() ||
				!line.startsWith(TokenType.IMPORT)) {
				continue;
			}
			
			if(expect(line, TokenType.IMPORT) == null) {
				continue;
			}
			String path = expectQuotedString(line);
			if(path == null) {
				continue;
			}
			expectEndOfLine(line);
			out.append(String.format(" %s", path));
		}
		out.append("\n");
		
		// Write output file
		try {
			BufferedWriter writer =
				new BufferedWriter(new FileWriter(outFile));
			writer.write(out.toString());
			writer.close();
		} catch(IOException e) {
			error("Unable to write output file", null);
		}
	}
	
	/**
	 * Compile a source file.
	 * @param source The source file on disk.
	 */
	public void compile(File source) {
		if(!loadSource(source)) {
			return;
		}
		
		gen = new CodeGenerator(source, this);

		// Consume program elements until done
		while(true) {
			SourceLine line = lines.poll();
			if(line == null) {
				break;
			}
			
			// Detect statement types and dispatch the proper handling method
			if(line.contains(TokenType.ROM)) {
				romLine(line);
			} else if(line.contains(TokenType.RAM)) {
				ramLine(line);
			} else if(line.contains(TokenType.IMPORT)) {
				importLine(line);
			} else if(line.contains(TokenType.SUB)) {
				subLine(line);
			} else if(line.contains(TokenType.BYTE)) {
				variableLine(line, TokenType.BYTE, 1);
			} else if(line.contains(TokenType.WORD)) {
				variableLine(line, TokenType.WORD, 2);
			} else if(line.contains(TokenType.LONG)) {
				variableLine(line, TokenType.LONG, 3);
			} else if(line.contains(TokenType.DWORD)) {
				variableLine(line, TokenType.DWORD, 4);
			} else if(line.contains(TokenType.ADDRESS)) {
				variableLine(line, TokenType.ADDRESS, 2);
			} else if(line.contains(TokenType.PORT)) {
				portLine(line);
			} else if(line.contains(TokenType.CONSTANT)) {
				constantLine(line);
			} else if(line.contains(TokenType.TYPE)) {
				typeLine(line);
			} else if(line.contains(TokenType.TABLE)) {
				tableLine(line);
			} else if(line.contains(TokenType.FILE)) {
				fileLine(line);
			} else if(line.contains(TokenType.BINFILE)) {
				binFileLine(line);
			} else if(looksLikeTypeVariableLine(line)) {
				variableLine(line, null, 0);
			} else {
				error("Unrecognized statement type", line);
			}
		}
		
		// Emit all variables
		if(!importMode) {
			gen.selectSourceSection(true);
			for(String key : namespace.keySet()) {
				Object o = namespace.get(key);
				if(o instanceof Variable) {
					Variable v = (Variable)o;
					boolean export = exportedNames.contains(key);
					boolean imported = importedNames.contains(key);
					if(v.getType() == TokenType.PORT) {
						gen.emitAssign(v.getName(), v.getAddress());
					} else {
						if(imported) {
							v.generateCode(false, imported, gen);
						} else {
							v.generateCode(export, false, gen);
						}
					}
				} else if(o instanceof Subroutine &&
					importedNames.contains(key)) {
					gen.emitImport(key, false);
				}
			}
		}
	}
	
	private void binFileLine(SourceLine line) {
		boolean extern = consume(line, TokenType.EXPORT);
		if(expect(line, TokenType.BINFILE) == null) {
			return;
		}
		
		String name = expectIdentifier(line);
		if(name == null) {
			return;
		}
		
		String path = expectQuotedString(line);
		if(path == null) {
			return;
		}
		
		Reference length = null;
		Reference offset = constantReference(line);
		if(offset == null) {
			offset = new Reference(0);
		} else {
			length = constantReference(line);
		}
		expectEndOfLine(line);
		
		File binFile = new File(containingDirectory, path);
		if(!binFile.exists()) {
			error(String.format("Unable to find file %s", path), line);
			return;
		}
		byte[] data = null;
		try {
			RandomAccessFile inf = new RandomAccessFile(binFile, "r");
			int fileLength = (int)inf.length();
			if(fileLength == 0) {
				error("File is empty", line);
				inf.close();
				return;
			}
			fileLength -= offset.getValue();
			if(fileLength <= 0) {
				error("Offset seeks to or past end of file", line);
				inf.close();
				return;
			}
			if(length != null &&
				fileLength < length.getValue()) {
				error("File is too short to satisfy length argument", line);
				inf.close();
				return;
			}
			if(length != null) {
				fileLength = length.getValue();
			}
			data = new byte[fileLength];
			inf.skipBytes(offset.getValue());
			inf.read(data, 0, fileLength);
			inf.close();
		} catch(FileNotFoundException e) {
			error(String.format("Unable to open file %s", path), line);
			return;
		} catch(IOException e) {
			error(String.format("Failed to read file %s", path), line);
			return;
		}
		
		Variable v = ReadOnlyVariable.forByteBuffer(line, name, data, true,
			romBank);
		addVariableSymbol(line, v, extern);
	}
	
	private File resolveImportPath(String path) {
		File ret;
		Queue<String> searchPaths = new LinkedList<String>(includePaths);
		searchPaths.add(containingDirectory);
		
		while(true) {
			String searchPath = searchPaths.poll();
			if(searchPath == null) {
				return null;
			}
			ret = new File(searchPath, path);
			if(ret.exists() &&
				ret.canRead() &&
				ret.isFile()) {
				break;
			}
		}
		return ret;
	}
	
	private void importLine(SourceLine line) {
		if(expect(line, TokenType.IMPORT) == null) {
			return;
		}
		String path = expectQuotedString(line);
		if(path == null) {
			return;
		}
		expectEndOfLine(line);
		
		File importFile = resolveImportPath(path);
		if(importFile == null) {
			error(String.format("Unable to find import file %s", path), line);
			return;
		}
		try {
			String canonicalPath = importFile.getCanonicalPath();
			if(canonicalPathsCompiled.contains(canonicalPath)) {
				return;
			}
		} catch(IOException e) {
			error(String.format(
				"Unable to find canonical path for import file %s", path),
				line);
			return;			
		}
		
		Uc65 importer = createImportCompiler(this);
		importer.compile(importFile);
		
		// Merge exported symbols
		for(String key : importer.exportedNames) {
			if(namespace.containsKey(key)) {
				error(String.format(
					"Imported file %s exports previously defined symbol %s",
					path, key), line);
			} else {
				Object o = importer.namespace.get(key);
				namespace.put(key, o);
				importedNames.add(key);
			}
		}
	}
	
	private void fileLine(SourceLine line) {
		// Handle optional export keyword
		boolean extern = consume(line, TokenType.EXPORT);
		
		if(expect(line, TokenType.FILE) == null) {
			return;
		}
		
		// Get the name of the file
		String name = expectIdentifier(line);
		if(name == null) {
			return;
		}
		expectEndOfLine(line);
		
		// Iterate over all data lines and collect data
		Vector<Byte> buffer = new Vector<Byte>();
		while(true) {
			SourceLine next = lines.poll();
			if(next == null) {
				error("Unterminated file statement", line);
				return;
			}
			if(next.contains(TokenType.END)) {
				expect(next, TokenType.END);
				expect(next, TokenType.FILE);
				expectEndOfLine(next);
				break;
			}
			Token t = next.peek();
			if(Variable.isType(t.getType())) {
				int vLength = Variable.sizeForType(t.getType());
				next.poll();
				while(true) {
					if(next.peek() == null) {
						break;
					}
					Reference r = expectReference(next);
					if(r == null) {
						break;
					}
					if(r.getWidth() > vLength) {
						error("Value out of range", next);
					}
					for(int i = 0; i < vLength; ++i) {
						buffer.add(r.getByte(i));
					}
					if(!consume(next, TokenType.COMMA)) {
						break;
					}
				}
			} else {
				String typeName = expectIdentifier(next);
				if(typeName == null) {
					continue;
				}
				
				Object o = resolveSymbol(typeName);
				if(!(o instanceof CompositeType)) {
					error("Expected type specifier", next);
					continue;
				}
				CompositeType type = (CompositeType)o;
				Map<String,CompositeType.Member> members = type.getMembers();
				
				LinkedHashMap<String,Reference> values =
					expectTypeMemberValues(next, type);
				for(String key : values.keySet()) {
					int vLength = members.get(key).getLength();
					for(int i = 0; i < vLength; ++i) {
						buffer.add(values.get(key).getByte(i));
					}
				}
			}
		}
		
		// Convert the data buffer
		byte[] data = new byte[buffer.size()];
		for(int i = 0; i < data.length; ++i) {
			data[i] = buffer.get(i);
		}
		
		// And finally produce the variable
		Variable var = ReadOnlyVariable.forByteBuffer(line, name, data, true,
			romBank);
		addVariableSymbol(line, var, extern);
	}
	
	private void tableLine(SourceLine line) {
		// Handle optional export keyword
		boolean extern = consume(line, TokenType.EXPORT);
		
		if(expect(line, TokenType.TABLE) == null) {
			return;
		}
		
		// Get the name of the table
		String name = expectIdentifier(line);
		if(name == null) {
			return;
		}
		
		// Get the type
		if(expect(line, TokenType.OF) == null) {
			return;
		}
		String typeName = expectIdentifier(line);
		if(typeName == null) {
			return;
		}
		Object o = resolveSymbol(typeName);
		if(!(o instanceof CompositeType)) {
			error("Expected composite type", line);
			return;
		}
		CompositeType type = (CompositeType)o;
		expectEndOfLine(line);
		
		// Construct the data table object
		AnonymousDataTable table = new AnonymousDataTable();
		for(CompositeType.Member m : type.getMembers().values()) {
			table.addColumn(m.getName(), m.getLength());
		}
		
		// Consume value lines
		while(true) {
			SourceLine next = lines.poll();
			if(next == null) {
				error("Unterminated table statement", line);
			}
			if(next.contains(TokenType.END)) {
				expect(next, TokenType.END);
				expect(next, TokenType.TABLE);
				expectEndOfLine(line);
				break;
			}
			
			Map<String,Reference> values = expectTypeMemberValues(next, type);
			if(values == null) {
				continue;
			}
			for(String key : values.keySet()) {
				table.addValue(key, values.get(key).getValue());
			}
			Set<String> missingKeys = table.endRow();
			for(String key : missingKeys) {
				error(String.format("Missing value for memeber %s", key), next);
			}
		}
		
		// Output variables
		for(CompositeType.Member m : type.getMembers().values()) {
			Variable var = new ReadOnlyVariable(line, name + "." + m.getName(),
				m.getType(), table.getColumnData(m.getName()), true, romBank);
			addVariableSymbol(line, var, extern);
		}
	}
	
	private LinkedHashMap<String,Reference> expectTypeMemberValues(
		SourceLine line, CompositeType type) {
		LinkedHashMap<String,Reference> ret =
			new LinkedHashMap<String,Reference>();
		Map<String,CompositeType.Member> members = type.getMembers();
		
		while(true) {
			String name = expectIdentifier(line);
			if(name == null) {
				return null;
			}
			
			if(expect(line, TokenType.ASSIGN) == null) {
				return null;
			}
			
			Reference ref = expectReference(line);
			if(!ref.isConstant()) {
				error("Only constant expressions may be used", line);
				return null;
			}
			
			if(ret.containsKey(name)) {
				error("Duplicate name in named value set", line);
				return null;
			}
			
			if(!members.containsKey(name)) {
				error(String.format(
					"Type %s does not contain a member named %s",
					type.getName(), name), line);
				break;
			}
			
			if(members.get(name).getLength() < ref.getWidth()) {
				error(String.format("Value exceeds range for member %s",
					name), line);
			}
			
			ret.put(name, ref);
						
			if(!consume(line, TokenType.COMMA)) {
				break;
			}
		}
		
		for(String memberName : members.keySet()) {
			if(!ret.containsKey(memberName)) {
				error(String.format("Missing initiaizer for member %s",
					memberName), line);
				return null;
			}
		}
		
		return ret;
	}
	
	private boolean looksLikeTypeVariableLine(SourceLine line) {
		for(Token t : line.getTokens()) {
			if(t.isType(TokenType.IDENTIFIER)) {
				Object o = resolveSymbol(t.getText());
				if(o != null && o instanceof CompositeType) {
					return true;
				} else {
					return false;
				}
			}
		}
		return false;
	}
	
	private void typeLine(SourceLine line) {
		// Handle optional export keyword
		boolean extern = false;
		if(consume(line, TokenType.EXPORT)) {
			extern = true;
		}
		
		// Complete type line
		if(expect(line, TokenType.TYPE) == null) {
			return;
		}
		String name = expectIdentifier(line);
		if(name == null) {
			return;
		}
		expectEndOfLine(line);
		
		// Construct composite type object
		CompositeType composite = new CompositeType(name);
		
		// Consume members
		while(true) {
			SourceLine next = lines.poll();
			
			if(next == null) {
				error("Unterminated type definition", line);
				return;	
			} else if(next.contains(TokenType.END)) {
				expect(next, TokenType.END);
				expect(next, TokenType.TYPE);
				expectEndOfLine(line);
				break;
			} else {
				Token type = next.poll();
				if(type == null || !Variable.isType(type.getType())) {
					error("Expected built-in type name", next);
					continue;
				}
				
				String memberName = expectIdentifier(next);
				if(memberName == null) {
					continue;
				}
				
				expectEndOfLine(next);
				
				if(!composite.addMember(memberName, type.getType(),
					Variable.sizeForType(type.getType()))) {
					error("Duplicate member in type", next);
				}
			}
		}
		
		if(composite.getMembers().size() <= 0) {
			error("At least one member must be defined for a composite type",
				line);
		}
		
		addSymbol(line, name, composite, extern);
	}
	
	private void assemblyBlock(SourceLine line) {
		gen.newExecutionBlock();
		
		if(expect(line, TokenType.ASM) == null) {
			return;
		}
		expectEndOfLine(line);
		
		while(!lines.isEmpty()) {
			line = lines.poll();
			if(line.isVerbatim()) {
				gen.emitVerbatimLine(line);
			} else {
				break;
			}
		}
		
		if(expect(line, TokenType.END) == null) {
			return;
		}
		if(expect(line, TokenType.ASM) == null) {
			return;
		}
		expectEndOfLine(line);
	}
	
	private void constantLine(SourceLine line) {
		boolean export = consume(line, TokenType.EXPORT);
		if(expect(line, TokenType.CONSTANT) == null) {
			return;
		}
		
		String name = expectIdentifier(line);
		if(name == null) {
			return;
		}
		
		if(expect(line, TokenType.ASSIGN) == null) {
			return;
		}
		
		int value = constant(line);
		expectEndOfLine(line);
		
		addSymbol(line, name, new Integer(value), export);
	}
	
	private void portLine(SourceLine line) {
		boolean extern = false;
		if(consume(line, TokenType.EXPORT)) {
			extern = true;
		}
		
		if(expect(line, TokenType.PORT) == null) {
			return;
		}
		
		String name = expectIdentifier(line);
		if(name == null) {
			return;
		}
		
		if(expect(line, TokenType.ASSIGN) == null) {
			return;
		}
		
		int address = constant(line);
		if(address < 0 || address > 0xffff) {
			error("Port address out of range", line);
		}
		expectEndOfLine(line);
		
		Variable v = new Variable(line, name, TokenType.PORT, 1, address,
			true, ramBank);
		addSymbol(line, name, v, extern);
	}
	
	/**
	 * Must be called before the object is destroyed.
	 */
	public void close() {
		if(gen != null) {
			gen.close();
		}
	}
	
	private void addSymbol(SourceLine line, String name, Object o,
		boolean export) {
		if(namespace.containsKey(name)) {
			error(String.format("Duplicate symbol name %s", name), line);
			return;
		}
		namespace.put(name, o);
		if(export) {
			exportedNames.add(name);
		}
	}
	
	private void addVariableSymbol(SourceLine line, Variable v, boolean extern
		) {
		addSymbol(line, v.getName(), v, extern);
		
		// Generate psuedo-variables for the byte references
		if(v.getWidth() > 1) {
			for(int i = 0; i < v.getWidth(); ++i) {
				Variable n = new Variable(line, v.getNameForByte(i),
					TokenType.BYTE, v.getLength(), 0, false, v.getBank());
				addSymbol(line, n.getName(), n, extern);
			}
		}
	}
	
	private Object resolveSymbol(String name) {
		if(name == null) {
			return null;
		}
		if(currentSubroutine != null) {
			String localName = currentSubroutine.getName() + "$" + name;
			if(namespace.containsKey(localName)) {
				return namespace.get(localName);
			}
		}
		if(namespace.containsKey(name)) {
			return namespace.get(name);
		}
		return null;
	}
	
	private Subroutine subDefinition(SourceLine line) {
		// Handle modifiers
		boolean extern = false;
		while(true) {
			if(consume(line, TokenType.EXPORT)) {
				extern = true;
				continue;
			}
			break;
		}
		
		// Get name
		expect(line, TokenType.SUB);
		Token t = expect(line, TokenType.IDENTIFIER);
		if(t == null) {
			return null;
		}
		String name = t.getText();
		
		Subroutine ret = new Subroutine(name, name.equals("frame") ||
			name.equals("interrupt"), extern);
		
		// Process parameter list
		while(!line.isEmpty()) {
			Token next = line.peek();
			if(Variable.isType(next.getType())) {
				line.poll();
				subParam(line, name, next.getType(), ret);
			} else if(next.isType(TokenType.AS)) {
				break;
			} else {
				error(String.format("Unexpected token %s",
					line.peek().getText()), line);
				break;
			}
			if(!consume(line, TokenType.COMMA)) {
				break;
			}
		}
		
		// Look for the return type
		if(consume(line, TokenType.AS)) {
			Token type = line.poll();
			if(type == null) {
				error("Unexpected end of line", line);
			} else if(!Variable.isType(type.getType())) {
				error("Expected builtin type", line);
			} else {
				Variable returnValue = new Variable(line, name + "$return",
					type.getType(), 1, 0, true, ramBank);
				ret.setReturnVariable(returnValue);
			}
		}
		
		expectEndOfLine(line);
		return ret;
	}
	
	private void subParam(SourceLine line, String subName, TokenType type,
		Subroutine sub) {
		String paramName = expectIdentifier(line);
		if(paramName == null) {
			return;
		}
		String fullName = subName + "$" + paramName;
		Variable param = new Variable(line, fullName, type, 1, 0, true,
			ramBank);
		sub.addParameter(param);
	}
	
	private void subLine(SourceLine line) {
		Subroutine sub = subDefinition(line);
		if(sub == null) {
			return;
		}
		for(Variable param : sub.getParameters()) {
			addVariableSymbol(line, param, sub.isExtern());
		}
		if(sub.getReturnVariable() != null) {
			addVariableSymbol(line, sub.getReturnVariable(), sub.isExtern());
		}
		addSymbol(line, sub.getName(), sub, sub.isExtern());
		
		// Sanity checks
		if(sub.isInterrupt() && sub.getReturnVariable() != null) {
			error("Interrupt subroutines may not return a value", line);
		} else if(sub.getName().equals("main") && sub.getReturnVariable() != null) {
			error("Subroutine main may not return a value", line);
		}
		
		// For import mode, just skip until the end of the subroutine
		if(importMode) {
			while(true) {
				SourceLine next = lines.poll();
				if(next == null) {
					error("Unterminated subroutine", line);
					break;
				}
				if(consume(next, TokenType.END) &&
					consume(next, TokenType.SUB)) {
					expectEndOfLine(line);
					break;
				}
			}
			return;
		}
		
		// Process the subroutine body
		lastStatementWasReturn = false;
		currentSubroutine = sub;
		gen.enterProcedure(line, sub.getName(), sub.isExtern(), romBank);
		sub.generateStartCode(romBank, gen);
		executableBody();
		currentSubroutine = null;
		
		// And make sure we were terminated correctly
		if(lines.isEmpty()) {
			error("Unexpected end of file", null);
			return;
		}
		
		SourceLine l = lines.poll();
		if(expect(l, TokenType.END) == null ||
			expect(l, TokenType.SUB) == null) {
			return;
		}
		expectEndOfLine(l);
		
		// Subroutine exit
		if(!lastStatementWasReturn && sub.getReturnVariable() != null) {
			error("Missing return statement", l);
		} else if(!lastStatementWasReturn) {
			gen.emitSourceLine(l);
			sub.generateReturn(romBank, gen);			
		}
		gen.exitProcedure();
	}
	
	private void executableBody() {
		gen.newExecutionBlock();
		while(!lines.isEmpty()) {
			SourceLine line = lines.peek();
			
			if(line.contains(TokenType.ASSIGN) ||
				line.contains(TokenType.ADDEQUAL) ||
				line.contains(TokenType.SUBEQUAL) ||
				line.contains(TokenType.SHIFTLEFTEQUAL) ||
				line.contains(TokenType.SHIFTRIGHTEQUAL) ||
				line.contains(TokenType.ANDEQUAL) ||
				line.contains(TokenType.OREQUAL) ||
				line.contains(TokenType.EOREQUAL)) {
				lastStatementWasReturn = false;
				lines.poll();
				assignLine(line);
			} else if(line.contains(TokenType.BYTE)) {
				lastStatementWasReturn = false;
				lines.poll();
				variableLine(line, TokenType.BYTE, 1);
			} else if(line.contains(TokenType.WORD)) {
				lastStatementWasReturn = false;
				lines.poll();
				variableLine(line, TokenType.WORD, 2);
			} else if(line.contains(TokenType.LONG)) {
				lastStatementWasReturn = false;
				lines.poll();
				variableLine(line, TokenType.LONG, 3);
			} else if(line.contains(TokenType.DWORD)) {
				lastStatementWasReturn = false;
				lines.poll();
				variableLine(line, TokenType.DWORD, 4);
			} else if(line.contains(TokenType.ADDRESS)) {
				lastStatementWasReturn = false;
				lines.poll();
				variableLine(line, TokenType.ADDRESS, 2);
			} else if(line.startsWith(TokenType.IF)) {
				lastStatementWasReturn = false;
				lines.poll();
				handleIf(line);
			} else if(line.startsWith(TokenType.WHILE)) {
				lastStatementWasReturn = false;
				lines.poll();
				handleWhile(line);
			} else if(line.startsWith(TokenType.LOOP)) {
				lastStatementWasReturn = false;
				lines.poll();
				handleLoop(line);
			} else if(line.startsWith(TokenType.BREAK)) {
				lastStatementWasReturn = false;
				lines.poll();
				handleBreak(line);
			} else if(line.startsWith(TokenType.CONTINUE)) {
				lastStatementWasReturn = false;
				lines.poll();
				handleContinue(line);
			} else if(line.startsWith(TokenType.RETURN)) {
				lastStatementWasReturn = true;
				lines.poll();
				handleReturn(line);
			} else if(line.contains(TokenType.ASM)) {
				lastStatementWasReturn = false;
				lines.poll();
				assemblyBlock(line);
			} else if(looksLikeTypeVariableLine(line)) {
				lastStatementWasReturn = false;
				lines.poll();
				variableLine(line, null, 0);
			} else {
				Subroutine sub = consumeSubroutine(line);
				if(sub == null) {
					// Special case to handle unknown identifiers
					Token t = line.peek();
					if(t != null &&
						t.isType(TokenType.IDENTIFIER)) {
						error(String.format("Unknown identifier %s",
							t.getText()), line);
						lines.poll();
						continue;
					} else {
						break;
					}
				}
				lastStatementWasReturn = false;
				lines.poll();
				handleCall(line, sub);
			}
		}
	}
	
	private Subroutine consumeSubroutine(SourceLine line) {
		Token t = line.peek();
		if(t == null) {
			return null;
		}
		Object o = resolveSymbol(t.getText());
		if(!(o instanceof Subroutine)) {
			return null;
		}
		line.poll();
		return (Subroutine)o;
	}
	
	private void handleCall(SourceLine line, Subroutine sub) {
		gen.emitSourceLine(line);
		List<Variable> params = sub.getParameters();
		for(int i = 0; i < params.size(); ++i) {
			handleAssign(line, new Reference(params.get(i), false, false, 0));
			if(i < params.size() - 1) {
				expect(line, TokenType.COMMA);
			}
		}
		gen.emitOpCode(Operation.JSR, AddressMode.ADDRESS, romBank, sub.getName(), (byte)0, false);
	}
	
	private void handleReturn(SourceLine line) {
		gen.emitSourceLine(line);
		expect(line, TokenType.RETURN);
		
		// Handle return value if nessecary
		Variable ret = currentSubroutine.getReturnVariable();
		if(ret != null) {
			Reference returnRef = new Reference(ret, false, false, 0);
			handleAssign(line, returnRef);
		}
		
		expectEndOfLine(line);
		currentSubroutine.generateReturn(romBank, gen);
	}
	
	private void handleContinue(SourceLine line) {
		gen.emitSourceLine(line);
		expect(line, TokenType.CONTINUE);
		
		int depth = 1;
		if(!line.isEmpty()) {
			depth = constant(line);
		}
		expectEndOfLine(line);
		
		if(depth < 1) {
			error("Continue depth too shallow", line);
		}
		if(depth > continueStack.size()) {
			error("Continue depth too deep", line);
		}
		String label = continueStack.get(continueStack.size() - depth);
		gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, label, (byte)0, false);
	}
	
	private void handleBreak(SourceLine line) {
		gen.emitSourceLine(line);
		expect(line, TokenType.BREAK);
		
		int depth = 1;
		if(!line.isEmpty()) {
			depth = constant(line);
		}
		expectEndOfLine(line);
		
		if(depth < 1) {
			error("Break depth too shallow", line);
		}
		if(depth > breakStack.size()) {
			error("Break depth too deep", line);
		}
		String label = breakStack.get(breakStack.size() - depth);
		gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, label, (byte)0, false);
	}
	
	private void handleLoop(SourceLine line) {
		gen.emitSourceLine(line);
		if(expect(line, TokenType.LOOP) == null) {
			return;
		}
		
		String startLabel = gen.label();
		String endLabel = gen.label();
		breakStack.push(endLabel);
		continueStack.push(startLabel);
		
		gen.emitLabel(romBank, startLabel);
		executableBody();
		
		line = lines.poll();
		if(line == null) {
			error("Unexpected end of file", line);
		} else if(expect(line, TokenType.END) == null ||
			expect(line, TokenType.LOOP) == null) {
		} else if(!line.isEmpty()) {
			if(expect(line, TokenType.WHEN) != null) {
				handleConditional(line, endLabel, startLabel);
			}
		} else {
			gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, startLabel, (byte)0, false);
		}
		expectEndOfLine(line);
		gen.emitLabel(romBank, endLabel);
		gen.newExecutionBlock();
		breakStack.pop();
		continueStack.pop();
		lastStatementWasReturn = false;
	}
	
	private void handleWhile(SourceLine line) {
		if(expect(line, TokenType.WHILE) == null) {
			return;
		}
		
		String startLabel = gen.label();
		String continueLabel = gen.label();
		String endLabel = gen.label();
		breakStack.push(endLabel);
		continueStack.push(continueLabel);
		
		gen.emitLabel(romBank, startLabel);
		gen.newExecutionBlock();
		handleConditional(line, continueLabel, endLabel);
		gen.emitLabel(romBank, continueLabel);
		executableBody();
		gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, startLabel, (byte)0, false);
		gen.emitLabel(romBank, endLabel);
		gen.newExecutionBlock();
		
		line = lines.poll();
		if(line == null) {
			error("Unexpected end of file", line);
		}
		expect(line, TokenType.END);
		expect(line, TokenType.WHILE);
		expectEndOfLine(line);
		breakStack.pop();
		continueStack.pop();
		lastStatementWasReturn = false;
	}
	
	private void handleIf(SourceLine line) {
		if(expect(line, TokenType.IF) == null) {
			return;
		}
		
		String thenLabel = gen.label();
		String elseLabel = gen.label();
		String endLabel = gen.label();
		
		handleConditional(line, thenLabel, elseLabel);
		gen.emitLabel(romBank, thenLabel);
		executableBody();
		// Only emit the Jump-to-End instruction if there's an Else clause
		line = lines.peek();
		if(line != null && line.startsWith(TokenType.ELSE)) {
			gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank,
				endLabel, (byte)0, false);
		}
		gen.newExecutionBlock();
		gen.emitLabel(romBank, elseLabel);
		
		// Process else statements until there are no more
		line = lines.poll();
		if(line == null) {
			error("Unexpeccted end of file", line);
			return;
		}
		while(line.startsWith(TokenType.ELSE)) {
			expect(line, TokenType.ELSE);
			if(line.startsWith(TokenType.IF)) {
				expect(line, TokenType.IF);
				String nextThen = gen.label();
				String nextElse = gen.label();
				handleConditional(line, nextThen, nextElse);
				gen.emitLabel(romBank, nextThen);
				executableBody();
				gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, endLabel, (byte)0, false);
				gen.newExecutionBlock();
				gen.emitLabel(romBank, nextElse);
			} else if(line.isEmpty()) {
				executableBody();
				gen.newExecutionBlock();
			} else {
				error(String.format("Expected if, found %s", line.peek().getText()), line);
				break;
			}
			line = lines.poll();
		}
		
		expect(line, TokenType.END);
		expect(line, TokenType.IF);
		gen.emitLabel(romBank, endLabel);
		gen.newExecutionBlock();
		lastStatementWasReturn = false;
 	}
	
	private void handleConditional(SourceLine line, String trueLabel, String falseLabel) {
		gen.emitSourceLine(line);
		
		Reference lparm = expectReference(line);
		if(lparm == null) {
			return;
		}
		
		Token t = line.poll();
		if(t == null) {
			error("Unexpected end of line", line);
			return;
		}
		
		Reference rparm = expectReference(line);
		if(rparm == null) {
			return;
		}
		expectEndOfLine(line);
		
		// Determine length of comparison operation and provide warnings
		int leftLength = lparm.getWidth();
		int rightLength = rparm.getWidth();
		int length = Math.max(leftLength, rightLength);
		if(leftLength != rightLength && !lparm.isConstant() && !rparm.isConstant()) {
			warn("Comparison of variables of differing width", line);
		}
		
		switch(t.getType()) {
			case EQUALS:
				if(length == 1) {
					if(rparm.isConstant() && rparm.getValue() == 0) {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);						
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					} else {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);
						rparm.emitOpForByte(Operation.CMP, 0, romBank, gen);
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
				} else {
					String falseJumpLabel = gen.label();
					if(rparm.isConstant() && rparm.getValue() == 0) {
						for(int i = 0; i < length; ++i) {
							lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, falseJumpLabel, (byte)0, false);
						}
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitLabel(romBank, falseJumpLabel);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					} else {
						for(int i = 0; i < length; ++i) {
							lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							rparm.emitOpForByte(Operation.CMP, i, romBank, gen);
							gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, falseJumpLabel, (byte)0, false);
						}
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitLabel(romBank, falseJumpLabel);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
				}
				break;
			case NOTEQUALS:
				if(rparm.isConstant() && rparm.getValue() == 0) {
					if(length == 1) {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);						
						gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);						
					} else {
						String falseJumpLabel = gen.label();
						for(int i = 0; i < length; ++i) {
							lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, falseJumpLabel, (byte)0, false);
						}
						gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitLabel(romBank, falseJumpLabel);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
				} else {
					for(int i = 0; i < length; ++i) {
						lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
						rparm.emitOpForByte(Operation.CMP, i, romBank, gen);
						gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
					gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
				}
				break;
			case LESS:
				if(rparm.isConstant() && rparm.getValue() == 0) {
					lparm.emitOpForByte(Operation.LDA, lparm.getWidth() - 1, romBank, gen);
					gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
					gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
				} else {
					if(length == 1) {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);
						rparm.emitOpForByte(Operation.CMP, 0, romBank, gen);
						gen.emitOpCode(Operation.BCC, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					} else {
						gen.emitOpCode(Operation.SEC, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
						for(int i = 0; i < length; ++i) {
							lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							rparm.emitOpForByte(Operation.SBC, i, romBank, gen);
						}
						gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
				}
				break;
			case GREATER:
				if(rparm.isConstant() && rparm.getValue() == 0) {
					String falseJumpLabel = gen.label();
					lparm.emitOpForByte(Operation.LDA, lparm.getWidth() - 1, romBank, gen);
					gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, falseJumpLabel, (byte)0, false);
					if(length == 1) {
						gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
					} else {
						gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						for(int i = lparm.getWidth() - 2; i >= 0; --i) {
							lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						}
					}
					gen.emitLabel(romBank, falseJumpLabel);
					gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
				} else {
					gen.emitOpCode(Operation.SEC, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
					for(int i = 0; i < length; ++i) {
						rparm.emitOpForByte(Operation.LDA, i, romBank, gen);
						lparm.emitOpForByte(Operation.SBC, i, romBank, gen);
					}
					gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
					gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
				}
				break;
			case LESSOREQUAL:
				if(rparm.isConstant() && rparm.getValue() == 0) {
					if(length == 1) {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);
						gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					} else {
						String falseJumpLabel = gen.label();
						lparm.emitOpForByte(Operation.LDA, lparm.getWidth() - 1, romBank, gen);
						gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, falseJumpLabel, (byte)0, false);
						for(int i = lparm.getWidth() - 2; i >= 0; --i) {
							lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS, romBank, falseJumpLabel, (byte)0, false);
						}
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitLabel(romBank, falseJumpLabel);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
				} else {
					gen.emitOpCode(Operation.SEC, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
					for(int i = 0; i < length; ++i) {
						lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
						rparm.emitOpForByte(Operation.SBC, i, romBank, gen);
					}
					gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
					gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
					gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
				}
				break;
			case GREATEROREQUAL:
				if(rparm.isConstant() && rparm.getValue() == 0) {
					lparm.emitOpForByte(Operation.LDA, lparm.getWidth() - 1, romBank, gen);
					gen.emitOpCode(Operation.BPL, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
					gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
				} else {
					if(length == 1) {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);
						rparm.emitOpForByte(Operation.CMP, 0, romBank, gen);
						gen.emitOpCode(Operation.BCS, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					} else {
						gen.emitOpCode(Operation.SEC, AddressMode.IMPLICIT, romBank, null, (byte)0, false);
						for(int i = 0; i < length; ++i) {
							rparm.emitOpForByte(Operation.LDA, i, romBank, gen);
							lparm.emitOpForByte(Operation.SBC, i, romBank, gen);
						}
						gen.emitOpCode(Operation.BMI, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.BEQ, AddressMode.ADDRESS, romBank, trueLabel, (byte)0, false);
						gen.emitOpCode(Operation.JMP, AddressMode.ADDRESS, romBank, falseLabel, (byte)0, false);
					}
				}
				break;
			default:
				error(String.format("Expected a comparison operator, found %s", t.getText()), line);
				break;
		}
	}
	
	private void assignLine(SourceLine line) {
		Reference target = expectReference(line);
		
		if(target == null) {
			return;
		}
		if(target.isConstant()) {
			error("Expected a variable reference, not a constant", line);
			return;
		}
		
		if(consume(line, TokenType.ASSIGN)) {
			Subroutine sub = consumeSubroutine(line);
			if(sub != null) {
				if(sub.getReturnVariable() == null) {
					error(String.format(
						"Subroutine %s does not have a return value",
						sub.getName()), line);
				} else {
					handleCall(line, sub);
					singleAssign(line, target,
						new Reference(sub.getReturnVariable(), false, false, 0));
				}
			} else {
				gen.emitSourceLine(line);
				handleAssign(line, target);
				expectEndOfLine(line);
			}
		} else if(consume(line, TokenType.ADDEQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.ADD);
			expectEndOfLine(line);
		} else if(consume(line, TokenType.SUBEQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.SUBTRACT);
			expectEndOfLine(line);
		} else if(consume(line, TokenType.SHIFTLEFTEQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.SHIFTLEFT);
			expectEndOfLine(line);
		} else if(consume(line, TokenType.SHIFTRIGHTEQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.SHIFTRIGHT);
			expectEndOfLine(line);
		} else if(consume(line, TokenType.ANDEQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.AND);
			expectEndOfLine(line);
		} else if(consume(line, TokenType.OREQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.OR);
			expectEndOfLine(line);
		} else if(consume(line, TokenType.EOREQUAL)) {
			gen.emitSourceLine(line);
			assignOp(line, target, TokenType.EOR);
			expectEndOfLine(line);
		} else {
			error("Expected an assignment operator", line);
			return;
		}
	}
	
	private void assignOp(SourceLine line, Reference target, TokenType op) {
		Reference rparm = expectReference(line);
		if(rparm == null) {
			error("Expected a value or expression", line);
			return;
		}
		doAssign(line, target, target, op, rparm);
	}
	
	private void singleAssign(SourceLine line, Reference target, Reference lparm) {
		int length = target.getWidth();
		if(length < lparm.getWidth()) {
			warn("Possible loss of precision", line);
		}
		for(int i = 0; i < length; ++i) {
			lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
			target.emitOpForByte(Operation.STA, i, romBank, gen);
		}
	}
	
	private void doAssign(SourceLine line, Reference target, Reference lparm,
		TokenType op, Reference rparm) {
		
		if(op == null || rparm == null) {
			singleAssign(line, target, lparm);
			return;
		}

		int length = target.getWidth();
		int calcLength = Math.max(lparm.getWidth(), rparm.getWidth());
		if(calcLength > length) {
			warn("Possible loss of percision", line);
		}
		
		switch(op) {
			case ADD:
				// See if we can optimize this into an increment
				if(target == lparm &&
					!target.isDereference() &&
					rparm.isConstant() &&
					rparm.getValue() == 1) {
					String doneLabel = gen.label();
					for(int i = 0; i < length; ++i) {
						target.emitOpForByte(Operation.INC, i, romBank, gen);
						if(i < length - 1) {
							gen.emitOpCode(Operation.BNE, AddressMode.ADDRESS,
								romBank, doneLabel, (byte)0, false);
						}
					}
					gen.emitLabel(romBank, doneLabel);
					break;
				}
				gen.emitOpCode(Operation.CLC, AddressMode.IMPLICIT, romBank,
					null, (byte)0, false);
				for(int i = 0; i < calcLength; ++i) {
					lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
					rparm.emitOpForByte(Operation.ADC, i, romBank, gen);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				for(int i = calcLength; i < length; ++i) {
					gen.emitOpCode(Operation.LDA, AddressMode.IMMEDIATE,
						romBank, null, (byte)0, false);
					if(i == calcLength) {
						gen.emitOpCode(Operation.ADC, AddressMode.IMMEDIATE,
							romBank, null, (byte)0, false);
					}
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				break;
			case SUBTRACT:
				// See if we can optimize this into a decrement
				if(target == lparm &&
					!target.isDereference() &&
					rparm.isConstant() &&
					rparm.getValue() == 1 &&
					target.getWidth() == 1) {
					target.emitOpForByte(Operation.DEC, 0, romBank, gen);
					break;
				}
				gen.emitOpCode(Operation.SEC, AddressMode.IMPLICIT, romBank,
					null, (byte)0, false);
				for(int i = 0; i < calcLength; ++i) {
					lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
					rparm.emitOpForByte(Operation.SBC, i, romBank, gen);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				for(int i = calcLength; i < length; ++i) {
					gen.emitOpCode(Operation.LDA, AddressMode.IMMEDIATE,
						romBank, null, (byte)0, false);
					if(i == calcLength) {
						gen.emitOpCode(Operation.SBC, AddressMode.IMMEDIATE,
							romBank, null, (byte)0, false);
					}
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				break;
			case AND:
				int left = Math.min(lparm.getWidth(), length);
				int right = Math.min(rparm.getWidth(), length);
				
				if(right < left) {
					int t = right;
					right = left;
					left = t;
				}
				for(int i = 0; i < left; ++i) {
					lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
					rparm.emitOpForByte(Operation.AND, i, romBank, gen);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				for(int i = left; i < length; ++i) {
					gen.emitOpCode(Operation.LDA, AddressMode.IMMEDIATE,
						romBank, null, (byte)0, false);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				break;
			case OR:
				left = Math.min(lparm.getWidth(), length);
				right = Math.min(rparm.getWidth(), length);
				
				Reference wider = lparm;
				Reference other = rparm;
				
				if(left < right) {
					wider = rparm;
					other = lparm;
				}
				
				for(int i = 0; i < Math.min(left, right); ++i) {
					wider.emitOpForByte(Operation.LDA, i, romBank, gen);
					other.emitOpForByte(Operation.ORA, i, romBank, gen);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
					
				}
				for(int i = Math.min(left, right); i < length; ++i) {
					wider.emitOpForByte(Operation.LDA, i, romBank, gen);
					target.emitOpForByte(Operation.STA, i, romBank, gen);						
				}
				break;
			case EOR:
				int validLength = Math.min(lparm.getWidth(), rparm.getWidth());
				for(int i = 0; i < validLength; ++i) {
					lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
					rparm.emitOpForByte(Operation.EOR, i, romBank, gen);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				for(int i = validLength; i < length; ++i) {
					gen.emitOpCode(Operation.LDA, AddressMode.IMMEDIATE,
						romBank, null, (byte)0, false);
					target.emitOpForByte(Operation.STA, i, romBank, gen);
				}
				break;
			case SHIFTLEFT:
			case SHIFTRIGHT:
				Operation firstShiftOp;
				Operation otherShiftOp;
				
				if(op == TokenType.SHIFTLEFT) {
					firstShiftOp = Operation.ASL;
					otherShiftOp = Operation.ROL;
				} else {
					firstShiftOp = Operation.LSR;
					otherShiftOp = Operation.ROR;
				}
				
				if(!rparm.isConstant()) {
					error("Shift operators may only be used with a constant right-hand parameter", line);
				} else {
					// Generate more efficient code for single-byte shifts
					if(lparm != target && lparm.getWidth() == 1 && target.getWidth() == 1) {
						lparm.emitOpForByte(Operation.LDA, 0, romBank, gen);
						for(int i = 0; i < rparm.getValue(); ++i) {
							gen.emitOpCode(firstShiftOp, AddressMode.IMPLICIT, romBank, null, (byte)0, true);
						}
						target.emitOpForByte(Operation.STA, 0, romBank, gen);
					// For all other shifts we do a copy then the shift in-place
					} else {
						// Copy the parameter into the target if needed
						if(lparm != target) {
							for(int i = 0; i < target.getWidth(); ++i) {
								lparm.emitOpForByte(Operation.LDA, i, romBank, gen);
								target.emitOpForByte(Operation.STA, i, romBank, gen);
							}
						}
						
						// And do the shift
						// FEATURE Consider rolling this into a loop
						for(int i = 0; i < rparm.getValue(); ++i) {
							for(int j = 0; j < target.getWidth(); ++j) {
								target.emitOpForByte(j == 0 ? firstShiftOp : otherShiftOp, j, romBank, gen);
							}
						}
					}
				}
				break;
			default:
				error("Expected a mathmatical operator", line);
				break;
		}
	}
	
	private void handleAssign(SourceLine line, Reference target) {
		if(target.isConstant()) {
			error("Expected a variable reference, not a constant", line);
			return;
		}
		
		Reference lparm = expectReference(line);
		if(lparm == null) {
			error("Expected a value or expression", line);
			return;
		}
		Reference rparm = null;
		Token op = line.peek();
		if(op != null && !op.isType(TokenType.COMMA)) {
			line.poll();
			
			rparm = expectReference(line);
			if(rparm == null) {
				return;
			}
		} else {
			op = null;
		}
		
		doAssign(line, target, lparm, op != null ? op.getType() : null, rparm);
	}
	
	private Reference constantReference(SourceLine line) {
		Token t = line.peek();
		if(t == null) {
			return null;
		}
		if(t.isType(TokenType.NUMBER)) {
			line.poll();
			return new Reference(parseInt(t.getText()));
		} else if(t.isType(TokenType.IDENTIFIER)) {
			Object o = resolveSymbol(t.getText());
			if(o instanceof Integer) {
				line.poll();
				return new Reference(((Integer)o).intValue());
			}
		}
		return null;
	}
	
	private Reference variableReference(SourceLine line) {
		Token t = line.peek();
		if(t == null) {
			return null;
		}
		if(t.isType(TokenType.IDENTIFIER)) {
			line.poll();
			String name = t.getText();
			Object o = resolveSymbol(name);
			if(o == null) {
				error(String.format("Unresolved symbol %s", name), line);
			} else if(o instanceof Variable) {
				return new Reference((Variable)o, false, false, 0);
			}
		}
		return null;
	}
	
	private Reference arrayReference(SourceLine line) {
		Reference v = variableReference(line);
		if(v == null) {
			return null;
		}
		if(v.getLength() > 1) {
			if(expect(line, TokenType.IDXOPEN) == null) {
				return null;
			}
			Reference ofs = constantReference(line);
			if(ofs == null) {
				ofs = variableReference(line);
			}
			if(ofs == null) {
				error("Expected constant or variable", line);
				return null;
			}
			if(ofs.getWidth() != 1) {
				error("Array index must be a byte value", line);
				return null;
			}
			if(ofs.isConstant()) {
				if(ofs.getValue() < 0 || ofs.getValue() >= v.getLength()) {
					error("Array index out of range", line);
					return null;
				}
			} else {
				if(ofs.getLength() > 1) {
					error("Array index must be a singular value", line);
					return null;
				}
			}
			v.setOffset(ofs);
			if(expect(line, TokenType.IDXCLOSE) == null) {
				error("Expected ']'", line);
				return null;
			}
		}
		return v;
	}
	
	private Reference addressReference(SourceLine line) {
		Token t = line.peek();
		if(t == null || !t.isType(TokenType.AT)) {
			return null;
		}
		line.poll();
		
		String name = expectIdentifier(line);
		if(name == null) {
			return null;
		}
		
		Object o = resolveSymbol(name);
		if(!(o instanceof Variable)) {
			return null;
		}
		
		return new Reference((Variable)o, true, false, 0);
	}
	
	private Reference derefReference(SourceLine line) {
		Token t = line.peek();
		if(t == null || !t.isType(TokenType.DEREFOPEN)) {
			return null;
		}
		line.poll();
		
		int derefWidth = 0;
		if(consume(line, TokenType.BYTE)) {
			derefWidth = 1;
		} else if(consume(line, TokenType.WORD) ||
			consume(line, TokenType.ADDRESS)) {
			derefWidth = 2;
		} else if(consume(line, TokenType.LONG)) {
			derefWidth = 3;
		} else if(consume(line, TokenType.DWORD)) {
			derefWidth = 4;
		}
		if(derefWidth == 0) {
			error("Expected type specifier", line);
			return null;
		}
		
		if(expect(line, TokenType.DEREFCLOSE) == null) {
			return null;
		}
		
		String name = expectIdentifier(line);
		if(name == null) {
			return null;
		}
		
		Object o = resolveSymbol(name);
		if(!(o instanceof Variable)) {
			error("Expected variable reference", line);
			return null;
		}
		
		Variable v = (Variable)o;
		if(v.getType() != TokenType.ADDRESS) {
			error("Attempt to dereference a non-address variable", line);
			return null;
		}
		
		Reference deref = new Reference(v, false, true, derefWidth);
		
		// Handle offset if needed
		if(consume(line, TokenType.IDXOPEN)) {
			Reference ofs = constantReference(line);
			if(ofs == null) {
				error("Expected constant pointer offset", line);
				return null;
			}
			if(ofs.getWidth() > 1 ||
				ofs.getByte(0) + derefWidth > 256) {
				error("Pointer offset plus dereference width must be a " +
					"byte value", line);
				return null;
			}
			deref.setOffset(ofs);
			if(expect(line, TokenType.IDXCLOSE) == null) {
				error("Expected ']'", line);
				return null;
			}
		}
		
		return deref;
	}
	
	private Reference expectReference(SourceLine line) {
		Reference v = constantReference(line);
		if(v == null) {
			v = arrayReference(line);
		}
		if(v == null) {
			v = addressReference(line);
		}
		if(v == null) {
			v = derefReference(line);
		}
		if(v == null) {
			error("Expected a constant, variable, array or address reference",
				line);
		}
		return v;
	}
	
	private String expectIdentifier(SourceLine line) {
		Token t = expect(line, TokenType.IDENTIFIER);
		if(t == null) {
			return null;
		}
		if(t.getText().contains(".")) {
			error("Identifiers may not contain the dot character", line);
		}
		return t.getText();
	}
	
	private String expectQuotedString(SourceLine line) {
		Token t = expect(line, TokenType.QUOTEDSTRING);
		if(t == null) {
			return null;
		}
		return t.getText();
	}
	
	private int parseInt(String text) {
		text = text.toLowerCase();
		if(text.startsWith("$") && text.length() > 1) {
			return (int)Long.parseLong(text.substring(1), 16);
		}
		if(text.startsWith("%") && text.length() > 1) {
			return (int)Long.parseLong(text.substring(1), 2);
		}
		if(text.startsWith("0x") && text.length() > 2) {
			return (int)Long.parseLong(text.substring(1), 16);
		}
		if(text.startsWith("0b") && text.length() > 2) {
			return (int)Long.parseLong(text.substring(1), 2);
		}
		return (int)Long.parseLong(text, 10);
	}
	
	private boolean variableLine(SourceLine line, TokenType type, int width) {
		// Handle modifiers
		boolean extern = false;
		boolean fast = type == TokenType.ADDRESS;
		while(true) {
			if(consume(line, TokenType.EXPORT)) {
				extern = true;
				continue;
			}
			if(consume(line, TokenType.FAST)) {
				fast = true;
				continue;
			}
			break;
		}
		
		// Get the type if needed
		CompositeType composite = null;
		Token t;
		Object o;
		if(type == null) {
			t = expect(line, TokenType.IDENTIFIER);
			if(t == null) {
				return false;
			}
			
			o = resolveSymbol(t.getText());
			if(o == null || !(o instanceof CompositeType)) {
				error("Expected a type identifier", line);
				return false;
			}
			
			composite = (CompositeType)o;
		} else {
			expect(line, type);
		}
		
		// Get name
		t = expect(line, TokenType.IDENTIFIER);
		if(t == null) {
			return false;
		}
		String name = t.getText();
		if(currentSubroutine != null) {
			name = currentSubroutine.getName() + "$" + name;
		}
		
		// See if a length was given
		int length = 1;
		if(consume(line, TokenType.IDXOPEN)) {
			length = constant(line);
			if(length < 1 || length > 256) {
				error("Invalid array length", line);
				length = 256;
			}
			expect(line, TokenType.IDXCLOSE);
		}
		expectEndOfLine(line);
		
		// Add variable(s) to namespace and generate code
		if(composite != null) {
			for(CompositeType.Member m : composite.getMembers().values()) {
				Variable var = new Variable(line, name + "." + m.getName(),
					m.getType(), length, 0, true, fast ? 0 : ramBank);
				addVariableSymbol(line, var, extern);
			}
		} else {
			Variable var = new Variable(line, name, type, length, 0, true,
				fast ? 0 : ramBank);
			addVariableSymbol(line, var, extern);
		}
		
		return true;
	}
	
	private int constant(SourceLine line) {
		Token t = line.poll();
		if(t == null) {
			error("Unexpected end of line", line);
		} else if(t.isType(TokenType.NUMBER)) {
			return parseInt(t.getText());
		} else if(t.isType(TokenType.IDENTIFIER)) {
			Object o = resolveSymbol(t.getText());
			if(o instanceof Integer) {
				return ((Integer)o).intValue();
			} else {
				error("Expected a number or constant reference", line);
			}
		} else {
			error(String.format("Expected a number, found %s", t.getText()), line);
		}
		return 0;
	}
	
	private boolean consume(SourceLine line, TokenType type) {
		Token t = line.peek();
		if(t != null && t.isType(type)) {
			line.poll();
			return true;
		}
		return false;
	}
	
	private Token expect(SourceLine line, TokenType type) {
		Token t = line.poll();
		if(t == null) {
			error("Unexpected end of line", line);
			return null;
		} else if(!t.isType(type)) {
			error(String.format("Expected %s but found %s",
				Token.nameForType(type),
				Token.nameForType(t.getType())), line);
			return null;
		}
		return t;
	}
	
	private void expectEndOfLine(SourceLine line) {
		Token t = line.poll();
		if(t != null) {
			error(String.format("Expected end of line, found %s", Token.nameForType(t.getType())), line);
		}
	}
	
	private void romLine(SourceLine line) {
		if(expect(line, TokenType.ROM) == null) {
			return;
		}
		romBank = constant(line);
		expectEndOfLine(line);
	}
	
	private void ramLine(SourceLine line) {
		if(expect(line, TokenType.RAM) == null) {
			return;
		}
		ramBank = constant(line);
		expectEndOfLine(line);
	}
}
