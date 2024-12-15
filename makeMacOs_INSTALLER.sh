
#!/bin/bash

APP_NAME="Cognition"

echo "------------------ CREATING '${APP_NAME}' INSTALLER (DMG) ------------------"
rm -rf bin/${APP_NAME}.app/Contents/MacOS/data
mkdir bin/${APP_NAME}.app/Contents/MacOS/data 
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/content
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/fonts 
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/ui
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/ui/images
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/ui/svg
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/ui/widgets
mkdir bin/${APP_NAME}.app/Contents/MacOS/data/ui/widgetHelp


# Copy over contents...
echo "Copying resources..."
# data folder
cp bin/data/gm.sf2 bin/${APP_NAME}.app/Contents/MacOS/data 
cp bin/data/themes.xml bin/${APP_NAME}.app/Contents/MacOS/data 
  
# data/fonts folder
cp bin/data/fonts/Verdana.ttf bin/${APP_NAME}.app/Contents/MacOS/data/fonts 
cp bin/data/fonts/Raleway-Bold.ttf bin/${APP_NAME}.app/Contents/MacOS/data/fonts 
cp bin/data/fonts/DejaVuSansMono-Bold.ttf bin/${APP_NAME}.app/Contents/MacOS/data/fonts 

# Data\ui\images folder
cp -r bin/data/ui/images/ bin/${APP_NAME}.app/Contents/MacOS/data/ui/images/ 

# Data\ui\svg folder
cp -r bin/data/ui/svg/ bin/${APP_NAME}.app/Contents/MacOS/data/ui/svg/    

# Data\ui\widgets folder
cp -r bin/data/ui/widgets/ bin/${APP_NAME}.app/Contents/MacOS/data/ui/widgets/     

# Data\content folder
cp -r bin/data/content/ bin/${APP_NAME}.app/Contents/MacOS/data/content/     

# Data\ui\widgetHelp folder
cp -r bin/data/ui/widgetHelp/ bin/${APP_NAME}.app/Contents/MacOS/data/ui/widgetHelp/     





#https://github.com/andreyvit/create-dmg
brew install create-dmg 

cd bin/resources/macOS/
tiffutil -cathidpicheck dmg-background.png dmg-background@2x.png -out dmg-background.tiff
cd ../../../

test -f ${APP_NAME}-Installer.dmg && rm ${APP_NAME}-Installer.dmg
create-dmg \
  --volname "${APP_NAME} Installer" \
  --volicon "bin/resources/macOS/${APP_NAME}.icns" \
  --background "bin/resources/macOS/dmg-background.tiff" \
  --window-pos 200 120 \
  --window-size 512 270 \
  --icon-size 40 \
  --icon "${APP_NAME}.app" 432 35 \
  --hide-extension "${APP_NAME}.app" \
  --app-drop-link 432 187 \
  "${APP_NAME}-Installer.dmg" \
  "bin/${APP_NAME}.app"