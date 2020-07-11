#include <iostream>

#include "monstream.h"

using namespace std;

int main() {
    cov::monstream m;
    m << "Hello\nWorld!   ";
    m.space();
    m << "Uh oh\nSpaghettiohs\nLol";
    m.space();
    m << "yes";
    m.space();
    m << "1\n2\n3\n4";
    m.newline();
    m << "Sup";
    m.flush();
    return 0;
}