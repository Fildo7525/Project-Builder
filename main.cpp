#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

int main(int argc, char ** argv){
    if(argc < 2){
        std::cerr << "\033[31mThe snippert is incorrect. Use it as project <projectname>\033[0m" << std::endl;
        return 1;
    }
    
    int err;
    std::string dir = argv[1], header = "Header.h", source = "Source.cpp";
    std::string command = "mkdir " + dir + " && cd " + dir + " && touch main.cpp " + header + " " + source +" build.sh makefile && mkdir Build && chmod +x build.sh";

    try{
        err = system(command.c_str());

        command = dir + "/main.cpp";
        std::fstream file(command, std::ios::out);
        file << "#include \"Header.h\"\n\nint main(){\n\tstd::cout << \"Hello World!\\n\";\n\treturn 0;\n}" << std::endl;
        file.close();
        if(file.bad()) throw -1;

        command = dir + "/Header.h";
        file.open(command, std::ios::out);
        file << "#pragma once\n\n#include <iostream>\n" << std::endl;
        file.close();
        if(file.bad()) throw -2;

        command = dir + "/Source.cpp";
        file.open(command, std::ios::out);
        file << "#include \"Header.h\"\n" << std::endl;
        file.close();
        if(file.bad()) throw -3;

        command = dir + "/makefile";
        file.open(command, std::ios::out);
        file << "CC = g++\nSTD = -std=c++11\n\n" << dir << ": main.o Source.o\n\t${CC} ${STD} main.o Source.o -o " << dir << "\n\nmain.o: main.cpp\n\t${CC} ${STD} -c main.cpp\n\nSource.o: Source.cpp\n\t${CC} ${STD} -c Source.cpp" << std::endl;
        file.close();
	if(file.bad()) throw -4;

        command = dir + "/build.sh";
        file.open(command, std::ios::out);
        file << "#!/bin/sh\n\nmv Build/makefile .\nmake\nmv makefile Build\nif [ $? -eq 0 ]\nthen\n\tmv main.o Source.o Build\n\tclear\n\t./" << dir << "\nfi" << std::endl;
        file.close();
	if(file.bad()) throw -5;
	
    command = "mv " + dir + "/makefile " + dir +"/Build";  
	err = system(command.c_str());

    }catch(int i){
        switch(i){
            case -1:
                std::cerr << "There was an error with main.cpp file" << std::endl;
                break;
            case -2:
                std::cerr << "There was an error with Header.h file" << std::endl;
                break;
            case -3:
                std::cerr << "There was an error with Source.cpp file" << std::endl;
                break;
            case -4:
                std::cerr << "There was an error with makefile file" << std::endl;
                break;
            case -5:
                std::cerr << "There was an error with bash.sh file" << std::endl;
                break;
            default:
                std::cerr << "An unidentified error has occured" << std::endl;
        }
        command = "cd .. && rm -rf " + dir;
        err = system(command.c_str());
        return 2;
    }
    return 0;
}
