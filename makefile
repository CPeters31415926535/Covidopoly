#Graciously adopted and adapted from John Tsiombikas
#Original on http://nuclear.mutantstargoat.com/articles/make/

MKDIR := lib
DEPDIR := $(MKDIR)/.dep

src := $(wildcard *.cpp) $(wildcard win/*.cpp)
obj := $(addprefix $(MKDIR)/,$(src:.cpp=.o))
dep := $(addprefix $(DEPDIR)/,$(src:.cpp=.d))

#LDFLAGS = -lGL -lglut -lpng -lz -lm

CXXFlAGS = -std=c++17

myprog: $(obj)
	$(CXX) -std=c++17 -o a.exe $^ $(LDFLAGS)
                                                                                     
$(MKDIR)/%.o: %.cpp
	$(CXX) -std=c++17 -c -o $@ $< $(LDFLAGS)

-include $(dep)

$(DEPDIR)/%.d: %.cpp
	$(CXX) -std=c++17 $< -MMD -MT $(@:$(DEPDIR)/%.d=$(MKDIR)/%.o) -MF $@

.PHONY: clean
clean:
	rm -f $(obj) a.exe