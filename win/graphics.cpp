#ifdef _WIN32
#ifndef MONSTREAM_IMPL
#define MONSTREAM_IMPL

#include "../monstream.h"

#include <iostream>
#include <windows.h>

using namespace cov;

HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

monstream::monstream() : x(0), y(0), curHeight(0), maxWidth(0) {}

monstream& monstream::operator<<(const context& c) {
    int index = colorBuffer[colorBuffer.size()-1].size();
    if(last == COLOR) {
        colorBuffer[colorBuffer.size()-1][index-1] += c;
    }
    colorBuffer[colorBuffer.size()-1].push_back(c);
    last = COLOR;
    return *this;
}

inline std::string fill(int n) {
    if(n<=0)
        return "";
    return std::string(n, ' ');
}

monstream& monstream::operator<<(const std::string& s) {
    if(last == PRINT) {
        //Abandon ship, it gets ugly
    } else {
        std::vector<int> breaks;
        breaks.push_back(-1);
        for(int i=0; i<s.length(); ++i) {
            if(s[i] == '\n') {
                breaks.push_back(i);
            }
        }
        breaks.push_back(s.length());
        int width;
        for(int i = 0; i<breaks.size()-1; ++i) {
            if(curHeight+i >= printBuffer.size()) {
                printBuffer.push_back({});
                printBuffer[curHeight+i].push_back(fill(x));
                colorBuffer.push_back({});
                colorBuffer[curHeight+i].push_back({{}, {}});
                lens.push_back(x);
            }
            width = breaks[i+1]-breaks[i]-1;
            lens[curHeight+i] += width;
            printBuffer[curHeight+i].push_back(s.substr(breaks[i]+1, width));
            maxWidth = width > maxWidth ? width : maxWidth;
        }
        y = breaks.size()-1;
        maxHeight = maxHeight < y ? y : maxHeight;
    }
    last = PRINT;
    return *this;
}

void monstream::newline() {
    space();
    curHeight += maxHeight;
    maxHeight = 0;
    x = 0;
    colorBuffer.push_back({{}, {}});
}

void monstream::space() {
    for(int i = curHeight; i < curHeight + maxHeight; ++i) {
        int index = printBuffer[i].size()-1;
        printBuffer[i][index] += fill(maxWidth+x-lens[i]);
        lens[i] = maxWidth+x;
        colorBuffer[i].push_back({{}, {}});
    }
    x += maxWidth;
    maxWidth = 0;
    last = COLOR;
}

void monstream::flush() const {
    for(int i = 0; i < printBuffer.size(); ++i) {
        for(int j = 0; j < printBuffer[i].size(); ++j) {
            std::cout << printBuffer[i][j];
        }
        std::cout << "\n";
    }
    std::cout.flush();
}

#endif
#endif