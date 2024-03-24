#!/bin/bash

# check for deps
echo -n "Checking for dependencies package..."
if [ ! -d "deps" ]; then
   echo "Fetching dependencies package..."
   curl -fsS -o nesicide-deps.tar.bz2 https://knob.phreneticappsllc.com/nesicide/nesicide-deps.tar.bz2 --insecure
   echo "Extracting dependencies package..."
   tar --checkpoint=100 --checkpoint-action=dot -xjf nesicide-deps.tar.bz2
   rm -f nesicide-deps.tar.bz2
else
   echo "found."
fi
# add CONFIG+=debug to qmake to build debug.
echo Building NESICIDE...
( cd build/ide; qmake; mingw32-make )
echo Building FamiTracker...
( cd build/famitracker; qmake; mingw32-make )
echo Building FamiPlayer...
( cd build/famiplayer; qmake; mingw32-make )
echo Building NES Emulator...
( cd build/nes-emulator; qmake; mingw32-make )
