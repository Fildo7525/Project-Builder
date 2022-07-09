#include "BuildProject.h"

void makeCppProject(const std::string &dir, const flags &languageFlags)
{
	std::string command = "mkdir -p " + dir + "/src && cd " + dir + " && touch src/" + dir + ".cpp src/" + dir + ".h src/CMakeLists.txt build.sh compile.sh && chmod +x build.sh compile.sh";
	executeCommand(command, INITIALIZE_DIR_ERROR);

	generateMainFile(dir, languageFlags);

	generateDirectoryNamedFiles(dir);

	generateCmakeFile(dir, languageFlags);

	generateBuildFiles(dir);

	command = "cd " + dir + " && cmake CMakeLists.txt -S . -B ./build && cp ./build/compile_commands.json .";
	executeCommand(command);
}

std::string cmakeVersion()
{
	executeCommand("cmake --version | grep version >> cmake_version.txt",
					"Cmake version could not be detected. Either cmake or grep is not installed on the executeCommand.");

	std::fstream cmakeVersionFile("cmake_version.txt", std::ios::in);
	std::string version;

	std::getline(cmakeVersionFile, version);
	auto beginPos = std::find(version.rbegin(), version.rend(), ' ').base() - version.begin();
	version = version.substr(beginPos);
	cmakeVersionFile.close();

	executeCommand("rm -f cmake_version.txt");

	return version;
}

void generateMainFile(const std::string &dir, const flags &languageFlags)
{
	indent tabs;
	std::string command = dir + "/main.cpp";

	std::fstream file(command, std::ios::out);
	if (languageFlags.qt)
		file << "// QT include files\n#include <QCoreApplication>\n\n";
	if (languageFlags.openCV)
		file << "// OpenCV include files\n#include <opencv2/highgui.hpp>\n\n";

	file << "#include \"" << dir << ".h\"\n\nint main(int argc, char *argv[])\n{\n"
				<< (languageFlags.qt ? "\tQCoreApplication a(argc, argv);\n" : "")
				<< tabs.up()() << "std::cout << \"Hello World!\\n\";\n"
				<< (languageFlags.qt ? "\t// a.exec(); // event loop\n" : "")
				<< tabs() << "return 0;\n"
			<< "}\n" << std::endl;

	file.close();
}

void generateDirectoryNamedFiles(const std::string &dir)
{
	std::string fileName = dir + "/src/" + dir + ".h";
	std::fstream file(fileName, std::ios::out);
	indent tabs;

	file << "#pragma once\n\n"
		 << "#include <iostream>\n\n"
		 << "class " << dir << '\n'
		 << "{\n"
		 << "public:"
		 << tabs.up()() << dir << "() = default;\n"
		 << "};\n" << std::endl;
	file.close();

	fileName = dir + "/src/" + dir + ".cpp";
	file.open(fileName, std::ios::out);
	file << "#include \"" << dir << ".h\"\n" << std::endl;
	file.close();

	file.open(dir + "/src/CMakeLists.txt");
	file << "add_library(lib)\n\n"
		 << "target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})\n" << std::endl;
	file.close();
}

void generateCmakeFile(const std::string &dir, const flags &languageFlags)
{
	indent tabs;

	std::string fileName;
	fileName = dir + "/CMakeLists.txt";
	std::fstream file(fileName, std::ios::out);

	file << "cmake_minimum_required(VERSION " << cmakeVersion() << ")\n"
		<< "project(" << dir << " VERSION " << cmakeVersion() << ")\n\n"

		<< "set(CMAKE_CXX_STANDARD 17)\n"
		<< "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
		<< "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n";

	if (languageFlags.qt) {
		file << "# QT5 definition\nset(CMAKE_AUTOMOC ON)\n"
			<< "set(CMAKE_AUTORCC ON)\n"
			<< "set(CMAKE_AUTOUIC ON)\n\n"

			<< "if(CMAKE_VERSION VERSION_LESS \"3.7.0\")\n"
				<< tabs.up()() <<"set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
			<< tabs.down()() << "endif()\n\n"

			<< "find_package(Qt5 COMPONENTS Widgets REQUIRED)\n\n";
	}
	if (languageFlags.openCV) {
			file << "# OpenCV definition\nfind_package(OpenCV REQUIRED)\n\n";
	}

	file << "set(SOURCES\n"
			<< tabs.up()() << "main.cpp\n"
			<< ")\n"
		<< "set(HEADERS\n"
			<< ")\n\n"

		<< "add_subdirectory(src)\n\n"

		<< "add_executable(${PROJECT_NAME}\n"
			<< tabs() << "${SOURCES}\n"
			<< tabs() << "${HEADERS}\n"
		<< ")\n\n"

	 	<< "target_link_libraries(${PROJECT_NAME} PUBLIC lib)\n\n";

	if (languageFlags.qt) {
		file << "target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)\n"
			<< "target_link_directories(${PROJECT_NAME} PUBLIC QTDIR)\n" << std::endl;
	}
	if (languageFlags.openCV) {
		file << "target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})\n"
			<< "target_link_directories(${PROJECT_NAME} PUBLIC OpenCV_INCLUDE_DIRS)\n" << std::endl;
	}

	file.close();
}

void generateBuildFiles(const std::string &dir)
{
	indent tabs;
	std::string fileName = dir + "/build.sh";
	std::fstream file(fileName, std::ios::out);

	file << shellInit()
		<< "\ncd build/\nmake -j16\nif [ $? -eq 0 ];then\n" 
			<< tabs.up()() << "clear\n"
			<< tabs() << "./" << dir
		<< "\nfi\n" << std::endl;
	file.close();

	fileName = dir + "/compile.sh";
	file.open(fileName, std::ios::out);
	file << shellInit()
		 << "\n\nclear\ncd build/\nmake -j16\n" << std::endl;
	file.close();
}

