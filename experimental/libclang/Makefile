
CXX=clang++
CXXFLAGS=$(shell llvm-config --cxxflags) -Wall
LDFLAGS=-L$(shell llvm-config --libdir) -lclang

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

hylian-c++: main.o
	$(CXX) $< -o $@ $(LDFLAGS)

clean:
	rm -f main.o
	rm -f hylian-c++
