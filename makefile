SRC_DIR := .
OBJ_DIR := .

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

LDFLAGS := -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS := -g -Wall -fpermissive -std=c++17 -IC:/SFML/include
TARGET := Mandelbrot.out

$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o
