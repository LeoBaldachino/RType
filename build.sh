#/bin/bash

git submodule update --init --recursive

dir="build"

if [[ ! -e $dir ]]; then
    mkdir $dir
elif [[ ! -d $dir ]]; then
    echo "$dir already exists but is not a directory" 1>&2
fi

cd $dir;cmake ..;make;mv $dir/bin/* $dir