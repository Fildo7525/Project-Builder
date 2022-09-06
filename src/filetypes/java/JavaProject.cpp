#include "JavaProject.h"

#include <algorithm>
#include <fstream>

JavaProject::JavaProject(const std::string &dir, const flags &languageFlags)
	: Project(dir, languageFlags)
{
}

void JavaProject::generate()
{
	linuxAndJavaPaths();

	std::cout << "slashed: " << m_slashedPackedLocation << std::endl;

	std::string command = "mkdir " + m_dir + " && cd " + m_dir + " && touch compile.sh build.sh && chmod 711 compile.sh build.sh && mkdir -p "
							+ m_slashedPackedLocation;
	executeCommand(command, INITIALIZE_DIR_ERROR);

	generateMainFile();

	generateBuildFiles();

	if (m_languageFlags.maven) {
		command = "mkdir -p " + m_dir + "/src/main/java " + m_dir + "/src/test/java && mv "
				+ m_dir + "/" + m_slashedPackedLocation.substr(0, m_slashedPackedLocation.find_first_of("/"))
				+ " " + m_dir + "/src/main/java && chmod 666 " + m_dir + "/src/main/java/" + m_slashedPackedLocation + "/Main.java";

		executeCommand(command);

		generatePomXML();
	}
}

std::string JavaProject::pathFromJavaPackagePath()
{
	std::string copy = m_packageLocation;
	std::replace_copy_if(m_packageLocation.begin(), m_packageLocation.end(), copy.begin(), [](const char c){ return c == '.'; }, '/');
	std::cout << "copy: " << copy << std::endl;
	return copy;
}

void JavaProject::linuxAndJavaPaths()
{
	std::cout << "Enter the package name e.g. com.example (default): ";
	std::getline(std::cin, m_packageLocation);
	if (m_packageLocation.empty())
		m_packageLocation = DEFAULT_PACKAGE_LOCATION;

	m_slashedPackedLocation = pathFromJavaPackagePath();
	std::cout << "slashedLocation: " << m_slashedPackedLocation << std::endl;
}

void JavaProject::generateMainFile()
{
	std::string fileName = m_dir + "/" + m_slashedPackedLocation + "/Main.java";

	std::fstream file(fileName, std::ios::out);
	file << "package " << m_packageLocation << ";\n\npublic class Main {\n\tpublic static void main(String args[]) {\n\t\tSystem.out.println(\"Hallo World!\");\n\t}\n}" << std::endl;
	file.close();
}

void JavaProject::generatePomXML()
{
	std::string fileName = m_dir + "/pom.xml";
	indent tabs;
	tabs.up().up();

	std::fstream file(fileName, std::ios::out);
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		 << "<project xmlns=\"http://maven.apache.org/POM/4.0.0\"\n"
				<< tabs() << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
				<< tabs() << "xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n"
			<< tabs.down()() << "<modelVersion>4.0.0</modelVersion>\n\n"

		<< tabs.down()() << "<groupId>" << m_packageLocation << "</groupId>\n"
		<< tabs() << "<artifactId>" << m_dir << "</artifactId>\n"
		<< tabs() << "<version>1.0-SNAPSHOT</version>\n\n"

		<< tabs() << "<properties>\n"
			<< tabs.up()() << "<maven.compiler.source>11</maven.compiler.source>\n"
			<< tabs() << "<maven.compiler.target>11</maven.compiler.target>\n"
		 << tabs.down()() << "</properties>\n"
		<< "</project>" << std::endl;
	file.close();
}

void JavaProject::generateBuildFiles()
{
	std::string compile_command = "javac --release 11 -Werror -d ./debug ";

	std::string fileName = m_dir + "/compile.sh";

	std::fstream file(fileName, std::ios::out);
	file << shellInit() << '\n';

	if (!m_languageFlags.maven) {
		file << compile_command << m_slashedPackedLocation << "/Main.java\n" << std::endl;
	}
	else {
		file << "mvn clean install\n" << std::endl;
	}
	file.close();

	fileName = m_dir + "/build.sh";

	file.open(fileName, std::ios::out);
	file << shellInit() << '\n';

	if (!m_languageFlags.maven) {
		file << compile_command << m_slashedPackedLocation << "/Main.java;\n"
			<< "if [ $? -eq 0 ]\nthen\n\tcd ./debug && java " << m_slashedPackedLocation << "/Main\nelse\n\trm -r *.class\nfi" << std::endl;
	}
	else {
		file << "mvn clean install\n"
			<< "if [[ $? == 0 ]]; then\n"
			<< "\tclear\n\tjava -Dfile.encoding=UTF-8 -cp ./target/classes " << m_packageLocation << ".Main\n"
			<< "fi" << std::endl;
	}
	file.close();
}

