CXX = g++

CXXFLAGS = -g --std=c++11

BINARY = hw10

TARFILE = hw10.tar

all: $(BINARY)

$(BINARY):
	$(CXX) $(CXXFLAGS) hw10.cpp -o $(BINARY)
clean:
	rm -rf $(BINARY) $(TARFILE)
tar:
	tar cf $(TARFILE) Makefile hw10.scr hw10.cpp