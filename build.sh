#!/usr/bin/zsh

cd ./build/
make -j16
if [[ $? == 0 ]]; then
	mv ./buildProject ..
fi
