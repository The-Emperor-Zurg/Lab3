#include <ctime>
#include <iostream>
#include <vector>

#include "../lib/Creating_to_BMP.h"
#include "../lib/collapse.cpp"

int main(int argc, char* argv[]) {
    int start_time = clock();
    opt = Parser(argc, argv);
    std::vector<std::vector<uint64_t>> heap(opt.length, std::vector<uint64_t> (opt.width, 0));
    std::ifstream file;
    file.open(opt.tsv_file, std::ios::in);
    if (!file.is_open()) {
        return 0;
    }
    while (!file.eof()) {
        int x;
        int y;
        int value;
        file >> x >> y >> value;
        heap[x][y] = value;
    }
    file.close();
    uint32_t c = 0;
    uint32_t counter = 0;
    bool flag = true;
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
    uint32_t k = 1;

    if (opt.frequency == 0) {
        if (opt.max_iter == 0) {
            while (flag) {
                Ext(heap, up, right, down, left);
                Collapsing(heap, up, right, down, left, flag);
            }
        } else {
            while (c < opt.max_iter) {
                Ext(heap, up, right, down, left);
                Collapsing(heap, up, right, down, left, flag);
            }
        }
        char *name_file = new char[666];
        sprintf(name_file, "%s/%d.bmp", opt.res_file.c_str(), k);
        CreatingBMPFile(heap, opt.length, opt.width, name_file);
        delete[] name_file;
    } else {
        if (opt.max_iter == 0) {
            while (flag) {
                Ext(heap, up, right, down, left);
                //Extension(heap, up, right, down, left);
                Collapsing(heap, up, right, down, left, flag);
                ++c;
                ++counter;
                if (counter == opt.frequency) {
                    char* name_file = new char[666];
                    sprintf(name_file, "%s/%d.bmp", opt.res_file.c_str(), k);
                    CreatingBMPFile(heap, opt.length, opt.width, name_file);
                    delete[] name_file;
                    counter = 0;
                    ++k;
                }
            }
        }
        else {
            while (c < opt.max_iter) {
                Ext(heap, up, right, down, left);
                //Extension(heap, up, right, down, left);
                Collapsing(heap, up, right, down, left, flag);
                ++c;
                ++counter;
                if (counter == opt.frequency) {
                    char *name_file = new char[666];
                    sprintf(name_file, "%s/%d.bmp", opt.res_file.c_str(), k);
                    CreatingBMPFile(heap, opt.length, opt.width, name_file);
                    delete[] name_file;
                    counter = 0;
                    ++k;
                }
            }
        }
    }
    int end_time = clock();
    std::cout << end_time - start_time;
    return 0;
}
