
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


if [ "$r" == "debug" ]
then
    echo "Packaging debug..."
    make Debug -j8 -s 2>&1
    rm -rf bin/libs
    cp -r bin/libs-linux64 bin/libs   
    make RunDebug || exit 1
 
elif [ "$r" == "release" ]
then
    make -j8 -s 2>&1
    rm -rf bin/libs
    cp -r bin/libs-linux64 bin/libs
    make RunRelease

elif [ "$r" == "release_no_exec" ]
then
    make -j8 -s 2>&1
    rm -rf bin/libs
    cp -r bin/libs-linux64 bin/libs

else
    echo "Did not do anything..."
fi

