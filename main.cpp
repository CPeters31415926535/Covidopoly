#include <iostream>

#include "monstream.h"
#include "deck.h"
#include "menu.h"
#include "menu.h"

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
    cov::menu m;
    cov::monstream m2;
    m.addOption(new cov::default_menu_item("Quit"));
    m.addOption(new cov::default_menu_item("Double quit"));
    m.addOption(new cov::default_menu_item("Triple quit"));
    m.display()->write(m2);
    m2.flush();
    return 0;
}