#include "include/Header.h"

int main(int argc, char ** argv){
	if(argc < 2){
			std::cerr << "\033[31mThe snippert is incorrect. Use it as buildProject [projectname] -t<language>\033[0m" << std::endl;
			return 1;
	}
	int option;
	flags opts;
	// printArgumets(argv);

	while((option = getopt(argc, argv,"qcmt:")) != -1){
		std::string newDir(argv[0]);
		switch(option){
			case 't': {
				std::string oarg(optarg);
				// std::cout << "OPTION t Marked\n";
				// printArgumets(argv);
				if(opts.typeFlag)
					std::cerr << RED << "Not allowed for multiple languages\n" << NORM << std::ends, exit(1);
				if(newDir.find("-") == 0) {
					std::cerr << RED << "Directory must be specified as a second argument buildProject [projectname] <-t language>\n"
							<< "Options:\n\t-q QT5 included (C++)\n\t-c OpenCV includec (C++)\n\t-m maven build system (Java)\n\n"
							<< "if language is not specified in particular option than it's ignored"<< NORM << std::endl, exit(2);
				}

				if(oarg == "java" || oarg == "j")
					opts.lang = flags::language::java, opts.typeFlag = true;
				else if(oarg == "cpp" || oarg == "c++" || oarg == "c")
					opts.lang = flags::language::cpp, opts.typeFlag = true;
				break;
			}

			case 'q':
				// std::clog << "QT marked\n";
				opts.qt = true;
				break;

			case 'c':
				opts.openCV = true;
				break;

			case 'm':
				std::cout << "setting m to true\n";
				opts.maven = true;
				break;

			default:
				std::perror("Getopt: "), opts.err = true;
		}
	}
	printArgumets(argv, argc);
	std::clog << "I am here\n";
	int idx = 2;
	if (opts.lang == flags::language::java) {
		if (opts.maven) {
			idx++;
		}
		std::clog << "Initialising javaCreation with index " << idx << "\n";
		javaCreation(argv[idx], opts.maven);
	} else if (opts.lang == flags::language::cpp) {
		if (opts.qt) {
			idx++;
			// std::clog << "Argument 3: " << argv[idx] << '\n';
		}
		if (opts.openCV) {
			idx++;
			std::clog << "Argument 3 OpenCV: " << argv[idx] << '\n';
		}
		cppCreation(argv[idx], opts);
	} else {
		std::cerr << "Filetype does not exist";
	}
}
