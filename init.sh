cmake -S . -B ./build
cd build/
nice make -j4 && cp ./buildProject ..

cd ..
BUILD_DIR="$(pwd)/build"
STARTUP_DIR="$(pwd)/startup"
LINK=$HOME/.local/share/zinit/completions/_buildProject

if [[ $SHELL = "/usr/bin/zsh" || $SHELL = "/bin/zsh" ]]; then
	echo "export PATH=\"$PATH:$BUILD_DIR\"" >> $HOME/.zshrc
	if [[ ! -f $LINK ]]; then
		ln -s $STARTUP_DIR/_buildProject.zsh $LINK
	fi
elif [[ $SHELL = "/bin/bash" ]]; then
	echo "export PATH=\"\$PATH:$BUILD_DIR\"" >> $HOME/.bashrc
	echo "source $STARTUP_DIR/init.bash" >> $HOME/.bashrc
	. ~/.bashrc
fi

read -p "Do you want to generate documentation? [Y/n]: " i
if [[ $i == "n" ]]; then
	exit 0
fi

which doxygen
if [[ $? != 0  ]]; then
	sudo apt install doxygen -y
fi

cd ./doc
doxygen config &> /dev/null
cd man/man3
PAGE=$(ls ../../.. -1 | grep md)
sudo cp ../../../$PAGE /usr/share/man/man3/buildProject.3

