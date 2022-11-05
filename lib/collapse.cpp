#include <fstream>
#include <vector>

#include "Parsing.h"

Options opt;

void Ext(std::vector<std::vector<uint64_t>>& v, bool& up, bool& right, bool& down, bool& left) {

    if (v[0][0] > 3) {
        up = true;
        left = true;
    }
    if (v[0][opt.width - 1] > 3) {
        up = true;
        right = true;
    }
    if (v[opt.length - 1][opt.width - 1] > 3) {
        right = true;
        down = true;
    }
    if (v[opt.length - 1][0] > 3) {
        left = true;
        down = true;
    }

    if (up & right & down & left) {
        return;
    }

    for (size_t j = 1; j < opt.width - 1; ++j) {
        if (v[0][j] > 3) {
            up = true;
            break;
        }
    }

    for (size_t i = 1; i < opt.length - 1; ++i) {
        if (v[i][0] > 3) {
            left = true;
        }
    }

    for (size_t i = 1; i < opt.length - 1; ++i) {
        if (v[i][opt.width - 1] > 3) {
            right = true;
        }
    }

    for (size_t j = 1; j < opt.width - 1; ++j) {
        if (v[opt.length - 1][j] > 3) {
            down = true;
            break;
        }
    }
}
// This function helps to extence our sandheap - nothing more
std::vector<std::vector<uint64_t>> Extension(std::vector<std::vector<uint64_t>>& v, const bool& up, const bool& right, const bool& down, const bool& left) {
    std::vector<std::vector<uint64_t>> a(opt.length, std::vector<uint64_t> (opt.width, 0));

    if (up) {
        opt.length++;
        a.insert(a.begin(), std::vector<uint64_t> (opt.width, 0));
    }
    if (right) {
        opt.width++;
        for (size_t i = 0; i < opt.width; ++i) {
            a[i].push_back(0);
        }
    }
    if (down) {
        opt.length++;
        //a.push_back(std::vector<uint64_t> (opt.width, 0));
        a.emplace_back(opt.width, 0);
    }
    if (left) {
        opt.width++;
        for (size_t i = 0; i < opt.width; ++i) {
            a[i].insert(a[i].begin(), 0);
        }
    }

    return a;
}

/*void Collapsing(std::vector<std::vector<uint64_t>>& v, const bool up, const bool right, const bool down, const bool left, bool& flag) {
    std::vector<std::vector<uint64_t>> a = Extension (v, up, right, down, left);
    flag = false;
    if (left && up) {
        for(size_t i = 0; i < v.size(); ++i) {
            for (size_t j = 0; j < v[i].size(); ++j) {
                if (v[i][j] > 3) {
                    flag = true;
                    a[i + 1][j + 1] += v[i][j] - 4;
                    a[i][j + 1]++;
                    a[i + 2][j + 1] ++;
                    a[i + 1][j]++;
                    a[i + 1][j + 2]++;
                } else {
                    a[i + 1][j + 1] += v[i][j];
                }
            }
        }
    } else if (up) {
        for(size_t i = 0; i < v.size(); ++i) {
            for (size_t j = 0; j < v[i].size(); ++j) {
                if (v[i][j] > 3) {
                    flag = true;
                    a[i + 1][j] += v[i][j] - 4;
                    a[i + 2][j]++;
                    a[i][j]++;
                    a[i + 1][j - 1]++;
                    a[i + 1][j + 1]++;
                } else {
                    a[i + 1][j] += v[i][j];
                }
            }
        }
    } else if (left) {
        for(size_t i = 0; i < v.size(); ++i) {
            for (size_t j = 0; j < v[i].size(); ++j) {
                if (v[i][j] > 3) {
                    flag = true;
                    a[i][j + 1] += v[i][j] - 4;
                    a[i][j + 2]++;
                    a[i][j]++;
                    a[i + 1][j + 1]++;
                    a[i - 1][j + 1]++;
                } else {
                    a[i][j + 1] += v[i][j];
                }
            }
        }
    } else {
        for(size_t i = 0; i < v.size(); ++i) {
            for (size_t j = 0; j < v[i].size(); ++j) {
                if (v[i][j] > 3) {
                    flag = false;
                    a[i][j] += v[i][j] - 4;
                    a[i][j + 1]++;
                    a[i][j - 1]++;
                    a[i + 1][j]++;
                    a[i - 1][j]++;
                } else {
                    a[i][j] += v[i][j];
                }
            }
        }
    }
}*/

void Collapsing(std::vector<std::vector<uint64_t>>& v, bool& up, bool& right, bool& down, bool& left, bool& flag) {
    std::vector<std::vector<uint64_t>> a = Extension(v, up, right, down, left);
    flag = false;
    short int x = left;
    short int y = up;

    for(size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v[i].size(); ++j) {
            if (v[i][j] > 3) {
                flag = true;
                a[i + y][j + x] += v[i][j] - 4;
                a[i + y][j + x + 1]++;
                a[i + y][j + x - 1]++;
                a[i + y - 1][j + x]++;
                a[i + y + 1][j + x]++;
            } else {
                a[i + y][j + x] += v[i][j];
            }
        }
    }
    v = a;
    up = false;
    right = false;
    down = false;
    left = false;
}