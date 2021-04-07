src = $(wildcard *.cpp)
obj = $(src:%.cpp=%.o)
target = checker
CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = 
LDFLAGS = -lreadline

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

$(target): $(obj)  
	$(CXX) $(obj) -o $(target) $(LDFLAGS)

.PHONY: clean rebuild all
clean:
	rm -rf $(obj) $(target) 

rebuild: clean $(target)

all: $(target)
