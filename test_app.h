#ifndef _TEST_APP_H
#define _TEST_APP_H
#include <vector>
#include <cstdint>
#include <fstream>
#include <ostream>
#include <iostream>
#include <unistd.h>

namespace test_app {

enum AppMode { WORDS, CHECKSUM, HELP, NONE };

struct ParseArgs_t {
	AppMode mode;
	const char* filename;
	const char* keyword;
};

void parse_args (int argc, char* argv[]);
int read_bytes (const char* filename, std::vector<char> &buf);
uint32_t calc_checksum (const std::vector<char> &bytes);
int count_words (const char* filename, const char* keyword);
void print_message(std::ostream &os, const std::string &msg);
void display_help();

};

extern test_app::ParseArgs_t programArgs;

#endif