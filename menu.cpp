#include <iostream>

#include "menu.h"

using namespace cov;

menu::menu() {}
menu::menu(std::vector<std::shared_ptr<menu_item>> items) : options(items) {}
menu::menu(std::vector<menu_item*> items) {
    options.reserve(items.size());
    for(auto item : items) {
        options.push_back(std::shared_ptr<menu_item>(item));
    }
}

void menu::addOption(const std::shared_ptr<menu_item>& item) {
    options.push_back(item);
}

void menu::addOption(menu_item* item) {
    addOption(std::shared_ptr<menu_item>(item));
}

bool isInt(const std::string& s) {
    for(char c : s) {
        if(c < '0' || c > '9')
            return false;
    }
    return true;
}

//Can maybe look into splitting into multiple functions for clarity
std::shared_ptr<menu_item> menu::display() {
    int val = -1;
    std::string inp;
    monstream m;
    for(int i = 0; i<options.size(); ++i) {
        options[i]->prewrite(m);
        m << std::to_string(i+1) << ") ";
        m.space();
        options[i]->write(m);
        m.newline();
    }
    //custom message?
    m << "Please enter an option:";
    do{
        m.flush();
        std::getline(std::cin, inp);
        if(!isInt(inp)) {
            for(int i = 0; i<options.size()&&val==-1; ++i) {
                if(options[i]->canAccept(inp)) {
                    val = i;
                }
            }
            if(val == -1) {
                monstream m2;
                m2 << RED << "ERROR: " << WHITE << "cannot recognize input " << GREEN << "\"" << inp << "\"";
                m2.flush(); 
            }
        } else {
            val = atoi(inp.c_str());
            if(val >= options.size() || val < 0) {
                monstream m2;
                m2 << RED << "ERROR: " << GREEN << std::to_string(val) << WHITE << " out of range";
                m2.flush(); 
                val = -1;
            } else {
                --val; //Humans don't like 0-indexing
            }
        }
    }while(val >= options.size() || val < 0);
    options[val]->onEnter();
    return options[val];
}