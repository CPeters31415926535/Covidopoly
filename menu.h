#ifndef MENU_H
#define MENU_H

#include <memory>
#include <vector>

#include "menuitem.h"

namespace cov{
    class menu {
        public:
            menu();
            menu(std::vector<std::shared_ptr<menu_item>> items);
            menu(std::vector<menu_item*> items);
            void addOption(menu_item* item);
            void addOption(const std::shared_ptr<menu_item>& item);
            std::shared_ptr<menu_item> display();
        private:
            std::vector<std::shared_ptr<menu_item>> options; 
    };
}

#endif