#! /bin/bash

# Utility build script for example code
# Should be superseded by build automation utility in release 0.6

uc65path="../../../uc65.jar"
uc65cmd="java -jar $uc65path"
cc65dir="../../../cc65/"
ca65cmd="$cc65dir/ca65.exe -g"
ld65cmd="$cc65dir/ld65.exe -vm"
libdir="../../../lib/"

fail=0

if [[ -z "$2" ]]; then
	cat <<ENDFILE
Usage: $0 platform example

Builds the named example program for the named platform.

Example: $0 nes simple
ENDFILE
	exit 1
fi

libdir="$libdir/$1/"

sourcedir="./$1/$2"
if [[ "$1" == "nes" ]]; then
	outfile="../$2.nes"
else
	echo "Unrecognized platform $1"
	exit 2
fi

cd "$sourcedir"
for file in *.uc; do
	$uc65cmd -i "$libdir" "$file"
	if (( $? != 0 )); then fail=1; fi
done
if (( fail > 0 )); then exit 3; fi

$ca65cmd "../../../lib/crt0.s"
if (( $? != 0 )); then fail=1; fi
for file in *.s; do
	$ca65cmd "$file"
	if (( $? != 0 )); then fail=1; fi
done
if (( fail > 0 )); then exit 4; fi

$ld65cmd -o "$outfile" -m "$outfile.map" -C "../../../lib/memory.cfg" "../../../lib/crt0.o" *.o
if (( $? != 0 )); then exit 5; fi

