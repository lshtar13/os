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

clean
