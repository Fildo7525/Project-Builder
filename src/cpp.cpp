#include "../include/Header.h"
#include <iostream>

void cppCreation(const std::string& dir, bool qt){
	std::string header = "Header.h", source = "Source.cpp";
	std::string command = "mkdir " + dir + " && cd " + dir + " && touch main.cpp " + header + " " + source +" build.sh compile.sh CMakeLists.txt && mkdir cmake-build && chmod +x build.sh compile.sh";
	int trash = system(command.c_str());

	command = dir + "/main.cpp";
	std::fstream file(command, std::ios::out);
	if (qt)
		file << "#include <QCoreApplication>\n#include \"" << dir << ".h\"\n\nint main(int argc, char *argv[])\n{\n\tQCoreApplication a(argc, argv);\n\tstd::cout << \"Hello World!\\n\";\n\treturn a.exec();\n}\n" << std::endl;
	else
		file << "#include \"" << dir << ".h\"\n\nint main()\n{\n\tstd::cout << \"Hello World!\\n\";\n\treturn 0;\n}\n" << std::endl;
	file.close();

	command = dir + "/" + dir + ".h";
	file.open(command, std::ios::out);
	file << "#pragma once\n\n#include <iostream>\n" << std::endl;
	file.close();

	command = dir + "/" + dir + ".cpp";
	file.open(command, std::ios::out);
	file << "#include \"" << dir << ".h\"\n" << std::endl;
	file.close();
	
	command = dir + "/CMakeLists.txt";
	file.open(command, std::ios::out);
	if (qt) {
		file << "cmake_minimum_required(VERSION 3.0.0)\n"
			<< "project(" << dir << " VERSION 0.1.0)\n\n"

			<< "set(CMAKE_CXX_STANDARD 17)\n"
			<< "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
			<< "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"

			<< "set(CMAKE_AUTOMOC ON)\n"
			<< "set(CMAKE_AUTORCC ON)\n"
			<< "set(CMAKE_AUTOUIC ON)\n\n"

			<< "set(Qt5_DIR \"/usr/lib/x86_64-linux-gnu/cmake/Qt5/Qt5Config.cmake\")\n"
			<< "set(QTDIR \"/usr/include/x86_64-linux-gnu/qt5/QtCore\")\n\n"

			<< "set(SOURCES\n\tmain.cpp\n\t" << dir << ".cpp\n)\n"
			<< "set(HEADERS\n\t" << dir << ".h\n)\n\n"

			<< "if(CMAKE_VERSION VERSION_LESS \"3.7.0\")\n"
				<< "\tset(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
			<< "endif()\n\n"

			<< "find_package(Qt5 COMPONENTS Widgets REQUIRED)\n\n"

			<< "add_executable(${PROJECT_NAME}\n"
				<< "\t${SOURCES}\n"
				<< "\t${HEADERS}\n"
			<< ")\n\n"

			<< "target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)\n"
			<< "target_link_directories(${PROJECT_NAME} PUBLIC QTDIR)\n" << std::endl;
	} else {
		file << "cmake_minimum_required(VERSION 3.0.0)\n"
			<< "project(" << dir << " VERSION 0.1.0)\n\n"
			<< "set(CMAKE_CXX_STANDARD 17)\n"
			<< "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"
			<< "set(SOURCES\n\tmain.cpp\n\tSource.cpp\n)\n\n"

			<< "add_executable(${PROJECT_NAME}\n"
				<< "\t${SOURCES}\n"
			<< ")\n\n"

			<< "#target_link_libraries(${PROJECT_NAME} PUBLIC pthread)\n#example of linking libraries\n" << std::endl;
	}
	file.close();

	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << "#!/usr/bin/zsh\ncd build/\nmake -j16\nif [ $? -eq 0 ];then\n\tclear\n\t./" << dir << "\nfi\n" << std::endl;
	file.close();

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << "#!/usr/bin/zsh\n\nclear\ncd build/\nmake -j16\n" << std::endl;
	file.close();

	command = "cd " + dir + " && cmake CMakeLists.txt -S . -B ./build && cp ./build/compile_commands.json .";
	trash = system(command.c_str());
}

