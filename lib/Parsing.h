#pragma once

#include <iostream>

struct Options {
    uint16_t length = 0;
    uint16_t width = 0;
    std::string tsv_file;
    std::string res_file;
    uint32_t max_iter = 0;
    uint32_t frequency = 0;
};

Options Parser (int argc, char* argv[]);
