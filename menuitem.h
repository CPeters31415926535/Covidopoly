#ifndef MENUITEM_H
#define MENUITEM_H

#include "monstream.h"

namespace cov {
    //They don't all have to be pure virtual
    class menu_item {
        public:
            virtual ~menu_item();
            virtual void write(monstream& m) = 0;
            virtual void prewrite(monstream& m) = 0;
            virtual bool canAccept(const std::string& input) = 0;
            virtual void onEnter() = 0;
        private:
    };

    class default_menu_item : public menu_item {
        public:
            ~default_menu_item();
            default_menu_item(const std::string& s, void (*f)(void) = [](){});
            void write(monstream& m);
            void prewrite(monstream& m);
            bool canAccept(const std::string& input);
            void onEnter();
        private:
            std::string message;
            void (*func)(void);
    };
}
#endif