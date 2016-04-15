#include "test_app.h"

static const std::string help_msg = 
"Usage: ./testapp [-f <filename> -m <mode> {-v <keyword>}] | -h\n \
-m [word|checksum] -- -m 'word' print the 'keyword' count, required option -v, -m 'checksum' calculate 32bit checksum\n \
-h -- display help info\n";

static const char* stringOpts = "f:m:v:h";

test_app::ParseArgs_t programArgs;

void test_app::parse_args (int argc, char* argv[]) {
	int opt = 0;
	programArgs.mode = AppMode::NONE;
	programArgs.filename = nullptr;
	programArgs.keyword = nullptr;

	opt = getopt(argc, argv, stringOpts);
	while (-1 != opt) {
		switch (opt) {
			case 'f': {
				programArgs.filename = optarg;
				break;
			}
			case 'm': {
				if (NONE == programArgs.mode) {
					std::string modeName(optarg);
					if (0 == modeName.compare("words")) {
						programArgs.mode = AppMode::WORD;
					} else if (0 == modeName.compare("checksum")) {
						programArgs.mode = AppMode::CHECKSUM;
					} else {
						print_message(std::cout, "Uknown mode\n");
						display_help();
					}
				} 
				break;	
			}
			case 'h': {
				if (NONE == programArgs.mode) {
					programArgs.mode = AppMode::HELP;
				}
				break;
			}
			case 'v': {
				programArgs.keyword = optarg;
				break;
			}
			default: {
				break;
			}
		}
		opt = getopt(argc, argv, stringOpts);
	}
}

int test_app::read_bytes (const char* filename, std::vector<char> &buf) {
	std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
	if (!ifs) {
		return 1;
	}

	int pos = ifs.tellg();
	buf.resize(pos);
	ifs.seekg(0, std::ios::beg);
	ifs.read(&buf[0], pos);

	return 0;
}

uint32_t test_app::calc_checksum (const std::vector<char> &bytes) {
	uint32_t checksum = 0;
	unsigned int shift = 0;

	for (auto it = bytes.begin(); it != bytes.end(); ++it) {
		checksum += (*it << shift);
		shift += 8;
		if (32 == shift) {
			shift = 0;
		}
	}

	return checksum;
}

int test_app::count_words (const char* filename, const char* keyword) {
	std::ifstream ifs(filename);
	if (!ifs) {
		return -1;
	}

	std::string token;
	int count = 0;
	while (ifs >> token) {
		if (0 == token.compare(keyword)) {
			++count;
		}
	}

	return count;
}

void test_app::print_message(std::ostream &os, const std::string &msg) {
	os << msg;
}

void test_app::display_help() {
	print_message(std::cout, help_msg);
}
