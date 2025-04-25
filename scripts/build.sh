#!/bin/bash
set -e

locations=(
	"$(pwd)/libc"
	"$(pwd)/kernel"
)

clean() {
	for location in "${locations[@]}"; do
		cd $location
		make clean
	done
}

headers() {
	for location in "${locations[@]}"; do
		cd $location
		make install-headers
	done
}

install() {
	for location in "${locations[@]}"; do
		cd $location
		make install
	done
}

clean
headers
install
