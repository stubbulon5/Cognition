# Dynamically Linked libraries

Dynamic linking proved to be tricky, esp with Fluidsynth.
https://blog.krzyzanowskim.com/2018/12/05/rpath-what/

https://medium.com/@donblas/fun-with-rpath-otool-and-install-name-tool-e3e41ae86172

You can check how libraries are linked by using otool, eg:
```
otool -L bin/Cognition_debug.app/Contents/MacOS/Cognition_debug
```


The currently working version is 2.0.7, when I tried 2.0.8, it crashed the app (problems with CoreAudio driver).

How to package Fluidsynth so that app will run as a standalone with all required dylibs bundled:


1.) Build your project to create bundle resulting in <OF_FOLDER>/apps/myApps/<YOUR_APP>/bin/<YOUR_APP>_debug
2.) Browse to the app path in a terminal: eg cd <OF_FOLDER>/apps/myApps/<YOUR_APP>
3.) Now we need to temporarily copy libs to the absolute /tmp path:
```
    cp ../../../addons/ofxFluidSynth/libs/lib/osx/libfluidsynth.3.0.2.dylib /tmp/libfluidsynth.3.dylib 
    cp bin/Cognition.app/Contents/MacOS/libfmodex.dylib /tmp/libfmodex.dylib
    unzip bin/libs-macOS/libs.zip -d 


```
4.) Now run the tool to bundle the libraries with your app: 
```
    sudo ./bin/libs-macOS/dylibbundler -cd -od -b -x ./bin/Cognition.app/Contents/MacOS/Cognition -d ./bin/Cognition.app/Contents/libs2 -p @executable_path/../libs/
```
5.) The tool will ask you where to locate  libfluidsynth.3.dylib and libfmodex.dylib reply with /tmp or /tmp/lib every time (it asks roughly 10 times). 

Finally! Your app will run as a standalone with all required dylibs bundled. (see the libs2 folder... all "fixed" these files must be added the the libs-macOS/libs.zip file)

helpful tip - when doing all of this and building the executable do NOT run the
```
install_name_tool -change @rpath/libfluidsynth.3.dylib @executable_path/../libs/libfluidsynth.3.dylib ./bin/Cognition.app/Contents/MacOS/Cognition && \
``` part of makeMacOs.sh - it messes with the dylibbundler (just temporarily comment it)


# Pre-zipped, for convenience
The above steps, containing version  libfluidsynth.3.0.2.dylib  (release 3.0.2) have been carried out, and the resulting files zipped into ./libs.zip

This makes it super easy to unzip them directly into your app right after your build. eg:
```
$ make Debug
$ unzip bin/libs-macOS/libs.zip <OF_FOLDER>/apps/myApps/<YOUR_APP>/bin/<YOUR_APP>_debug/Contents
$ install_name_tool -change @rpath/libfluidsynth.2.dylib @executable_path/../libs/libfluidsynth.2.dylib ./bin/<YOUR_APP>.app/Contents/MacOS/<YOUR_APP> 
```

BEar in mind, the last step (install_name_tool) is vital, otherwise the app simply will not link to Fluidsynth!