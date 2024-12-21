
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

APP_NAME="Cognition"
# --------------------------------------------------------------
# Be sure to compile it initially in Xcode before thying this...
# --------------------------------------------------------------

SOURCE_CODE_TARGET="/Users/zabba/projects/of_v0.11.2_ios_release/apps/myApps/${APP_NAME}"

echo "Updating core source code in iOS target project [${SOURCE_CODE_TARGET}/src]..."
cp -r ./src/app_widgets $SOURCE_CODE_TARGET/src
cp -r ./src/core $SOURCE_CODE_TARGET/src
cp -r ./src/viz $SOURCE_CODE_TARGET/src

cd ${SOURCE_CODE_TARGET}
#xcodebuild -list -project Cognition.xcodeproj/

# List simulators eg:
# xcrun simctl list | grep "iPad Pro"

SIMULATOR_DEVICE_NAME="iPad Pro (12.9-inch) (5th generation) (274D51A1-AACC-45BA-88CE-269894898766)"
SIMULATOR_DEVICE_ID="274D51A1-AACC-45BA-88CE-269894898766"

PATH_TO_APPLICATION_BUNDLE="/Users/zabba/Library/Developer/Xcode/DerivedData/Cognition-crdezphhfvaqncfsbgkylqrbicvz"
BUNDLE_ID_OF_APP_BUNDLE="net.fluidtheory.cognition"

DEVICE_NAME="Stuart’s iPad"

if [ "$r" == "debug" ]
then
    #echo "Packaging debug..."
    #xcodebuild -scheme $APP_NAME -configuration Debug build  
    echo "Opening XCode.. Run it from there ..."
    xed .

    # xcodebuild \
    #   -scheme $APP_NAME  \
    #   -destination "platform=iOS,name=$DEVICE_NAME"  

      #-destination "platform=iOS Simulator,id=${SIMULATOR_DEVICE_ID}"      # link errors

      # echo "Launching Simulator... ${SIMULATOR_DEVICE_NAME}"
      # /Applications/Xcode.app/Contents/Developer/Applications/Simulator.app/Contents/MacOS/Simulator -CurrentDeviceUDID $SIMULATOR_DEVICE_ID & echo "done..."

      # echo "Installing App Bundle [${PATH_TO_APPLICATION_BUNDLE}] to Simulator..."
      # xcrun simctl install $SIMULATOR_DEVICE_ID $PATH_TO_APPLICATION_BUNDLE

      # echo "Launching AppBundle [${BUNDLE_ID_OF_APP_BUNDLE}] in Simulator..."
      # xcrun simctl launch $SIMULATOR_DEVICE_ID $BUNDLE_ID_OF_APP_BUNDLE



elif [ "$r" == "release" ]
then
    echo "Packaging release..."

    xcodebuild -scheme Cognition -configuration Release build  
    brew install ios-deploy        

else
    echo "Did not do anything..."
fi

