@echo off 

echo "------------------ CREATING INSTALLER (Windows) ------------------"

echo " Setting Icon using rcedit: https://github.com/electron/rcedit"
bin\resources\win\rcedit-x64 "bin\Cognition.exe" --set-icon "bin\resources\win\cognition.ico"

echo "Using NSIS: Nullsoft Scriptable Install System: https://sourceforge.net/projects/nsis/"
"c:\Program Files (x86)\NSIS\makensis.exe" bin\resources\win\installer.nsi
