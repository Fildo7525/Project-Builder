#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <getopt.h>

#define GREEN "\033[32;2m"
#define	RED "\033[31;2m"
#define NORM "\033[0;0m"

void javaCreation(const std::string&);
void cppCreation(const std::string&);

int main(int argc, char ** argv){
		if(argc < 2){
				std::cerr << "\033[31mThe snippert is incorrect. Use it as buildProject [projectname] -t<language>\033[0m" << std::endl;
				return 1;
		}
	//std::cout << argv[1] << std::endl;
	int option;
	bool typeFlag = false, err = false;

	while((option = getopt(argc, argv,"t:")) != -1){
		std::string oarg(optarg);
		std::string newDir(argv[0]);
		switch(option){
			case 't':
				if(typeFlag)
					std::cerr << RED << "You are only allowed to specify on file type\n" << NORM << std::ends, exit(1);
				if(newDir.find("-") == 0)
					std::cerr << RED << "Directory must be specified as a second argument buildProject [projectname] -t<language>" << NORM << std::endl, exit(2);

				if(oarg == "java" || oarg == "j")
					javaCreation(argv[1]), typeFlag = true;
				else if(oarg == "cpp" || oarg == "c++" || oarg == "c")
					cppCreation(argv[1]), typeFlag = true;
				break;

			default:			
				std::cout << "error\n", err = true;
		}	
	}	
}

void javaCreation(const std::string& dir){
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch Main.java compile.sh build.sh && chmod 711 compile.sh build.sh";
	int trash = system(command.c_str());

	command = dir + "/Main.java";
	std::fstream file(command, std::ios::out);
	file << "public class Main {\n\tpublic static void main(String args[]){\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "javac Main.java"<< std::endl;
	file.close();


	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "javac Main.java;\nif [ $? -eq 0 ]\nthen\n\tjava Main\nelse\n\trm Main.class\nfi" << std::endl;
	file.close();
}

void cppCreation(const std::string& dir){
	std::string header = "Header.h", source = "Source.cpp";
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch main.cpp " + header + " " + source +" build.sh compile.sh CMakeLists.txt && mkdir Build cmake-build && chmod +x build.sh compile.sh";
	int trash = system(command.c_str());

	command = dir + "/main.cpp";
	std::fstream file(command, std::ios::out);
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

	command = dir + "/CMakeLists.txt";
	file.open(command, std::ios::out);
	file << "cmake_minimum_required(VERSION 3.0.0)\n"
		<< "project(" << dir << " VERSION 0.1.0)\n"
		<< "set(CMAKE_CXX_STANDARD 17)\n"
		<< "add_executable(" << dir << " main.cpp Source.cpp)\n"
		<< "#target_link_libraries(" << dir <<" pthread)\n # how to add libraries";
	file.close();

	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "#!/bin/sh\ncmake --build ./cmake-build\nif [ $? -eq 0 ]; then\n./cmake-build/" << dir << "\nfi\n" << std::endl;
	file.close();

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "#!/bin/sh\n\nclear\n./cmake-build/" << dir << std::endl;
	file.close();

	command = "cd " + dir + " && cmake CMakeLists.txt -S . -B ./cmake-build -DCMAKE_EXPORT_COMPILE_COMMANDS=1";
	std::cout	<< command << '\n';
	trash = system(command.c_str());

}
