CXX = /opt/bin/clang++

CXXFLAGS = -v -g -O3 -Wall -fmessage-length=0 -nostdinc++ -std=c++11 -I /opt/include/c++/v1

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
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $<

%.o: %.cc
	if [ -f $@ ]; then rm -f $@; fi
	${CXX} ${CXXFLAGS} -c $<		