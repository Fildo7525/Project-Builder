#include "include/Header.h"
#include <cstdio>

int main(int argc, char ** argv){
	if(argc < 2){
			std::cerr << "\033[31mThe snippert is incorrect. Use it as buildProject [projectname] -t<language>\033[0m" << std::endl;
			return 1;
	}
	int option;
	flags opts;
	// printArgunets(argv);

	while((option = getopt(argc, argv,"qmt:")) != -1){
		std::string newDir(argv[0]);
		switch(option){
			case 't': {
				std::string oarg(optarg);
				// std::cout << "OPTION t Marked\n";
				// printArgunets(argv);
				if(opts.typeFlag)
					std::cerr << RED << "Not allowed\n" << NORM << std::ends, exit(1);
				if(newDir.find("-") == 0)
					std::cerr << RED << "Directory must be specified as a second argument buildProject [projectname] <-t language>" << NORM << std::endl, exit(2);

				if(oarg == "java" || oarg == "j")
					opts.t = flags::language::java, opts.typeFlag = true;
				else if(oarg == "cpp" || oarg == "c++" || oarg == "c")
					opts.t = flags::language::cpp, opts.typeFlag = true;
				break;
			}

			case 'q':
				// std::clog << "QT marked\n";
				opts.q = true;
				break;

			case 'm':
				opts.m = true;
				break;
			default:
				std::perror("Getopt: "), opts.err = true;
		}
	}
	// printArgunets(argv);
	int idx = 2;
	if (opts.t == flags::language::java) {
		if (opts.m) {
			idx = 3;
		}
		javaCreation(argv[idx], opts.m);
	} else {
		if (opts.q) {
			idx = 3;
			// std::clog << "Argument 3: " << argv[3] << '\n';
		}
		cppCreation(argv[idx], opts.q);
	}
}
