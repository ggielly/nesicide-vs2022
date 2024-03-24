#! /bin/bash

# My make for uc65 projects

# Outputs the usage information
function help {
	cat <<ENDFILE
Usage: make.sh target [mmu]
  target       The target system, I.E. 'nes'
  mmu          The target memory model, I.E. 'nrom'

This command will compile all .uc files in the current directory and all
subdirectories along with any .uc files in the library directory for the named
target system and memory model, then assemble and link them all together.

ENVIRONMENT VARIABLES
  BUILD_DIR    The directory to place intermediate files, defaults to "../build"
  OUT_PATH     The output file name. The default value is dependant on the
               target system, and will be in the directory "../"
  UC65_HOME    The home directory for uc65, defaults to the directory containing
               this script
  CC65_BIN     The binary directory for cc65, defaults to "\$UC65_HOME/cc65"
  LIB_ROM      ROM bank for libraries, defaults to 0
  LIB_RAM      RAM bank for libraries, defaults to 1
ENDFILE
}

# Environment variable defaults
if [[ -z "$BUILD_DIR" ]]; then
	BUILD_DIR="../build"
fi
if [[ -z "$UC65_HOME" ]]; then
	UC65_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
fi
if [[ -z "$CC65_BIN" ]]; then
	CC65_BIN="$UC65_HOME/cc65"
fi
if [[ -z "$LIB_ROM" ]]; then
	LIB_ROM=0
fi
if [[ -z "$LIB_RAM" ]]; then
	LIB_RAM=1
fi

# Argument handling
if [[ -n "$3" ]]; then
	help
	exit 1
elif [[ "$1" == "?" || "$1" == "-h" || "$1" == "--help" ]]; then
	help
	exit 0
elif [[ -z "$1" ]]; then
	help
	exit 1
fi
TARGET="$1"
if [[ -z "$OUT_PATH" ]]; then
	case "$TARGET" in
		"nes")
			OUT_PATH="../out.nes"
			;;
		*)
			echo "Unrecognized target system $1"
			exit 9
			;;
	esac
fi
MMU="$2"
TARGET_DIR="$UC65_HOME/lib/$TARGET"
MMU_DIR="$TARGET_DIR/$MMU"
UC_FLAGS="-i $TARGET_DIR -c librom=$LIB_ROM -c libram=$LIB_RAM"
LD_FLAGS="-C $MMU_DIR/memory.cfg -m $BUILD_DIR/build.map"
if [[ -n "$OUT_PATH" ]]; then
	LD_FLAGS="-o $OUT_PATH $LD_FLAGS"
fi

# Argument validation
if [[ ! -d "$BUILD_DIR" ]]; then
	mkdir -p "$BUILD_DIR"
	if (( $? != 0 )); then
		exit 2
	fi
fi
if [[ ! -d "$UC65_HOME" ]]; then
	echo "UC65_HOME Directory does not exist" >&2
	exit 3
fi
if [[ ! -d "$CC65_BIN" ]]; then
	echo "CC65_BIN Directory does not exist" >&2
	exit 4
fi
if [[ ! -d "$TARGET_DIR" ]]; then
	echo "Target does not exist" >&2
	exit 5
fi
if [[ ! -d "$MMU_DIR" ]]; then
	echo "MMU does not exist" >&2
	exit 6
fi
CA="$CC65_BIN/ca65"
if [[ ! -e "$CA" ]]; then
	CA="$CA.exe"
fi
if [[ ! -e "$CA" ]]; then
	echo "Unable to locate assembler"
	exit 7
fi
LD="$CC65_BIN/ld65"
if [[ ! -e "$LD" ]]; then
	LD="$LD.exe"
fi
if [[ ! -e "$LD" ]]; then
	echo "Unable to locate linker"
	exit 8
fi

# Source compilation
for fname in $(find ./ "$TARGET_DIR" "$MMU_DIR" -name "*.uc"); do
	outfile=$(echo "$fname" | md5sum | cut -f1 -d" ")
	outfile="$BUILD_DIR/$outfile.s"
	java -jar "$UC65_HOME/uc65.jar" $UC_FLAGS -o "$outfile" "$fname"
	if (( $? != 0 )); then exit 10; fi
done

# Suck up assembly source files to compile
find ./ $BUILD_DIR -name "*.s" > $BUILD_DIR/build.lst
ls -1 $TARGET_DIR/*.s >> $BUILD_DIR/build.lst 2>/dev/null
if [[ "$TARGET_DIR" != "$MMU_DIR" ]]; then
	ls -1 $MMU_DIR/*.s >> $BUILD_DIR/build.lst 2>/dev/null
fi

# Assembly
for fname in $(cat $BUILD_DIR/build.lst); do
	outfile=$(echo "$fname" | md5sum | cut -f1 -d" ")
	outfile="$BUILD_DIR/$outfile.o"
	"$CA" -o "$outfile" "$fname"
	if (( $? != 0 )); then exit 11; fi
done

# Linkage
"$LD" $LD_FLAGS $BUILD_DIR/*.o
if (( $? != 0 )); then exit 12; fi

