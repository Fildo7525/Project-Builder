#include "../include/Header.h"
#include "core.h"
#include <string>


void makeJavaProject(const std::string &dir, const flags &languageFlags)
{
	auto [slashedPackedLocation, packageLocation] = linuxAndJavaPaths();

	std::string command = "mkdir " + dir + " && cd " + dir + " && touch compile.sh build.sh && chmod 711 compile.sh build.sh && mkdir -p "
							+ slashedPackedLocation;
	executeCommand(command, INITIALIZE_DIR_ERROR);

	generateMainFile(dir, slashedPackedLocation, slashedPackedLocation);

	generateBuildFiles(dir, slashedPackedLocation, packageLocation, languageFlags.maven);

	if (languageFlags.maven) {
		command = "mkdir -p " + dir + "/src/main/java && mv " + dir + "/" + slashedPackedLocation.substr(0, slashedPackedLocation.find_first_of("/")) 
				+ " " + dir + "/src/main/java && chmod 666 " + dir + "/src/main/java/" + slashedPackedLocation + "/Main.java";
		std::clog << command << std::endl;

		executeCommand(command);

		generatePomXML(dir, packageLocation);
	}
}

std::string pathFromJavaPackagePath(const std::string &packagePath)
{
	std::string copy = packagePath;
	std::replace_copy_if(packagePath.begin(), packagePath.end(), copy.begin(), [](const char c){ return c == '.'; }, '/');
	return copy;
}

std::pair<std::string, std::string> linuxAndJavaPaths()
{
	std::string packageLocation;

	std::cout << "Enter the package name (com.example)[enter for default]: ";
	std::getline(std::cin, packageLocation);
	if (packageLocation.empty())
		packageLocation = DEFAULT_PACKAGE_LOCATION;

	auto slashedPackedLocation = pathFromJavaPackagePath(packageLocation);
	return {slashedPackedLocation, packageLocation};
}

void generateMainFile(const std::string &dir, const std::string &slashedPackedLocation, const std::string &packageLocation)
{
	std::string command = dir + "/" + slashedPackedLocation + "/Main.java";
	std::clog << command << '\n';
	std::fstream file(command, std::ios::out);
	file << "package " << packageLocation << ";\n\npublic class Main {\n\tpublic static void main(String args[]){\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();
}

void generatePomXML(const std::string &dir, const std::string &packageLocation)
{
	std::string command = dir + "/pom.xml";
	std::clog << command << '\n';
	indent tabs;
	tabs.up().up();

	std::fstream file(command, std::ios::out);
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		 << "<project xmlns=\"http://maven.apache.org/POM/4.0.0\"\n"
				<< tabs() << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
				<< tabs() << "xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n"
			<< tabs.down()() << "<modelVersion>4.0.0</modelVersion>\n\n"

		<< tabs.down()() << "<groupId>" << packageLocation << "</groupId>\n"
		<< tabs() << "<artifactId>" << dir << "</artifactId>\n"
		<< tabs() << "<version>1.0-SNAPSHOT</version>\n\n"

		<< tabs() << "<properties>\n"
			<< tabs.up()() << "<maven.compiler.source>11</maven.compiler.source>\n"
			<< tabs() << "<maven.compiler.target>11</maven.compiler.target>\n"
		 << tabs.down()() << "</properties>\n"
		<< "</project>" << std::endl;
	file.close();
}

void generateBuildFiles(const std::string &dir, const std::string &slashedPackedLocation, const std::string &packageLocation, bool maven)
{
	std::string compile_command = "javac --release 11 -Werror -d ./debug ";
	std::cout << compile_command << '\n';

	std::string command = dir + "/compile.sh";
	std::clog << command << '\n';
	std::fstream file(command, std::ios::out);
	if (!maven) {
		file << compile_command << slashedPackedLocation << "/Main.java" << std::ends;
	}
	else {
		file << shellInit() << '\n'
			<< "mvn clean install\n"
			<< "# mvn dependency:\n" << std::endl;
	}
	file.close();

	command = dir + "/build.sh";
	std::clog << command << '\n';
	file.open(command, std::ios::out);
	if (!maven) {
		file << compile_command << slashedPackedLocation << "/Main.java;\nif [ $? -eq 0 ]\nthen\n\tcd ./debug && java " << slashedPackedLocation << "/Main\nelse\n\trm -r *.class\nfi" << std::endl;
	}
	else {
		file << shellInit() << '\n'
			<< "mvn clean install\n"
			<< "# mvn dependency:\n"
			<< "if [[ $? == 0 ]]; then\n"
			<< "\tclear\n\tjava -Dfile.encoding=UTF-8 -cp ./target/classes " << packageLocation << ".Main\n"
			<< "fi" << std::endl;
	}
	file.close();
}

