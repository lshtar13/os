#!/bin/bash
set -e

packages=(
	"build-essential"
	"bison"
	"flex"
	"libgmp3-dev"
	"libmpc-dev"
	"libmpfr-dev"
	"texinfo"
	"libisl-dev"
)

defaultPath="./cross"
srcPath="$defaultPath/src"
binPath="$defaultPath/bin"

binutilsVersion="2.41"
gccVersion="11.4.0"
binutilsName="binutils-$binutilsVersion"
gccName="gcc-$gccVersion"
downloads=(
	"$binutilsName https://ftp.gnu.org/gnu/binutils/$binutilsName.tar.gz"
	"$gccName https://ftp.gnu.org/gnu/gcc/$gccName/$gccName.tar.gz"
)

# Script Description
echo "This script is for installing the GCC cross compiler."
echo ""
echo "The following packages will be installed, and binutils and GCC source codes will be downloaded and extracted."
echo ""
echo "List of packages to be installed:"

# Package List Output
for package in "${packages[@]}"; do
	echo "  - $package"
done

echo ""
read -r -p "Are you going to install those dependencies? (y/n) " answer

if [[ "$answer" == "y" ]]; then
	# Install Dependency Packages
	sudo apt update
	sudo apt install "${packages[@]}" -y
else
	echo "Skipping dependency installation..."
fi

echo ""
read -r -p "Enter the directory to download and extract source codes \
    (or the path to existing source codes: default - ./cross): " crossPath

if [[ -z "$crossPath" ]]; then
	echo "No extract path provided. Using default path($defaultPath)."
	crossPath="$defaultPath"
fi

crossPath=$(readlink -f "$crossPath")
srcPath="$crossPath/src"
binPath="$crossPath/bin"
if [[ ! -d "$crossPath" ]]; then
	echo "Creating directory: $crossPath"
	mkdir -p "$srcPath"
	mkdir -p "$binPath"
fi

# Download and extract binutils and GCC source code
for download in "${downloads[@]}"; do
	name=$(echo "$download" | awk '{print $1}')
	url=$(echo "$download" | awk '{print $2}')
	filename=$(basename "$url")

	echo ""
	read -r -p "Download and extract ${name} source code from ${url}? (y/n) " answer

	if [[ "$answer" == "y" ]]; then
		echo "Downloading ${name} source code..."
		wget "$url"
		echo "Download completed."

		echo "Extracting ${filename} to ${crossPath}..."
		tar -xzf "$filename" -C "$srcPath"
		echo "Extraction completed."
		rm "$filename"* # Remove tar.gz file after extraction
	else
		echo "Skipping ${name} download and extraction."
	fi
done
echo "Download and extraction completed."
echo ""

echo "Start building..."
export PREFIX="$crossPath"
export TARGET=i686-elf
export PATH="$binPath:$PATH"

read -r -p "Do you want to build binutils? (y/n): " answer
if [[ "$answer" == "y" ]]; then
	cd "$crossPath/src"
	mkdir build-binutils
	cd build-binutils
	../"$binutilsName"/configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
	make
	make install
	echo "Binutils build completed."
else
	echo "Skipping binutils build."
fi

read -r -p "Do you want to build gcc? (y/n): " answer
if [[ "$answer" == "y" ]]; then
	cd "$crossPath/src"
	which -- $TARGET-as || echo $TARGET-as is not in the PATH

	mkdir build-gcc
	cd build-gcc
	../$gccName/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
	make clean
	make all-gcc
	make all-target-libgcc
	make all-target-libstdc++-v3
	make install-gcc -j3
	make install-target-libgcc -j3
	make install-target-libstdc++-v3 -j3
	echo "GCC build completed."
else
	echo "Skipping gcc build."
fi

echo "Build process completed."
