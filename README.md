Modest attempts to make Integrated Development Environment for the 8-bit Nintendo Entertainment System alive again. 

This fork is a modest try to compile the NESICIDE project on recent computer in Windows10/11 with Visual Studio 2022 (with some code cleaning and bug fixing).

## Products in Project

This project contains the following products :

* nesicide-vs : the IDE itself :)
* a NES emulator : standalone package of the emulator used in the IDE, from the original project => https://github.com/christopherpow/nesicide
* Dn-FamiTracker : the maintained fork of jsr's FamiTracker => https://github.com/Dn-Programming-Core-Management/Dn-FamiTracker
* FamiPlayer : a music player for .ftm files
* qhexedit
* qscintilla2
* rtmidi
* c64-emulator
* cc65 compilator

### Windows prerequisites

* Install Visual Studio 2022 with the following components :
* Qt Visual Studio Tools
* C++/CLI support
* MFC support
* Windows 10 SDK (10.0.19041.0)
* Install `git`
* Install [Qt 5.12.12](http://download.qt.io/archive/qt/5.12/5.12.12/) and make sure qmake and your Qt installation is in your PATH.


## Building

0. Clone the repository.
1. Open the vxproj file in the root of the project.
2. Generate the whole solution :D
3. If you have fingers, cross them.

`NOTE : It won't compile yet`






