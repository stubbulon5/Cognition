
#!/bin/bash

set -e

while getopts ":r:" opt; do
  case $opt in
    r) r="$OPTARG"
    ;;
    \?) echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done

#    sudo killall Dock && sudo killall Finder && \   
#     touch bin/Cognition_debug.app && \  
#    cp bin/resources/macOS/cognition.icns bin/Cognition_debug.app/Contents/Resources/Cognition_debug.icns && \  
#    


if [ "$r" == "debug" ]
then
    echo "Packaging debug..."
    make Debug -j8 -s 2>&1 && \
    unzip bin/libs-macOS/libs.zip -d bin/Cognition_debug.app/Contents/ && \
    install_name_tool -change @rpath/libfluidsynth.3.dylib @executable_path/../libs/libfluidsynth.3.dylib ./bin/Cognition_debug.app/Contents/MacOS/Cognition_debug && \
    cp bin/libs-macOS/misc/Info.plist.debug bin/Cognition_debug.app/Contents/Info.plist && \
    make RunDebug || exit 1
 
# BIG SUR FIX (until of 0.11.1 release!) ---------------------------------
# https://forum.openframeworks.cc/t/building-in-macos-11-0-big-sur/36581/5

 #     cp bin/resources/macOS/cognition.icns bin/Cognition.app/Contents/Resources/Cognition.icns && \
elif [ "$r" == "release" ]
then
    echo "Packaging release..."
    make -j8 -s 2>&1 && \
    unzip bin/libs-macOS/libs.zip -d bin/Cognition.app/Contents/ && \
    cp bin/libs-macOS/misc/Info.plist bin/Cognition.app/Contents/ && \
    cp bin/resources/macOS/cognition.icns bin/Cognition.app/Contents/Resources/ && \
    install_name_tool -change @rpath/libfluidsynth.3.dylib @executable_path/../libs/libfluidsynth.3.dylib ./bin/Cognition.app/Contents/MacOS/Cognition && \
    make RunRelease
else
    echo "Did not do anything..."
fi

