# Project-Builder

This program is compatible with Linux

currently supports these languages:
 - java           ==> java / j
 - cpp            ==> cpp / c++ / c

Generates project folder with specified name in the argument
For cpp:
  - build/
  - compile_commands.json
  - build.sh
  - compile.sh
  - main.cpp
  - `ProjectName`.cpp
  - `ProjectName`.h

For java:
  - build.sh
  - compile.sh
You are asked to enter package name. There will be created:
 - Main.java
With `maven` option set there will be also pom.xml

Supported options per language:
  - cpp:
    - QT5      ==> --qt5 / -q
    - OpenCV   ==> --opencv / -c
  - java:
    - maven    ==> --maven / -m

<h2>Neovim</h2>

If you are looking for a code editor or an IDE. I highly recommend ```neovim``` 
My neovim config is adjusted for this project creator. Check it out if you want 
 https://github.com/Fildo7525/nvimLua 

<h2>VS Code</h2>

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

<h2>Updates</h2>

If you have any suggestions for any improvement, do not hesitate to create an issue or fork the repository.

