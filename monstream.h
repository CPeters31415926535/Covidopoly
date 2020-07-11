#ifndef MONSTREAM_H
#define MONSTREAM_H

#include <optional>
#include <string>
#include <vector>

namespace cov {

    enum color {
        BLACK, WHITE, RED, GREEN, BLUE
    };

    enum mode {
        FOREGROUND, BACKGROUND
    };

    struct context {
        std::optional<color> fg;
        std::optional<color> bg;
        context& operator+=(const context& a) {
            if(!fg)
                fg = a.fg;
            if(!bg)
                bg = a.bg;
            return *this;
        }
    };

    class monstream {
        public:
            monstream();

            monstream& operator<<(const std::string& a);
            monstream& operator<<(const context& a);
            monstream& operator<<(const mode& a);
            monstream& operator<<(const color& a);

            void newline();
            void space();
            void flush() const;
        
        private:
            #ifdef _WIN32
            std::vector<std::vector<std::string>> printBuffer;
            std::vector<std::vector<context>> colorBuffer;
            std::vector<int> lens;
            enum type {
                PRINT, COLOR
            };
            type last;

            #else
            std::vector<std::string> printBuffer; //Wow, look how much better unix is
            #endif

            int x, y;
            int curHeight;
            int maxHeight, maxWidth;
    };
}

#endif