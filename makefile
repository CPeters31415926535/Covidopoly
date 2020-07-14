#Graciously adopted and adapted from John Tsiombikas
#Original on http://nuclear.mutantstargoat.com/articles/make/

MKDIR := lib
DEPDIR := $(MKDIR)/.dep

src := $(wildcard *.cpp) $(wildcard win/*.cpp)
obj = $(addprefix $(MKDIR)/,$(src:.cpp=.o))
dep = $(addprefix $(DEPDIR)/,$(src:.cpp=.d))

#LDFLAGS = -lGL -lglut -lpng -lz -lm

CXXFlAGS += -std=c++17

myprog: $(obj)
	$(CXX) -std=c++17 -o a $^ $(LDFLAGS)

-include $(dep)

$(MKDIR)/%.o: %.cpp
	$(CXX) -std=c++17 -c -o $@ $^ $(LDFLAGS)

$(DEPDIR)/%.d: %.cpp
	$(CXX) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) myprog