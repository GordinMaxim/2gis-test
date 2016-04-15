#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include "test_app.h"

int main (int argc, char* argv[]) {
	test_app::parse_args(argc, argv);

	switch (programArgs.mode) {
		case test_app::AppMode::WORD: {
			if (!programArgs.filename || !programArgs.keyword) {
				test_app::print_message(std::cout, "mode WORD required filename and keyword\n");
				exit(0);
			}
			int count = test_app::count_words(programArgs.filename, programArgs.keyword);
			if (count < 0) {
				std::stringstream sstream;
				sstream << "Can't open file " << programArgs.filename << '\n';
				test_app::print_message(std::cout, sstream.str());	
			}
			std::stringstream sstream;
			sstream << count << " " << programArgs.keyword << " founded\n";
			test_app::print_message(std::cout, sstream.str());
			break;
		}
		case test_app::AppMode::CHECKSUM: {
			if (!programArgs.filename) {
				test_app::print_message(std::cout, "mode CHECKSUM required filename\n");
				exit(0);	
			}
			std::vector<char> bytebuf;
			if (test_app::read_bytes(programArgs.filename, bytebuf)) {
				std::stringstream sstream;
				sstream << "Can't read file " << programArgs.filename << '\n';
				test_app::print_message(std::cout, sstream.str());	
			}
			uint32_t checksum = test_app::calc_checksum(bytebuf);
			std::stringstream sstream;
			sstream << "Checksum of " << programArgs.filename << " - " << std::hex << checksum;
			test_app::print_message(std::cout, sstream.str());
			break;
		}
		case test_app::AppMode::HELP: {
			test_app::display_help();
		}
		default: {
			break;
		}
	}
	return 0;
}