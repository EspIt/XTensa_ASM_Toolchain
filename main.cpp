#include <stdio.h>
#include "parseOptions.h"
#include "toolchain.h"

std::string opt_src = "";
std::string opt_out = "";
bool opt_verbose = false;

int main(int argc, char* argv[]){

	//---------------------------------------------Parse
	if (parseOptions(argv, argc, opt_src, opt_out, &opt_verbose) == 1)
		return -1;

	if (opt_out != "" && opt_out.back() != '\\') opt_out += "\\";

	//---------------------------------------------Assembly
	if (assemble(&opt_src, &opt_out, opt_verbose) == -1)
		return -1;
	
	//---------------------------------------------Objdump
	if (objdump(&opt_src, &opt_out, opt_verbose) == -1)
		return -1;

	//---------------------------------------------Disassembly
	if (disassemble(&opt_src, &opt_out, opt_verbose) == -1)
		return -1;

	remove("a.out");

	return 0;
}