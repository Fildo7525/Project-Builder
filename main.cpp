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
        std::cerr << "\033[31mThe snippert is incorrect. Use it as buildProject [projectname] <-t language>\033[0m" << std::endl;
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
					std::cerr << RED << "Not allowed\n" << NORM << std::ends, exit(1);
				if(newDir.find("-") == 0)
					std::cerr << RED << "Directory must be specified as a second argument buildProject [projectname] <-t language>" << NORM << std::endl, exit(2);

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
	//std::cout << GREEN << "Dir is in javaCreation: " << dir << std::endl;
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch Main.java compile.sh build.sh && chmod 711 compile.sh build.sh";
	int trash = system(command.c_str());
	//std::cout << command << NORM << std::endl;

	command = dir + "/Main.java";
	std::fstream file(command, std::ios::out);
	file << "public class Main {\n\tpublic static void main(String args[]){\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();
	//std::cout << GREEN<< command << NORM << std::endl;

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "javac Main.java"<< std::endl;
	file.close();
	//std::cout << GREEN<< command << NORM << std::endl;


	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "javac Main.java;\nif [ $? -eq 0 ]\nthen\n\tjava Main\nelse\n\trm Main.class\nfi" << std::endl;
	file.close();
	//std::cout << GREEN<< command << NORM << std::endl;
}

void cppCreation(const std::string& dir){
	std::string header = "Header.h", source = "Source.cpp";
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch main.cpp " + header + " " + source +" build.sh compile.sh .ccls .vimspector.json makefile && mkdir Build && chmod +x build.sh compile.sh";
	int trash = system(command.c_str());
	command = dir + "/.ccls";
	std::fstream file(command, std::ios::out);
	file << "clang++\n%h %cpp -std=c++17";
	file.close();

	command = dir + "/.vimspector.json";
	file.open(command, std::ios::out);
	file << "{\n" 
			<< "\t\"configurations\": {\n"
			<< "\t\"Launch\": {\n"
				<< "\t\t\"adapter\": \"vscode-cpptools\",\n"
				<< "\t\t\"default\" : true,\n"
				<< "\t\t\"breakpoints\": {\n"
					<< "\t\t\t\"exception\": {\n"
						<< "\t\t\t\t\"caught:\": \"\",\n"
						<< "\t\t\t\t\"uncaught\": \"Y\"\n"
					<< "\t\t\t}\n"
				<< "\t\t},\n"
				<< "\t\t\"filetypes\": [\n"
					<< "\t\t\t\"cpp\",\n"
					<< "\t\t\t\"c\",\n"
					<< "\t\t\t\"objc\",\n"
					<< "\t\t\t\"rust\"\n"
				<< "\t\t],\n"
				<< "\t\t\"configuration\": {\n"
					<< "\t\t\t\"request\": \"launch\",\n"
					<< "\t\t\t\"program\": \"${workspaceRoot}/" << dir <<"\",\n"
					<< "\t\t\t\"args\": [],\n"
					<< "\t\t\t\"cwd\": \"${workspaceRoot}\",\n"
					<< "\t\t\t\"environment\": [],\n"
					<< "\t\t\t\"externalConsole\": true,\n"
					<< "\t\t\t\"stopOnEntry#json\": \"${stopOnEntry:true}\",\n"
					<< "\t\t\t\"MIMode\": \"gdb\",\n"
					<< "\t\t\t\"setupCommands\": [\n"
						<< "\t\t\t\t{\n"
							<< "\t\t\t\t\"description\": \"Enable pretty-printing for gdb\",\n"
							<< "\t\t\t\t\"text\": \"-enable-pretty-printing\",\n"
							<< "\t\t\t\t\"ignoreFailures\": true\n"
						<< "\t\t\t\t}\n"
					<< "\t\t\t]\n"
					<< "\t\t\t}\n"
				<< "\t\t}\n"
			<< "\t}\n"
		<< "}";
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
	file << "CC = g++\nSTD = -std=c++11 -g\nHEADERS = "<< header <<"\n.PHONY: all\nall:main.o Source.o " << dir << std::endl << dir 
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
	trash = system(command.c_str());

}
