# Project-Builder

This program is compatible with Linux

The usage is extremly easy just type into console
```
 $ make    // I named it buildProject

 // To create new project just type
 $ buildProject <ProjectName> -t<option>
```
currently supports these options:
 - java / j
 - cpp

Generates project folder with specified name in the argument
- <name>
  - /Build
  - build.sh
  - compile.sh
  - main.cpp
  - Header.cpp
  - Source.cpp
  - .ccls (for code completion in neovim)
  - .vimspector.json (debugging with vimspector)

Furthermore, if you are writing code in VS code go into ```Keyboard Shortcuts``` ``` Ctrl + K ```
switch into JSON view ( icon in the top right corner ) and add a snippet
```
{
    "key": "ctrl+b", 
    "command": "workbench.action.terminal.sendSequence",
    "args": { "text": "./build.sh\n" }
},
```

-> ```Ctrl + B``` keybinding to build the project, although you can set it to your own keybinding                                                   
-> ``` workbench.action.terminal.sendSequence ``` sends the command to console                                                            
-> ``` ./build.sh\n ``` the send command                                                     
