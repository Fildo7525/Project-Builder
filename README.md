# Project-Builder

This program is compatible with Linux

The usage is extremly easy just type into console
```
 $ g++ main.cpp -o <nameAfterBuild>    // I named it projectBuild

 // To create new project just type
 $ projectBuild <ProjectName>
```

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
