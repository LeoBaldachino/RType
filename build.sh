#/bin/bash

git submodule update --init --recursive

dir="build"

if [[ -d $dir ]]; then
    rm -rf $dir/*
else
    mkdir $dir
fi

cd $dir;cmake ..;make;mv bin/* .
