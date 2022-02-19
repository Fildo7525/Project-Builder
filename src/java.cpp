#include "../include/Header.h"
#include <cstdlib>
#include <string>

void javaCreation(std::string dir, bool maven){
	std::string compile_command = "javac --release 11 -Werror -d ./debug ";


	std::string packageLocation;

	std::cout << "Enter the package name (com.example)[enter for default]: ";
	std::getline(std::cin, packageLocation);
	if (packageLocation.empty())
		packageLocation = DEFAULT_PACKAGE_LOCATION;

	auto slashedPackedLocation = replaceDots(packageLocation);

	std::string command = "mkdir " + dir + " && cd " + dir + " && touch compile.sh build.sh && chmod 711 compile.sh build.sh && mkdir -p " + slashedPackedLocation;// + " && touch Main.java";
	int trash = system(command.c_str());

	command = dir + "/" + slashedPackedLocation + "/Main.java";
	std::fstream file(command, std::ios::out);
	file << "package " << packageLocation << ";\n\npublic class Main {\n\tpublic static void main(String args[]){\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();

	if (!maven) {
		command = dir + "/compile.sh";
		file.open(command, std::ios::out);
		file << compile_command << slashedPackedLocation << "/Main.java" << std::ends;
		file.close();

		command = dir + "/build.sh";
		file.open(command, std::ios::out);
		file << compile_command << slashedPackedLocation << "/Main.java;\nif [ $? -eq 0 ]\nthen\n\tcd ./debug && java " << slashedPackedLocation << "/Main\nelse\n\trm -r *.class\nfi" << std::endl;
		file.close();
	}
	else {
		command = "mkdir -p " + dir + "/src/main/java && mv " + dir + "/" + slashedPackedLocation.substr(0, slashedPackedLocation.find_first_of("/")) + " " + dir + "/src/main/java";
		// std::clog << ORANGE << command << NORM << std::endl;
		compile_command = "mvnw install\nmvnw compile\n";

		int trash = system(command.c_str());
		slashedPackedLocation = "src/main/java/" + slashedPackedLocation;

		command = dir + "/pom.xml";
		file.open(command, std::ios::out);
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			 << "<project xmlns=\"http://maven.apache.org/POM/4.0.0\"\n"
					<< "\t\txmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
					<< "\t\txsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n"
			 	<< "\t<modelVersion>4.0.0</modelVersion>\n\n"

			<< "\t<groupId>" << packageLocation << "</groupId>\n"
			<< "\t<artifactId>" << dir << "</artifactId>\n"
			<< "\t<version>1.0-SNAPSHOT</version>\n\n"

			<< "\t<properties>\n"
				<< "\t\t<maven.compiler.source>11</maven.compiler.source>\n"
				<< "\t\t<maven.compiler.target>11</maven.compiler.target>\n"
			 << "\t</properties>\n"
			<< "</project>" << std::endl;
		file.close();

		command = dir + "/build.sh";
		file.open(command, std::ios::out);
		file << "mvn clean install\n"
			<< "# mvn dependency:\n"
			<< "if [[ $? == 0 ]]; then\n"
			<< "\tclean\n\tjava -Dfile.encoding=UTF-8 -cp ./target/classes " << packageLocation << ".Main\n"
			<< "fi" << std::endl;
		file.close();

		command = dir + "/compile.sh";
		file.open(command, std::ios::out);
		file << "mvn clean install\n"
			<< "# mvn dependency:\n" << std::endl;
		file.close();
	}
}


std::string replaceDots(const std::string &packagePath)
{
	auto copy = packagePath;
	for(auto &letter : copy)
	{
		if (letter == '.')
			letter = '/';
	}
	return copy;
}


void printArgunets(char **argv)
{
	int i = 0;
	for ( ; i < 4; i++) {
		std::clog << "Argument " << i << ": " << argv[i] << '\n';
	}
}
