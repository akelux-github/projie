CXX = /opt/local/bin/clang++

CXXFLAGS =	-O3 -Wall -fmessage-length=0 -nostdinc++ -std=c++11 -I /opt/local/include/libc++

OBJS =		C++11.o

LDFLAGS = -stdlib=libc++  -L /opt/local/lib

LIBS =

TARGET =	C++11 userliterals

SYMS = *.dSYM

all:	$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET) $(SYMS)
	
%: %.cpp
	rm -f $@
	${CXX} ${CXXFLAGS} $(LDFLAGS) -o $@ $<
	