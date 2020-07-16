#include "menuitem.h"

using namespace cov;

#define dmi default_menu_item

menu_item::~menu_item() {}

dmi::~dmi() {}
dmi::dmi(const std::string& s, void (*f)(void)) : message(s), func(f) {}

void dmi::write(monstream& m) {
    m << message;
}

void dmi::prewrite(monstream& m) {}

bool dmi::canAccept(const std::string& s) {
    return false;
}

void dmi::onEnter() {
    func();
}