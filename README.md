Modest attempts to make Integrated Development Environment for the 8-bit Nintendo Entertainment System alive again. 

This fork is a try to maintain and compile on recent computer in Windows10/11 with Visual Studio 2022.

## Products in Project

This project contains the following products:

* nesicide-vs : the IDE itself
* a NES emulator : standalone package of the emulator used in the IDE
* Dn-FamiTracker : the maintained fork of jsr's FamiTracker => https://github.com/Dn-Programming-Core-Management/Dn-FamiTracker
* FamiPlayer : a music player for .ftm files
* qhexedit
* qscintilla2
* rtmidi
* c64-emulator
* cc65 compilator


2. Make sure qmake and your Qt installation is in your PATH.


### Windows prerequisites

* *Install Visual Studio 2022 with the following components:
* Qt Visual Studio Tools
* *C++/CLI support
* *MFC and ATL support
* *Windows 10 SDK (10.0.19041.0)
* Install `git`
* Install [Qt 5.12.12](http://download.qt.io/archive/qt/5.12/5.12.12/) 


## Building

This goal of this project is to generate a running build for Windows10 in Visual Studio 2022.
Open the vxproj file in the root of the project and build the solution.



`NOTE: The build process takes a while, so grab a snack while you wait. ;)`



