# Cognition

Source code for Cognition - Music Visualization application written on top of the awesome [openFrameworks](https://openframeworks.cc/) and using my UI Framework passion project ofxAquamarine.

## Set-up
### The openFrameworks setup guides reside [here](https://openframeworks.cc/download/)


### Project code:
Must be cloned to a folder named "Cognition" due to the VSCode build environment. ie
This folder should reside in /<OF_ROOT>/apps/myApps/Cognition
also, with MSYS2, the new version of C:\msys64\usr\bin\make.exe is incompatible. Downgrading to 4.2.1 fixes. (find in bin\resources\win\make.exe)
also, sometimes the Debug build does not run properly, bur release is fine.

```
git clone git@github.com:stubbulon5/Cognition.git
```

This is the platform independent /src code folder which is shared across platform specific build setups (ie Windows, macOS, Linux)

and the addons folder should reside in /<OF_ROOT>/addons
```
git clone git@github.com:stubbulon5/Cognition-addons.git addons
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


Packaging up for distribution:
```
./makeLinux_INSTALLER.sh
./makeMacOs_INSTALLER.sh
and
// Make sure to run setx PATH "c:\msys64\mingw64\bin;c:\msys64\usr\bin;%PATH%" in an Admin comd prompt first
makeWin_INSTALLER.bat
```

# Documentation setup (Doxygen and GraphViz)
Instructions followed from https://www.youtube.com/watch?v=LZ5E4vEhsKs
https://www.doxygen.nl/manual/starting.html
Install tools:
```
# macOs
brew install doxygen
brew install graphviz

# Linux
 sudo apt-get install doxygen
 sudo apt-get install graphviz
 ```

# Generate App Documentation
``` 
cd doc/ && doxygen && x-www-browser file://`pwd`/html/index.html && cd ..
```


# Generate  Aquamarine UI Documentation
``` 
cd src/uiViz/doc/ && doxygen && x-www-browser file://`pwd`/html/index.html && cd ../../../
```