#include <iostream>
#include <vector>

#include "monstream.h"

using namespace std;

int main() {
    cov::monstream m;
    for(int y = 0; y < 8; ++y) {
        for(int x = 0; x < 8; ++x) {
            m << "+----\n|\n|\n|\n|";
            m.space();
        }
        m << "+\n|\n|\n|\n|";
        m.newline();
    }
    for(int x = 0; x < 8; ++x) {
        m << "+----";
    }
    m << "+";
    m.flush();
    return 0;
}