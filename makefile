CXX=g++
CXXFLAGS=-std=c++17 -Wall
TARGET=tetris
FILES=main.cpp engine.cpp container.cpp

all: $(TARGET)

$(TARGET): $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
