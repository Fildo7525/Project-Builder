#include "../include/Header.h"

void makeJavaProject(const std::string &dir, bool maven)
{
	std::string packageLocation;

	std::cout << "Enter the package name (com.example)[enter for default]: ";
	std::getline(std::cin, packageLocation);
	if (packageLocation.empty())
		packageLocation = DEFAULT_PACKAGE_LOCATION;

	auto slashedPackedLocation = pathFromJavaPackagePath(packageLocation);

	std::string command = "mkdir " + dir + " && cd " + dir + " && touch compile.sh build.sh && chmod 711 compile.sh build.sh && mkdir -p "
							+ slashedPackedLocation;
	std::clog << command << '\n';
	system(command.c_str());

	command = dir + "/" + slashedPackedLocation + "/Main.java";
	std::clog << command << '\n';
	std::fstream file(command, std::ios::out);
	file << "package " << packageLocation << ";\n\npublic class Main {\n\tpublic static void main(String args[]){\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();

	if (!maven) {
		std::string compile_command = "javac --release 11 -Werror -d ./debug ";
		std::cout << compile_command << '\n';

		command = dir + "/compile.sh";
		std::clog << command << '\n';
		file.open(command, std::ios::out);
		file << compile_command << slashedPackedLocation << "/Main.java" << std::ends;
		file.close();

		command = dir + "/build.sh";
		std::clog << command << '\n';
		file.open(command, std::ios::out);
		file << compile_command << slashedPackedLocation << "/Main.java;\nif [ $? -eq 0 ]\nthen\n\tcd ./debug && java " << slashedPackedLocation << "/Main\nelse\n\trm -r *.class\nfi" << std::endl;
		file.close();
	}
	else {
		command = "mkdir -p " + dir + "/src/main/java && mv " + dir + "/" + slashedPackedLocation.substr(0, slashedPackedLocation.find_first_of("/")) 
				+ " " + dir + "/src/main/java && chmod 666 " + dir + "/src/main/java/" + slashedPackedLocation + "/Main.java";
		std::clog << command << std::endl;
		// std::clog << ORANGE << command << NORM << std::endl;

		system(command.c_str());

		command = dir + "/pom.xml";
		std::clog << command << '\n';
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
		std::clog << command << '\n';
		file.open(command, std::ios::out);
		file << shellInit() << '\n'
			<< "mvn clean install\n"
			<< "# mvn dependency:\n"
			<< "if [[ $? == 0 ]]; then\n"
			<< "\tclear\n\tjava -Dfile.encoding=UTF-8 -cp ./target/classes " << packageLocation << ".Main\n"
			<< "fi" << std::endl;
		file.close();

		command = dir + "/compile.sh";
		std::clog << command << '\n';
		file.open(command, std::ios::out);
		file << shellInit() << '\n'
			<< "mvn clean install\n"
			<< "# mvn dependency:\n" << std::endl;
		file.close();
	}
}

std::string pathFromJavaPackagePath(const std::string &packagePath)
{
	std::string copy = packagePath;
	std::replace_copy_if(packagePath.begin(), packagePath.end(), copy.begin(), [](const char c){ return c == '.'; }, '/');
	return copy;
}

