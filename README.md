nesicide is an Integrated Development Environment (IDE) for the 8-bit Nintendo Entertainment System (NES).

This fork is a try to maintain and compile on recent computer. ATM tests and best effort are pushed to the Linux version/compilation.

## Products in Project

This project contains the following products:

* NESICIDE : the IDE itself
* A NES emulator : standalone package of the emulator used in the IDE
* FamiTracker : a fork of jsr's FamiTracker
* FamiPlayer : a music player for .ftm files

## Prerequisites

The following steps are required prior to building this project on any platform.

0. Install `git`
1. Install [Qt 5.12.6](http://download.qt.io/archive/qt/5.12/5.12.6/) as it was the latest kit to be verified to build NESICIDE properly without errors.
   TODO : testing to v5.12.12
2. Make sure qmake and your Qt installation is in your PATH.


### Debian prerequisites

```sh
sudo apt-get install qtchooser build-essential libasound2-dev liblua5.1-dev libsdl1.2-dev libgl1-mesa-dev 
```

### Arch Linux prerequisites

```sh
sudo pacman -S lua sdl mesa wine
```

### Windows prerequisites

Install [GnuWin32](https://sourceforge.net/projects/getgnuwin32/) and [wget](http://gnuwin32.sourceforge.net/packages/wget.htm).

## Building

This project builds for Linux, macOS, and Windows. To perform a build for any supported platform follow the instructions for the platform below.

`NOTE: The build process takes a while, so grab a snack while you wait. ;)`

### Linux (work in progress)

0. `./build/linux-build.sh`
1. `./build/linux-deploy.sh local`

### macOS (outdated and untested)
At the time of writing this, MacOS Homewbrew contains Qt 5.14.1, and NESICIDE can also be built with that version of Qt. 
So, alternatively, you can install Qt using :

   ```
   brew intall qt5
   ```
If you installed Qt from Homebrew, you need to set the following environment variable, so that the build process can find qmake (the qt5 Homebrew formula is keg-only):

```
PATH="/usr/local/opt/qt/bin:$PATH"
```

0. `./build/osx-build.sh`
1. `./build/osx-deploy.sh local`

### Windows (outdated and untested)

NOTE: The build process uses GnuWin32 tools and MinGW tools. Install these and make sure that `mingw32-make` and `wget` are on your path.

0. `./build/windows-build.sh`
1. `./build/windows-deploy.sh local`

## Running

The `deploy.sh` creates artifacts of the following form.

### Linux

Separate AppImage executables for each product of the project. See https://appimage.org/ for information on AppImage containers.

### macOS

Separate Apple Disk Images (DMGs) for each product of the project.

### Windows

Monolithic bzipped tarball containing all products of the project, extractable to anywhere.

Enjoy!
