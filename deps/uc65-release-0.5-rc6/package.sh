#! /bin/bash

svnUri=http://uc65.googlecode.com/svn/trunk/

if [[ -z "$1" ]]; then
  cat <<ENDFILE
Usage: $0 name_of_release

Automates the export and packaging of the uc65 project for a release. uc65.jar
should be pre-exported in the current directory. Yes, I'm that lazy :)
ENDFILE
  exit 1
fi

rm -rf dist
svn export "$svnUri" dist
cp uc65.jar dist
cd dist
zip -r "uc65-$1.zip" *
mv "uc65-$1.zip" ../
cd ..

