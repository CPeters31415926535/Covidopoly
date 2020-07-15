#include <iostream>

#include "monstream.h"
#include "deck.h"

using namespace std;

int main() {/*
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
    m2.flush();*/
    cov::deck<int> d({1, 1, 2, 3, 4, 5, 6});
    d.draw();
    d.remove();
    d.draw();
    d.remove();
    for(int i = 0; i < 20; ++i) {
        d.print();
        std::cout << '\n' << *(d.draw()) << '\n';
    }
    d.print();
    std::cout << '\n';
    d.reinsert(1);
    d.print();
    return 0;
}