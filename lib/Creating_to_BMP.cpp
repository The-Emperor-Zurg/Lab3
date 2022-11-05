#include <cstdio>
#include <fstream>

#include "Creating_to_BMP.h"

const short int kBytesPerPixel = 3;
const short int kSizeHeader = 14;
const short int kSizeInfoHeader = 40;

void CreatingBMPFile(const std::vector<std::vector<uint64_t>>& heap, const uint16_t length, const uint16_t width, const char* Name) {

    char padding[3] = {0, 0, 0};
    const uint64_t paddingSize = (4 - (length * 3) % 4) % 4;

    std::ofstream file;
    file.open(Name, std::ios::out | std::ios::binary);

    size_t fileSize = width * length * 3 + paddingSize * length + kSizeHeader + kSizeInfoHeader;
    static char fileHeader[] = {
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0
    };
    fileHeader[0] = static_cast<char>('B');
    fileHeader[1] = static_cast<char>('M');
    fileHeader[2] = static_cast<char>(fileSize);
    fileHeader[3] = static_cast<char>(fileSize >> 8);
    fileHeader[4] = static_cast<char>(fileSize >> 16);
    fileHeader[5] = static_cast<char>(fileSize >> 24);
    fileHeader[10] = static_cast<char>(kSizeHeader + kSizeInfoHeader);

    file.write(reinterpret_cast<char*>(fileHeader), kSizeHeader);

    static char infoHeader[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    infoHeader[0] = static_cast<char>(kSizeInfoHeader);
    infoHeader[4] = static_cast<char>(length);
    infoHeader[5] = static_cast<char>(length >> 8);
    infoHeader[6] = static_cast<char>(length >> 16);
    infoHeader[7] = static_cast<char>(length >> 24);

    infoHeader[8] = static_cast<char>(width);
    infoHeader[9] = static_cast<char>(width >> 8);
    infoHeader[10] = static_cast<char>(width >> 16);
    infoHeader[11] = static_cast<char>(width >> 24);

    infoHeader[12] = static_cast<char>(1);
    infoHeader[14] = static_cast<char>(kBytesPerPixel * 8);

    file.write(reinterpret_cast<char*>(infoHeader), kSizeInfoHeader);


    for (int i = width - 1; i >= 0; i--) {
        for (int j = 0; j < length; j++) {
            uint64_t value = heap[i][j];
            uint8_t color[3];
            if (value == 0) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
            if (value == 1) {
                color[0] = 0;
                color[1] = 255;
                color[2] = 0;
            }
            if (value == 2) {
                color[0] = 128;
                color[1] = 0;
                color[2] = 128;
            }
            if (value == 3) {
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
            }
            if (value >= 4) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(padding, paddingSize);
    }
    file.close();
    printf("Made %s \n", Name);
}
