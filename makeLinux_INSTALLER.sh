
#!/bin/bash
echo "------------------ CREATING INSTALLER (Linux) ------------------"

# http://manpages.ubuntu.com/manpages/bionic/man1/chrpath.1.html
# sudo apt-get install chrpath

# https://flatpak.org/setup/Ubuntu/
echo "Installing flatpack..."
sudo apt install flatpak
sudo apt install gnome-software-plugin-flatpak
flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
# ^^^ Requires system restart if 1st time ^^^
flatpak install flathub org.flatpak.Builder

sudo chown $USER:$USER ./build-dir/ 
sudo rm -rf ./build-dir/




sudo apt install flatpak-builder
#flatpak install flathub org.freedesktop.Platform//19.08 org.freedesktop.Sdk//19.08

flatpak install flathub org.gnome.Platform//3.36 org.gnome.Sdk//3.36




sudo apt-get install flatpak-builder elfutils

echo "Building flatpack..."
rm -rf build-dir
# https://docs.flatpak.org/en/latest/first-build.html
# flatpak-builder build-dir bin/resources/linux/org.flatpak.Cognition.json
# For some reason, flatpack-builder wasn't in path, so hardcoding absolute, fix this later ^^^   --repo=cognition-repo 
flatpak-builder \
    --force-clean \
    build-dir bin/resources/linux/org.flatpak.Cognition.json

flatpak-builder --run build-dir bin/resources/linux/org.flatpak.Cognition.json Cognition



flatpak remove org.flatpak.Cognition 

flatpak --user remote-add --no-gpg-verify cognition-repo repo
flatpak --user install cognition-repo org.flatpak.Cognition

 flatpak run org.flatpak.Cognition