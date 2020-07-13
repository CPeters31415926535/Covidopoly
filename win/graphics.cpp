#ifdef _WIN32
#ifndef MONSTREAM_IMPL
#define MONSTREAM_IMPL

#include "../monstream.h"

#include <iostream>
#include <windows.h>

using namespace cov;

HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

monstream::monstream() : x(0), y(0), curHeight(0), maxWidth(0), maxHeight(0), m(FOREGROUND) {
    buf.push_back({});
    buf[0].push_back({"", {WHITE, BLACK}});//TODO: make this work well with a changing default and copying
    lens.push_back(0);
}

monstream& monstream::operator<<(const context& c) {
    int index = buf[y].size()-1;
    if(buf[y][index].first == "") {
        buf[y][index].second = c + buf[y][index].second;
    } else if (!(buf[y][index].second == c)) {
        buf[y].push_back({"", c+buf[y][index].second});
    }
    return *this;
}

inline std::string fill(int n) {
    if(n<=0)
        return "";
    return std::string(n, ' ');
}

std::vector<std::string> breakByLine(std::string text) {
    std::vector<int> breaks;
    breaks.push_back(-1);
    for(int i = 0; i<text.length(); ++i) {
        if(text[i] == '\n') {
            breaks.push_back(i);
        }
    }
    breaks.push_back(text.length());
    std::vector<std::string> res;
    int width;
    for(int i = 0; i<breaks.size()-1; ++i) {
        width = breaks[i+1]-breaks[i]-1;
        res.push_back(text.substr(breaks[i]+1, width));
    }
    return res;
}

inline int length(std::string s) {
    int len = 0;
    for(char c : s) {
        if(isprint(c))
            ++len;
    }
    return len;
}

monstream& monstream::operator<<(const std::string& s) {
    std::vector<std::string> lines = breakByLine(s);
    for(int i = 0; i < lines.size(); ++i) {
        if(y+i >= buf.size()) {
            //Custom color handling goes here
            buf.push_back({});
            buf[y+i].push_back({fill(x), {std::nullopt, std::nullopt}});
            lens.push_back(x);
        }
        int index = buf[y+i].size()-1;
        buf[y+i][index].first += lines[i];//Here
        lens[y+i] += length(lines[i]);
        if(lens[y+i]-x > maxWidth) {
            maxWidth = lens[y+i]-x;
        }
    }
    y += lines.size()-1;
    if(maxHeight < y-curHeight+1) {
        maxHeight = y-curHeight+1;
    }
    return *this;
}

monstream& monstream::operator<<(const mode& a) {
    m = a;
    return *this;
}

monstream& monstream::operator<<(const color& c) {
    if(m == FOREGROUND)
        return (*this) << context(c, std::nullopt);
    else
        return (*this) << context(std::nullopt, c);
}

monstream& monstream::operator<<(const monstream& m) {
    if(&m == this) {
        int size = buf.size();
        int size2 = buf[size-1].size()-1;
        text fin = buf[size-1][size2];
        for(int i = 0; i < size; ++i) {
            int in = buf[i].size()-1;
            if(i == size-1) {
                --in;
            }
            for(int j = 0; j < in; ++j) {
                (*this) << buf[i][j].second;
                (*this) << buf[i][j].first;
            }
            (*this) << "\n";
        }
        (*this) << fin.second;
        (*this) << fin.first;
    } else {
        for(int i = 0; i<m.buf.size(); ++i) {
            for(int j = 0; j<m.buf[i].size(); ++j) {
                (*this) << m.buf[i][j].second;
                (*this) << m.buf[i][j].first;
            }
            (*this) << "\n";
        }
    }
    return *this;
}

void monstream::newline() {
    space();
    curHeight += maxHeight;
    y = curHeight;
    maxHeight = 1;
    x = 0;
    buf.push_back({});
    buf[curHeight].push_back({fill(x), {std::nullopt, std::nullopt}});
    lens.push_back(x);
}

void monstream::space() {
    for(int i = curHeight; i < curHeight + maxHeight; ++i) {
        int index = buf[i].size()-1;
        buf[i][index].first += fill(maxWidth+x-lens[i]);
        lens[i] = maxWidth+x;
        buf[i].push_back({"", buf[i][index].second});
    }
    x += maxWidth;
    maxWidth = 0;
    y = curHeight;
}

int colcode(const color& c) {
    switch(c) {
        case BLACK: return 0;
        case WHITE: return 15;
        case RED: return 4;
        case GREEN: return 2;
        case BLUE: return 1;
    }
    return 0;
}

void setColor(const context& c) {
    //We hardcode white on black here, we can make it customizable later
    SetConsoleTextAttribute(hstdout, (colcode(c.bg.value_or(BLACK))<<4)|colcode(c.fg.value_or(WHITE)));
}

void monstream::flush() const {
    for(int i = 0; i < buf.size(); ++i) {
        for(int j = 0; j < buf[i].size(); ++j) {
            setColor(buf[i][j].second);
            std::cout << buf[i][j].first;
        }
        std::cout << "\n";
    }
    std::cout.flush();
}

#endif
#endif