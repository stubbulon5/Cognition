# Cognition

Source code for Cognition (Bloom, Working title) Music Composition application written on top of the awesome [openFrameworks](https://openframeworks.cc/)

## Set-up
### The openFrameworks setup guides reside [here](https://openframeworks.cc/download/)


### Project code:
Must be cloned to a folder named "Cognition" due to the VSCode build environment. ie
This folder should reside in /<OF_ROOT>/apps/myApps/Cognition
also, with MSYS2, the new version of C:\msys64\usr\bin\make.exe is incompatible. Downgrading to 4.2.1 fixes. (find in bin\resources\win\make.exe)
also, sometimes the Debug build does not run properly, bur release is fine.

```
git clone git@bitbucket.org:stubbulon5/cognition.git Cognition
```

This is the platform independent /src code folder which is shared across platform specific build setups (ie Windows, macOS, Linux)

and the addons folder should reside in /<OF_ROOT>/addons
```
git clone git@bitbucket.org:stubbulon5/cognition-ofx-addons.git addons
```


## Build
There is a corresponding build script for each platform:
```
./makeLinux.sh -r <debug|release>
./makeMacOs.sh -r <debug|release>
and
makeWin.bat <debug|release>
```

VSCode is the ideal IDE for use too see .vscode/tasks.json), simply hitting ctrl-shift-b will bring up the build command palette with build choices.


as well as packaging up for distribution:
```
./makeLinux_INSTALLER.sh
./makeMacOs_INSTALLER.sh
and
// Make sure to run setx PATH "c:\msys64\mingw64\bin;c:\msys64\usr\bin;%PATH%" in an Admin comd prompt first
makeWin_INSTALLER.bat
```

# Vst3
Minimum of c++ 14 compiler required otherwise make_unique, etc other macros fail. To fix / change in OF:
libs/openFrameworksCompiled/project/osx/config.osx.default.mk line 132: PLATFORM_CXXFLAGS += -std=c++11 -> -std=c++14

# FluidSynth
FluidSynth is an (aweseome) cross-platform, real-time software synthesizer based on the Soundfont 2 specification. 
Repo here : https://github.com/FluidSynth/fluidsynth

This application uses ofxFluidSynth Openframeworks addon.
Steps to update / recompile the libs for ofxFluidSynth  (in the event of new release):
```
1.) git clone git@github.com:FluidSynth/fluidsynth.git
2.) Read the corresponding OS's build instructions here: https://github.com/FluidSynth/fluidsynth/wiki/BuildingWithCMake#common-tips-for-compiling-from-source

https://github.com/FluidSynth/fluidsynth/wiki/BuildingWithCMake

MACOS
    $ cd fluidsynth-x.y.z/
    $ mkdir build
    $ cd build
    $ cmake -Denable-framework=OFF ..
Now run make:
    $  make VERBOSE=1

    now copy build/src/libfluidsynth.x.y.z.dylib

LINUX
------
    $ cd fluidsynth-x.y.z/
    $ mkdir build
    $ cd build
    $ cmake ..
Now run make:
    $  make VERBOSE=1

3.) Now copy the includes into the ofxFluidSynth addon 

a.) copy the fluidsynth-x.y.z/fluidsynth/include/fluidsynth folder to <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/fluidsynth
b.) Copy the fluidsynth.h header from fluidsynth/cmake_admin/include/fluidsynth.h to <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/fluidsynth
c.) Copy the version.h header from fluidsynth/cmake_admin/include/fluidsynth/version.h into <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/fluidsynth folder

d.) Copy the binary / lib fluidsynth/cmake_admin/src/libfluidsynth.so.2 to <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/lib/linux64 (if it's a linux system, change accordingly for macOS and win)

e.) Finally, we MUST include the library in our distribution, so *also* copy fluidsynth/cmake_admin/src/libfluidsynth.so.2 to the cognition bin/libs folder eg : <OPENFRAMEWORKS_FOLDER>/apps/myApps/bloom/bin/libs


macOS
------

In project root, 

To enable Tracy profiler:
Change /of_v0.10.1_osx_release/libs/openFrameworksCompiled/project/osx/config.osx.default.mk
PLATFORM_CXXFLAGS += -std=c++11 -> PLATFORM_CXXFLAGS += -std=c++14



-----> TODO : Make it dynamically linked!!


    $ cd fluidsynth-x.y.z/
    $ mkdir build
    $ cd build
    $ cmake -Denable-framework=OFF -Denable-portaudio=OFF -Denable-libsndfile=ON ..
Now run make:
    $  make VERBOSE=1


    
3.) Now copy the includes into the ofxFluidSynth addon 

a.) copy the fluidsynth-x.y.z/fluidsynth/include/fluidsynth folder to <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/fluidsynth/fluidsynth
b.) Copy the fluidsynth.h header from fluidsynth/build/include/fluidsynth.h to <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/fluidsynth
c.) Copy the version.h header from fluidsynth/build/include/fluidsynth/version.h into <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/fluidsynth folder

d.) Copy the binary / lib fluidsynth/cmake_admin/src/libfluidsynth.2.dylib to <OPENFRAMEWORKS_FOLDER>/addons/ofxFluidSynth/libs/lib/linux64 (if it's a linux system, change accordingly for macOS and win)

e.) Finally, we MUST include the library in our distribution, so *also* copy fluidsynth/cmake_admin/src/libfluidsynth.2.dylib to the cognition bin/libs folder eg : <OPENFRAMEWORKS_FOLDER>/apps/myApps/bloom/bin/libs
```

WINDOWS
Building with MSYS2 on Windows (mingw32.exe) :
Follow instructions: https://github.com/FluidSynth/fluidsynth/wiki/BuildingWithCMake#building-with-msys2-on-windows


# Documentation setup (Doxygen and GraphViz)
Instructions followed from https://www.youtube.com/watch?v=LZ5E4vEhsKs
Install tools:
```
sudo apt-get install doxygen
sudo apt-get install graphviz
```
Edit doc/Doxyfile

# App Documentation
``` 
cd doc/ && doxygen && x-www-browser file://`pwd`/html/index.html && cd ..
```

# Aquamarine UI Documentation
``` 
cd src/uiViz/doc/ && doxygen && x-www-browser file://`pwd`/html/index.html && cd ../../../
```

# Performance Profiling
``` 
source /opt/intel/vtune_amplifier_2019/amplxe-vars.sh && /opt/intel/vtune_amplifier_2019/bin64/amplxe-gui --path-to-open bin/profiling/Cognition/Cognition.amplxeproj
``` 



elm colors
todo clear hover (it alpha transitionaing)
cursor navigation with table plus enter het for select

