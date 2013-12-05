CXX = /opt/bin/clang++

CXXFLAGS = -v -O3 -Wall -fmessage-length=0 -std=c++11 -nostdinc++ -I /opt/include/c++/v1

LDFLAGS = -stdlib=libc++ -L /opt/lib

LIBS =

CPP_FILES = $(wildcard *.cpp)

TARGET = $(CPP_FILES:.cpp=)

OBJS =	$(CPP_FILES:.cpp=.o)

SYMS = 

all: $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET) $(SYMS)

%: %.cpp
	@ if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $<

%.o: %.cc fundef.hpp
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} -c $<
	
fundef: fundef.cpp src1.o src2.o
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $^