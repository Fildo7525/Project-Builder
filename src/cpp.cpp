#include "../include/Header.h"

void cppCreation(const std::string& dir, bool qt){
	std::string header = "Header.h", source = "Source.cpp";
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch main.cpp " + header + " " + source +" build.sh compile.sh CMakeLists.txt && mkdir cmake-build && chmod +x build.sh compile.sh";
	int trash = system(command.c_str());

	command = dir + "/main.cpp";
	std::fstream file(command, std::ios::out);
	file << "#include \"Header.h\"\n\nint main()\n{\n\tstd::cout << \"Hello World!\\n\";\n\treturn 0;\n}" << std::endl;
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
	if (qt) {
		file << "cmake_minimum_required(VERSION 3.0.0)\n"
			<< "project(" << dir << " VERSION 0.1.0)\n\n"

			<< "set(CMAKE_CXX_STANDARD 17)\n"
			<< "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"

			<< "set(CMAKE_AUTOMOC ON)\n"
			<< "set(CMAKE_AUTORCC ON)\n"
			<< "set(CMAKE_AUTOUIC ON)\n"
			<< "set(Qt5_DIR \"/usr/lib/x86_64-linux-gnu/cmake/Qt5/Qt5Config.cmake\")\n\n"

			<< "if(CMAKE_VERSION VERSION_LESS \"3.7.0\")\n"
				<< "\tset(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
			<< "endif()\n\n"

			<< "find_package(Qt5 COMPONENTS Widgets REQUIRED)\n\n"

			<< "add_executable(" << dir << "\n"
				<< "\tmain.cpp Source.cpp\n"
			<< ")\n"
			<< "target_link_libraries(" << dir <<" PUBLIC Qt5::Core)\n" << std::endl;
	} else {
		file << "cmake_minimum_required(VERSION 3.0.0)\n"
			<< "project(" << dir << " VERSION 0.1.0)\n\n"
			<< "set(CMAKE_CXX_STANDARD 17)\n\n"
			<< "add_executable(" << dir << " main.cpp Source.cpp)\n"
			<< "#target_link_libraries(" << dir << " pthread)\n#example of linking libraries";
	}
	file.close();

	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "#!/bin/sh\ncmake --build ./cmake-build\nif [ $? -eq 0 ];then\n./cmake-build/" << dir << "\nfi";
	file.close();

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "#!/bin/sh\n\nclear\ncmake --build ./cmake-build\n";
	file.close();

	command = "cd " + dir + " && cmake CMakeLists.txt -S . -B ./cmake-build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && mv ./cmake-build/compile_commands.json .";
	trash = system(command.c_str());
}

