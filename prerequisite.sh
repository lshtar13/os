#!/bin/bash

# Script Description
echo "This script is for installing the GCC compiler."
echo "The following packages will be installed, and binutils and GCC source codes will be downloaded and extracted."
echo ""
echo "List of packages to be installed:"

# Package List Output
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
  echo "skip..."
fi

downloads=(
  "binutils-2.41 https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz"
  "gcc-11.4.0 https://ftp.gnu.org/gnu/gcc/gcc-11.4.0/gcc-11.4.0.tar.gz"
)

# Download and extract binutils and GCC source code
for download in "${downloads[@]}"; do
  name=$(echo "$download" | awk '{print $1}')
  url=$(echo "$download" | awk '{print $2}')
  filename=$(basename "$url")

  echo ""
  read -r -p "Do you want to download and extract ${name} source code (from ${url})? (y/n) " answer

  if [[ "$answer" == "y" ]]; then
    echo "Downloading ${name} source code..."
    wget "$url"
    echo "Download completed."
    echo ""

    read -r -p "Where to extract? (absolute path) " extractPath

    if [[ -z "$extractPath" ]]; then
      echo "No extract path provided. Using current directory."
      extractPath="./"
    fi

    if [[ ! -d "$extractPath" ]]; then
      echo "Creating directory $extractPath"
      mkdir -p "$extractPath"
    fi

    echo "Extracting ${filename} to ${extractPath}..."
    tar -xzf "$filename" -C "$extractPath"
    echo "Extraction completed."
    rm "$filename" # remove tar.gz file after extraction
  else
    echo "Skipping ${name} download and extraction."
  fi
done

echo "Download and extraction completed. Next step is to build."
echo "You need to manually build."