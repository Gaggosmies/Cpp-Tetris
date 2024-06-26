CXX=g++
CXXFLAGS=-std=c++17 -Wall -static-libstdc++ -static-libgcc
TARGET=tetris
FILES=main.cpp engine.cpp

all: $(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
