# Project-Builder

This is a light weight project builder program that is compatible with Linux.

## Table of contents
 - [Compilation](#Compilation)
 - [Usage](#Usage)
 - [Supported languages](#supported-languages)
    - [Cpp](#Cpp)
    - [Java](#Java)
    - [Python](#Python)
 - [TODO](#TODO)
 - [Neovim](#Neovim)
 - [VS Code](#vs-code)
 - [Updates](#Updates)

## Compilation

Firstly, clone this repository ```git clone --branch master git@github.com:Fildo7525/Project-Builder.git```.

The installation process is really easy. Just type into the shell ```$SHELL ./init.sh```. That is all. By doing this you will get completion for this
executable for bash and zsh.<br />

Otherwise if you want to do the installation by hand follow the steps below.<br />

To compile the project be sure to have cmake installed. To check, if the cmake executable is installed on your system
enter ```cmake --version```. If you have it installed run ```cmake -S . -B ./build```. After the cmake setup
go to the build directory and compile the project ```cd ./build && nice make -j4```. To use the executable in the whole system be sure
to add it into the path ```echo 'export PATH="${PATH}:path/to/executable"' >> ~/.bashrc```. If you use other shell, replace the shell config file
(e.g for zsh ```echo 'export PATH="${PATH}:path/to/executable"' >> ~/.zshrc```). Alternatively, you can move the executable to the ```/usr/bin``` folder.
Or create a link to the executable in the ```/usr/bin``` folder. To be able to use autocompletion in bash source the ./startup/init.bash in the .bashrc. For zsh completion create a link ```ln -s $PWD/startup/_buildProject.zsh $HOME/.local/share/zinit/completion/_buildProject```.

If you want to build the documentation, go to the doc folder and run ```doxygen -g config && doxygen config```. This will generate html, latex, and man documentation.

## Usage

If you did not compile the project, read and do the [Compilation](#compilation) section.
To run the code run:

    buildProject <project-directory> --type <language> [options]

Example:

    buildProject MyProject --type cpp --qt5

To see more detailed usage read README.md or run `buildProject --help`.

## Supported languages

Note: to define a language use `--type / -t` flag and than specify language

Currently supported these language options:
 | Language | Language flag |
 |  :----:  |     :---:     |
 | [cpp](#Cpp)      | cpp / c++ / c |
 | [java](#Java)     | java / j      |
 | [python](#Python)     | python / py     |

Generates project folder with specified name in the argument

### Cpp

  - build/
  - compile_commands.json (compilation flags for language servers (LSP's) like clangd)
  - run (contains code for compilation and launching the code)
  - compile (contains code for compilation)
  - main.cpp
  - src/`ProjectName`.cpp
  - src/`ProjectName`.h

#### Supported options

 | Option |      Flag     | Description |
 | :----: |    :----:     |-------------|
 | QT5    | --qt5 / -q    | To be able to use this flag. Download qt5 using ```sudo apt install qt5``` command on Ubuntu. Or any other package manager. |
 | OpenCV | --opencv / -c | To be able to use OpenCV download it using your prefered package manager. |
 | Raspberry pi | --rpi   | To be able to use this option you have to download and install WiringPi library. This option links Wiring Pi to the project. |
 | Advent of code | --aoc / -a| To create a project with already some includes and some basic functionality meaning reading from file. Two files are created ```input``` and ```test``` |

 NOTE: WiringPi is a deprecated library, which may not work on newer boards. Try installing maintained code. e.g.: https://github.com/joan2937/pigpio or for C++ it's https://github.com/JoachimSchurig/CppGPIO.

### Java

  - run
  - compile <br />
You are asked to enter package name.<br />
There will be created:
 - Main.java
With `maven` option set there will be also pom.xml

#### Supported options

 | Option |      Flag     | Description |
 | :----: |    :----:     |-------------|
 | maven  |  --maven / -m | Maven is a build system supporting java language. Install it using your prefered package manager. |

### Python

 - run
 - main.py

#### Supported options

 | Option |      Flag     | Description |
 | :----: |    :----:     |-------------|
 |        |               |             |

  Currently there are no supported options for python.

NOTE: For supported options the appropriate dependencies have to be installed.

## TODO
- ROS2 option for cpp project
- Raspberry Pi for python

## Neovim

If you are looking for a code editor or an IDE. I highly recommend ```neovim```
My neovim config is adjusted for this project creator. Check it out if you want
https://github.com/Fildo7525/nvimLua. To start with your own configuration watch
the [Neovim from scratch](https://www.youtube.com/watch?v=ctH-a-1eUME&list=PLhoH5vyxr6Qq41NFL4GvhFp-WLd5xzIzZ) series.

## VS Code

Otherwise, if you are writing code in VS code go into ```Keyboard Shortcuts``` / ``` Ctrl + K ```
switch into JSON view ( icon in the top right corner ) and add a snippet

    {
        "key": "ctrl+b",
        "command": "workbench.action.terminal.sendSequence",
        "args": { "text": "./run\n" }
    },

-> ```Ctrl + B``` keybinding to build the project, although you can set it to your own keybinding<br />
-> ``` workbench.action.terminal.sendSequence ``` sends the command to console<br />
-> ``` ./run\n ``` the send command<br />

## Updates

If you have any suggestions for any improvement, do not hesitate to create an issue or fork the repository and create a pull request.

