# Project-Builder

This program is compatible with Linux

## Compilation

To compile the project be sure to have cmake installed. To check if the executable is installed on your system
enter ```cmake --version```. If you have it installed run ```cmake -S . -B ./build```. After the cmake setup
go to the build direcotory and compile the project ```cd ./build && make```. To use the executable in the whole system be sure
to add it into the path ```echo 'export PATH="${PATH}:path/to/executable"' >> ~/.bashrc```. If you use other shell, replace the shell config file.

## Usage

If you did not compile the project, read and do the [Compilateion](#compilation) section.
To run the code run:

    buildProject <project-directory> --type <language> [options]

example:

    buildProject MyProject --type cpp --qt5

## Supported languages

Currently supported these language options:
 | Language | Language flag |
 |  :----:  |     :---:     |
 | cpp      | cpp / c++ / c |
 | java     | java / j      |

Generates project folder with specified name in the argument

### Cpp

  - build/
  - compile_commands.json
  - build.sh
  - compile.sh
  - main.cpp
  - `ProjectName`.cpp
  - `ProjectName`.h

#### Supported options

 | Option |      Flag     | Description |
 | :----: |    :----:     |-------------|
 | QT5    | --qt5 / -q    | To be able to use this flag. Download qt5 using ```sudo apt install qt5``` command on Ubuntu. Or any other package manager. |
 | OpenCV | --opencv / -c | To be able to use OpenCV download it using your prefered package manager. |

### Java

  - build.sh
  - compile.sh <br />
You are asked to enter package name.<br />
There will be created:
 - Main.java
With `maven` option set there will be also pom.xml

#### Supported options

 | Option |      Flag     | Description |
 | :----: |    :----:     |-------------|
 | maven  |  --maven / -m | Maven is a build system supporting java language. Install it using your prefered package manager. |

NOTE: For supported options the appropriate dependencies have to be installed.

## Neovim

If you are looking for a code editor or an IDE. I highly recommend ```neovim```
My neovim config is adjusted for this project creator. Check it out if you want
https://github.com/Fildo7525/nvimLua

## VS Code

Otherwise, if you are writing code in VS code go into ```Keyboard Shortcuts``` / ``` Ctrl + K ```
switch into JSON view ( icon in the top right corner ) and add a snippet

    {
        "key": "ctrl+b",
        "command": "workbench.action.terminal.sendSequence",
        "args": { "text": "./build.sh\n" }
    },

-> ```Ctrl + B``` keybinding to build the project, although you can set it to your own keybinding<br />
-> ``` workbench.action.terminal.sendSequence ``` sends the command to console<br />
-> ``` ./build.sh\n ``` the send command<br />

## Updates

If you have any suggestions for any improvement, do not hesitate to create an issue or fork the repository.

