#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <getopt.h>

#define GREEN "\033[32;3m"
#define NORM "\033[0;0m"

void javaCreation(const std::string&);
void cppCreation(const std::string&);

int main(int argc, char ** argv){
    if(argc < 2){
        std::cerr << "\033[31mThe snippert is incorrect. Use it as buildProject [projectname] <-t language>\033[0m" << std::endl;
        return 1;
    }
	//std::cout << argv[1] << std::endl;
	int option;
	bool typeFlag = false, err = false;
	while((option = getopt(argc, argv,"t:")) != -1){
		std::string oarg(optarg);
		switch(option){
			case 't':
				if(typeFlag)
					std::cerr << "Not allowed\n", exit(1);

				if(oarg == "java" || oarg == "j")
					javaCreation(argv[1]), typeFlag = true;
				else if(oarg == "cpp" || oarg == "c++")
					cppCreation(argv[1]), typeFlag = true;
				break;

			default:      
				std::cout << "error\n", err = true;
		}	
	}	
	//std::cout << argv[2] << std::endl;
	if(!typeFlag && !err)
		cppCreation(argv[2]);
}

void javaCreation(const std::string& dir){
	std::string main = dir + ".java";
	//std::cout << GREEN << "Dir is in javaCreation: " << dir << std::endl;
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch " + main + " compile.sh build.sh && chmod 711 compile.sh build.sh";
	system(command.c_str());
	//std::cout << command << NORM << std::endl;

	command = dir + "/" + main;
	std::fstream file(command, std::ios::out);
	file << "class " << dir << "{\n\tpublic static void main(String args[]){\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();
	//std::cout << GREEN<< command << NORM << std::endl;

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "javac " << main << std::endl;
	file.close();
	//std::cout << GREEN<< command << NORM << std::endl;


	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "javac " << main << ";\njava " << dir << std::endl;
	file.close();
	//std::cout << GREEN<< command << NORM << std::endl;
}

void cppCreation(const std::string& dir){
	std::string header = "Header.h", source = "Source.cpp";
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch main.cpp " + header + " " + source +" build.sh compile.sh .ccls makefile && mkdir Build && chmod +x build.sh compile.sh";
	system(command.c_str());
	command = dir + "/.ccls";
	std::fstream file(command, std::ios::out);
	file << "clang++\n%h %cpp -std=c++17";
	file.close();

	command = dir + "/main.cpp";
	file.open(command, std::ios::out);
	file << "#include \"Header.h\"\n\nint main(){\n\tstd::cout << \"Hello World!\\n\";\n\treturn 0;\n}\n " << std::endl;
	file.close();

	command = dir + "/Header.h";
	file.open(command, std::ios::out);
	file << "#pragma once\n\n#include <iostream>\n" << std::endl;
	file.close();

	command = dir + "/Source.cpp";
	file.open(command, std::ios::out);
	file << "#include \"Header.h\"\n" << std::endl;
	file.close();

	command = dir + "/makefile";
	file.open(command, std::ios::out);
	file << "CC = g++\nSTD = -std=c++11\nHEADERS = "<< header <<"\n.PHONY: all\nall:main.o Source.o " << dir << std::endl << dir 
		 << ": main.o Source.o\n\t${CC} ${STD} main.o Source.o -o " << dir 
		 << "\n\nmain.o: main.cpp\n\t${CC} ${STD} -c main.cpp\n\nSource.o: Source.cpp\n\t${CC} ${STD} -c Source.cpp" << std::endl;
	file.close();

	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "#!/bin/sh\n .\nmake -f ./Build/makefile\nif [ $? -eq 0 ]\nthen\n\tmv main.o Source.o Build\n\tclear\n\t./" << dir << "\nfi" << std::endl;
	file.close();

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "#!/bin/sh\n\nclear\nmake -f ./Build/makefile\nif [ $? -eq 0 ]\nthen\n\tmv main.o Source.o Build\nfi" << std::endl;
	file.close();

	command = "mv " + dir + "/makefile " + dir +"/Build";  
	system(command.c_str());

}
