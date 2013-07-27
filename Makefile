CXXFLAGS=-O3 -std=c++11 -Wall -Wextra -Weffc++ -pedantic

SOURCES= $(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
TARGET=example

LINKS=-lboost_regex

CXX=g++

all: $(TARGET)
	@echo C++VerbalExpressions built

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LINKS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
