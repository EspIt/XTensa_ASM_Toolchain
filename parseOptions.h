#pragma once
#include <string>
#include <iostream>
#include "getopt.h"

int parseOptions(char* argv[], int argc, std::string& opt_src, std::string& opt_out, bool *opt_verbose){
	int c;

	while ((c = getopt(argc, argv, "s:o:vh")) != -1)
	switch (c)
	{
	case 's':
		opt_src = std::string(optarg);
		break;
	case 'o':
		opt_out = std::string(optarg);
		break;
	case 'v':
		*opt_verbose = true;
		break;
	case 'h':
		std::cout << "Usage:" << std::endl << "-s <file>\tSpecify Assembly Source file (relative)" << std::endl << "-o <path>\tSpecify output directory" << std::endl << "-v\t\tEnables verbose logging" << std::endl << "-h\t\tShows this help" << std::endl << std::endl;
		break;
	case '?':
		if (optopt == 's' || optopt == 'o')
			std::cerr << "Option -" << char(optopt) << " requires an argument. See -h for details." << std::endl;
		else if (isprint(optopt))
			std::cerr << "Unknown option -" << char(optopt) << ". See -h for available options." << std::endl;
		else
			std::cerr << "Unknown character (unprintable)." << std::endl;
		return 1;
	default:
		abort();
	}

	return 0;
}