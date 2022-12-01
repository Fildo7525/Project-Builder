#include "BuildProject.h"
#include "core.h"
#include <string>

#define AOC_HEADERS "#include <fstream>\n#include <algorithm>\n#include <iterator>\n#include <numeric>\n#include <vector>\n"

CppProject::CppProject(const std::string &directory, const flags &options)
	: Project(directory, options)
{
}

void CppProject::generate()
{
	std::cout << "m_dir: " << m_dir << std::endl;
	std::string command = "mkdir -p " + m_dir + "/src && cd " + m_dir + " && touch src/" + m_dir + ".cpp src/" + m_dir + ".h src/CMakeLists.txt build.sh compile.sh && chmod +x build.sh compile.sh";
	executeCommand(command, INITIALIZE_DIR_ERROR);

	generateMainFile();

	generateDirectoryNamedFiles();

	generateCmakeFile();

	generateBuildFiles();

	command = "cd " + m_dir + " && cmake CMakeLists.txt -S . -B ./build && cp ./build/compile_commands.json .";

	executeCommand(command);
	if (m_languageFlags.aoc) {
		command = "touch " + m_dir + "/input " + m_dir + "/test";
		executeCommand(command, "The files test and input could not be created");
	}
}

std::string CppProject::cmakeVersion()
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

void CppProject::generateMainFile()
{
	indent tabs;
	std::string command = m_dir + "/main.cpp";

	std::fstream file(command, std::ios::out);
	if (m_languageFlags.qt)
		file << "// QT include files\n#include <QCoreApplication>\n\n";
	if (m_languageFlags.openCV)
		file << "// OpenCV include files\n#include <opencv2/highgui.hpp>\n\n";

	file << "#include \"" << m_dir << ".h\"\n\nint main(int argc, char *argv[])\n{\n"
				<< (m_languageFlags.qt ? "\tQCoreApplication a(argc, argv);\n" : "")
				<< (m_languageFlags.aoc ? "\tstd::fstream input(\"../input\", std::ios::in);\n\tstd::string line;" : "")
				<< (m_languageFlags.aoc ? "while (std::getline(input, line)) {\n\t}\n" : "")
				<< tabs.up()() << "std::cout << \"Hello World!\\n\";\n"
				<< (m_languageFlags.qt ? "\t// a.exec(); // event loop\n" : "")
				<< tabs() << "return 0;\n"
			<< "}\n" << std::endl;

	file.close();
}

void CppProject::generateDirectoryNamedFiles()
{
	std::string fileName = m_dir + "/src/" + m_dir + ".h";
	std::fstream file(fileName, std::ios::out);
	indent tabs;

	file << "#pragma once\n\n"
		 << "#include <iostream>\n"
		 << (m_languageFlags.aoc ? AOC_HEADERS : "")
		 << (m_languageFlags.qt ? "#include <QObject>\n\n" : "\n")
		 << "class " << m_dir << (m_languageFlags.qt ? "\n\t: public QObject" : "") << '\n'
		 << "{\n"
		 << (m_languageFlags.qt ? "\tQ_OBJECT;\n" : "")
		 << "public:\n"
		 << tabs.up()() << m_dir <<(m_languageFlags.qt ? "(QObject *parent = nullptr);" : "() = default;\n\n")
		 << (m_languageFlags.qt ? "\nsignals:\n\npublic slots:\n" : "")
		 << "};\n" << std::endl;
	file.close();

	fileName = m_dir + "/src/" + m_dir + ".cpp";
	file.open(fileName, std::ios::out);
	file << "#include \"" << m_dir << ".h\"\n" << std::endl;
	if (m_languageFlags.qt) {
		file << m_dir << "::" << m_dir << "(QObject *parent)\n"
			 << "\t: QObject(parent)\n"
			 << "{\n"
			 << "}\n" << std::endl;
	}
	file.close();

	file.open(m_dir + "/src/CMakeLists.txt");
	file << "add_library(lib\n"
		 << tabs() << m_dir << ".cpp\n"
		 << tabs() << m_dir << ".h\n"
		 << ")\n\n"
		 << "target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})\n" << std::endl;
	if (m_languageFlags.qt) {
		file << "target_include_directories(\n\tlib\nPUBLIC\n\t${CMAKE_CURRENT_SOURCE_DIR}\n\tQTDIR\n)\n"
			 << "target_link_libraries(lib PUBLIC Qt5::Widgets)\n" << std::endl;
	}
	if (m_languageFlags.openCV) {
		file << "target_link_libraries(lib PUBLIC ${OpenCV_LIBS})\n"
			 << "target_link_directories(lib PUBLIC OpenCV_INCLUDE_DIRS)\n" << std::endl;
	}
	file.close();
}

void CppProject::generateCmakeFile()
{
	indent tabs;

	std::string fileName;
	fileName = m_dir + "/CMakeLists.txt";
	std::fstream file(fileName, std::ios::out);

	file << "cmake_minimum_required(VERSION " << cmakeVersion() << ")\n"
		<< "project(" << m_dir << " VERSION " << cmakeVersion() << ")\n\n"

		<< "set(CMAKE_CXX_STANDARD 17)\n"
		<< "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
		<< "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n";

	if (m_languageFlags.qt) {
		file << "# QT5 definition\nset(CMAKE_AUTOMOC ON)\n"
			<< "set(CMAKE_AUTORCC ON)\n"
			<< "set(CMAKE_AUTOUIC ON)\n\n"

			<< "if(CMAKE_VERSION VERSION_LESS \"3.7.0\")\n"
				<< tabs.up()() <<"set(CMAKE_INCLUDE_CURRENT_DIR ON)\n"
			<< tabs.down()() << "endif()\n\n"

			<< "find_package(Qt5 COMPONENTS Widgets REQUIRED)\n\n";
	}
	if (m_languageFlags.openCV) {
			file << "# OpenCV definition\nfind_package(OpenCV REQUIRED)\n\n";
	}
	if (m_languageFlags.rasPi) {
			file << "find_library(WIRINGPI_LIBRARIES NAMES wiringPi)\n\n";
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

		<< "target_link_libraries(\n\t${PROJECT_NAME}\nPUBLIC\n\tlib";
	if (m_languageFlags.rasPi)
		file << "\n\t${WIRINGPI_LIBRARIES}";
	if (m_languageFlags.qt)
		file << "\n\tQt5::Widgets";
	if (m_languageFlags.openCV)
		file << "\n\t${OpenCV_LIBS}";

	file << "\n)\n\n";

	if (m_languageFlags.qt || m_languageFlags.openCV) {
		file << "target_link_directories(\n\t${PROJECT_NAME}\nPUBLIC";
		if (m_languageFlags.qt)
			file << "\n\tQTDIR";
		if (m_languageFlags.openCV)
			file << "\n\tOpenCV_INCLUDE_DIRS";

		file << "\n)\n" << std::endl;
	}

	file.close();
}

void CppProject::generateBuildFiles()
{
	indent tabs;
	std::string fileName = m_dir + "/build.sh";
	std::fstream file(fileName, std::ios::out);

	file << shellInit()
		<< "\ncd build/\nmake -j16\nif [ $? -eq 0 ];then\n" 
			<< tabs.up()() << "clear\n"
			<< tabs() << "./" << m_dir
		<< "\nfi\n" << std::endl;
	file.close();

	fileName = m_dir + "/compile.sh";
	file.open(fileName, std::ios::out);
	file << shellInit()
		 << "\n\nclear\ncd build/\nmake -j16\n" << std::endl;
	file.close();
}

