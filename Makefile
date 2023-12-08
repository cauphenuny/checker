src = $(wildcard *.cpp)
obj = $(src:%.cpp=%.o)
target = checker
CXX = g++
CXXFLAGS = -Wall -std=c++11
CPPFLAGS = 
LDFLAGS = 

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

$(target): $(obj)
	$(CXX) $(obj) -o $(target) $(LDFLAGS)

.PHONY: clean rebuild all install uninstall

clean:
	rm -rf $(obj) $(target) 

rebuild: clean $(target)

run: $(target)
    ./checker

all: $(target)

install:
	./install
uninstall:
	./uninstall
