@echo off 

IF "%~1"=="debug"  (
    echo "Packaging debug..." && copy bin\libs-win bin\ && make Debug -j4 -s && make RunDebug
)


IF "%~1"=="release"  (
    echo "Packaging RELEASE..." && copy bin\libs-win bin\ && make -j4 -s && make RunRelease
)
