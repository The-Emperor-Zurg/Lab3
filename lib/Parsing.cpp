//Parser
#include <string>

#include "Parsing.h"

Options Parser (int argc, char* argv[]) {
    Options options;
    for (size_t i = 1; i < argc; i+=2 ) {
        std::string s = argv[i];

        if (s == "-l" || s == "--length") {
            options.length = std::atoi(argv[i + 1]);
        }
        if (s == "-w" || s == "--width") {
            options.width = std::atoi(argv[i + 1]);
        }
        if (s == "-i" || s == "--input") {
            options.tsv_file = argv[i + 1];
        }
        if (s == "-o" || s == "--output") {
            options.res_file = argv[i + 1];
        }
        if (s[1] == 'm' || s == "--max-iter") {
            options.max_iter = std::atoi(argv[i + 1]);
        }
        if (s[1] == 'f' || s == "--freq") {
            options.frequency = std::atoi(argv[i + 1]);
        }
    }

    if (options.length == 0 || options.width == 0 || options.tsv_file == "" || options.res_file == "") {
        std::exit(0);
    }

    return options;
}
