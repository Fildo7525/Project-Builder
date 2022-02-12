#include "../include/Header.h"

void javaCreation(std::string dir){
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

	command = dir + "/compile.sh";
	file.open(command, std::ios::out);
	file << compile_command << slashedPackedLocation << "/Main.java"<< std::endl;
	file.close();

	command = dir + "/build.sh";
	file.open(command, std::ios::out);
	file << compile_command << slashedPackedLocation << "/Main.java;\nif [ $? -eq 0 ]\nthen\n\tcd ./debug && java " << slashedPackedLocation << "/Main\nelse\n\trm -r *.class\nfi" << std::endl;
	file.close();
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
