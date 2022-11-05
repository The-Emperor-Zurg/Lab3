#pragma once

#include <cstdint>
#include <vector>

void CreatingBMPFile(const std::vector<std::vector<uint64_t>>& heap, uint16_t length, uint16_t width, const char* Name);
