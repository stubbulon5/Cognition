
Singular sound use VERSION: 3.4.1 right now for the Aeros, so I will use that version for this example:


For release VERSION: 3.4.1 manually download the Zip here:
https://github.com/protocolbuffers/protobuf/releases/tag/v3.4.1


Then follow installation instructions to build / install:
https://github.com/protocolbuffers/protobuf/blob/master/src/README.md

Then copy the lib files to the add-on folder (for example, on a Mac it these are the locations):
cp  /usr/local/lib/libprotobuf.a <OFX_ADDONS_FOLDER>/ofxProtobuf/libs/lib/osx/
cp  /usr/local/lib/libprotobuf-lite.a <OFX_ADDONS_FOLDER>/ofxProtobuf/libs/lib/osx/


<OFX_ADDONS_FOLDER> = openFrameworks adding folder



Windows
------------
