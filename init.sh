cmake -S . -B ./build
cd build/
nice make -j4 && cp ./buildProject ..

cd ../startup/
DIR=$(pwd)
LINK=$HOME/.local/share/zinit/completions/_buildProject

if [[ $SHELL == "/usr/bin/zsh" || $SHELL == "/bin/zsh" ]]; then
	echo "export PATH="$PATH:$DIR/build"" >> $HOME/.zshrc
	if [[ ! -f $LINK ]]; then
		ln -s $DIR/startup/_buildProject.zsh $LINK
	fi
elif [[ $SHELL == "/bin/bash" ]]; then
	echo "export PATH="$PATH:$DIR/build"" >> $HOME/.bashrc
	echo "source "$DIR./init.bash"" >> $HOME/.bashrc
fi

