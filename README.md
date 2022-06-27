# Project-Builder

This program is compatible with Linux

The usage is extremly easy just type into console
```
 $ make    // I named it buildProject feel free to change name

 // To create new project just type
 $ buildProject <ProjectName> -t<language> [options]
```
currently supports these languages:
 - java           ==> j
 - cpp            ==> c

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
With `maven` option there will be also pom.xml

Supported options per language:
  - cpp:
    - QT5      ==> -q
    - OpenCV   ==> -c
  - java:
    - maven    ==> -m

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
