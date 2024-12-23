# Cognition

Hey there :-) Cognition is a Music Theory Visualization application written on top of the awesome [openFrameworks](https://openframeworks.cc/) and using my UI Framework passion project [ofxAquamarine](https://github.com/stubbulon5/ofxAquamarine). This is a sole development, but I welcome collaboration and input from music enthusiasts! 

Have a feature request? You can maybe tempt me with coffee :-) [Buy me a coffee!](buymeacoffee.com/stubbulon5)

## Project set up
VSCode is the IDE of choice, but feel free to use your own, though please note, all instructions are written based on the assumption that VSCode is being used. 
- Install openFrameworks. The openFrameworks setup guides reside [here](https://openframeworks.cc/download/)
- Clone the [Cognition](https://github.com/stubbulon5/Cognition) repo to `/<OF_ROOT>/apps/myApps/` folder (ie. `of_v0.12.0_osx_release/apps/myApps/Cognition`)
- Clone the [Cognition-addons](https://github.com/stubbulon5/Cognition-addons) repo to `/<OF_ROOT>/apps/addons/` folder (ie. `of_v0.12.0_osx_release/addons`)

## Build it!
There is a corresponding build script for each platform:
```
./makeLinux.sh -r <debug|release>
./makeMacOs.sh -r <debug|release>
and
makeWin.bat <debug|release>
```

## A word on setup and Intellisense
Using macOs, set `"compilerPath": "/usr/bin/clang"`, the inside the `.vscode/c_cpp_properties.json`. 

I found this to be the most stable, but it's not perfect!


## Packaging up for distribution:
```
./makeLinux_INSTALLER.sh
./makeMacOs_INSTALLER.sh
and
// Make sure to run setx PATH "c:\msys64\mingw64\bin;c:\msys64\usr\bin;%PATH%" in an Admin comd prompt first
makeWin_INSTALLER.bat
```

## Documentation setup (Doxygen and GraphViz)
Install tools:
```
# macOs
brew install doxygen
brew install graphviz

# Linux
sudo apt-get install doxygen
sudo apt-get install graphviz
 ```

## Generate App Documentation
``` 
cd doc/ && doxygen && x-www-browser file://`pwd`/html/index.html && cd ..
```
