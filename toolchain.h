#pragma once

#include <iostream>
#include <fstream>
#include "shell.h"
#include "stringutils.h"

int assemble(std::string *opt_src, std::string *opt_out, bool opt_verbose) {
	std::string msg_asm = systemRes(("lib\\xtensa-lx106-elf-as.exe --strip-local-absolute -a " + std::string(*opt_src == "" ? "asm.S" : opt_src->c_str())).c_str());

	if (msg_asm.find("Error:", 0) != std::string::npos) {
		std::cerr << "Assembler error:" << std::endl << std::endl << msg_asm << std::endl << std::endl << "ASSEMBLING HALTED!" << std::endl;
		return -1;
	}

	if (opt_verbose)
		std::cout << "Assembler:" << std::endl << std::endl << msg_asm << std::endl << std::endl << std::endl;

	return 0;
}

int objdump(std::string *opt_src, std::string *opt_out, bool opt_verbose) {
	std::string msg_objd = systemRes("lib\\xtensa-lx106-elf-objdump.exe -s a.out");

	std::deque<std::string*> data;
	int size;

	//Split to Sections
	splitString(msg_objd, "Contents of section ", data, size);

	if (size == 0) {
		std::cerr << "Objdump error:" << std::endl << std::endl << msg_objd << std::endl << std::endl << "ASSEMBLING HALTED!" << std::endl;
		return -1;
	}

	if (opt_verbose)
		std::cout << "Objdump:" << std::endl << std::endl << msg_objd << std::endl << std::endl << std::endl;

	//Skip first section (not a section)
	data.pop_front();

	for (int i = 0; i < size - 1; i++) {
		std::string output;

		std::deque<std::string*> lines;
		int lcount;
		//split to lines
		splitString(*data[i], "\n", lines, lcount);

		//Über zeilen iterieren
		for (int l = 1; l < lcount; l++) {
			//Skip empty lines
			if (*lines[l] == "")
				continue;

			const char *line = lines[l]->c_str();

			//Go to Data
			for (int spaces = 0; spaces < 2;) {
				if (*line == ' ') spaces++;
				line++;
			}

			//Über Data interieren
			while (!(*line == ' ' && *(line - 1) == ' ')) {
				for (int c = 0; c < 4; c++) {
					output += "0x";
					output += *line;
					line++;
					output += *line;
					line++;
					output += ", ";
				}
				line++;
			}
		}

		//Remove last comma
		output.pop_back();
		output.pop_back();

		lines[0]->pop_back();

		std::ofstream out;
		out.open((*opt_out == "" ? std::string("") : *opt_out) + "section" + *lines[0] + ".rhex", std::ios::out);
		out << output << std::flush;
		out.close();
	}
	return 0;
}

int disassemble(std::string *opt_src, std::string *opt_out, bool opt_verbose) {
	std::string msg_objd = systemRes("lib\\xtensa-lx106-elf-objdump.exe -d a.out");

	std::deque<std::string*> data;
	int size;

	//Split to Sections
	splitString(msg_objd, "Disassembly of section ", data, size);

	if (size == 0) {
		std::cerr << "Diasassemble error:" << std::endl << std::endl << msg_objd << std::endl << std::endl << "ASSEMBLING HALTED!" << std::endl;
		return -1;
	}

	//Skip first section (not a section)
	data.pop_front();

	std::cout << "Optimized Assembly:" << std::endl << std::endl;

	for (int i = 0; i < size - 1; i++) {
		std::cout << "Section " << *data[i] << std::endl;
	}
	return 0;
}

