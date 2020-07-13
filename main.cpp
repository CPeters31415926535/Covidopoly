#include <iostream>
#include <vector>

#include "monstream.h"

using namespace std;

int main() {
    cov::monstream m, m2;
    for(int y = 0; y < 8; ++y) {
        for(int x = 0; x < 8; ++x) {
            if(x==1&&y==0)
                m << cov::RED;
            m << "+---\n|\n|\n|";
            m.space();
        }
        m << "+\n|\n|\n|";
        m.newline();
    }
    for(int x = 0; x < 8; ++x) {
        m << "+---";
    }
    m << "+";
    m.newline();
    m.newline();
    m << m;
    m2 << m;
    m2.space();
    m2 << "  ";
    m2.space();
    m2 << m;
    m2.flush();
    return 0;
}