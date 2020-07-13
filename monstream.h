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

    template<class T>
    inline std::optional<T> rep(std::optional<T> a, std::optional<T> b) {
        if(a) {
            return a;
        }
        return b;
    }

    struct context {
        std::optional<color> fg;
        std::optional<color> bg;
        context(const color& a, const color& b) {
            fg = a;
            bg = b;
        }
        context(const std::optional<color>& a, const std::optional<color>& b) {
            fg = a;
            bg = b;
        }
        //Soft-equals, just means b is strictly weaker than this (in the sense of equality or nullopts in place of defined values)
        bool operator==(const context& b) const {
            if(b.fg && b.fg != fg)
                return false;
            if(b.bg && b.bg != bg)
                return false;
            return true;
        }
        context& operator+=(const context& a) {
            if(!fg)
                fg = a.fg;
            if(!bg)
                bg = a.bg;
            return *this;
        }
        context operator+(const context& a) const {
            return{rep(fg, a.fg), rep(bg, a.bg)};
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
            //TODO: decide if a struct called line that is a combination of length, and a vector of text is necessary
            std::vector<int> lens;

            typedef std::pair<std::string, context> text;
            std::vector<std::vector<text>> buf;

            mode m;

            int x, y;
            int curHeight;
            int maxHeight, maxWidth;
    };
}

#endif