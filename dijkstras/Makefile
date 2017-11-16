PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++11
LD := g++
LDFLAGS := -O3
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
BINS := dijkstra

.PHONY : release
release : CXXFLAGS += -O3
release : $(BINS)

.PHONY : debug
debug : CXXFLAGS += -g -pg
debug : LDFLAGS += -pg
debug : $(BINS)

$(BINS) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY : clean
clean :
	@rm -f $(OBJS) *.o dijkstra
