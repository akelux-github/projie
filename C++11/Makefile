CXX = g++

CXXFLAGS = -O3 -Wall -fmessage-length=0 


LDFLAGS =

LIBS =

CPP_FILES = $(wildcard *.cpp)

TARGET = $(CPP_FILES:.cpp=)

OBJS =	$(CPP_FILES:.cpp=.o)

SYMS = 

all: $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET) $(SYMS)

%: %.cpp
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $<

printrbtree: printrbtree.cpp redblacktree.hpp
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $<

rbtree: rbtree.cpp redblacktree.hpp
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $<	

%.o: %.cc
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} -c $<		