# SRC_DIR := .
# OBJ_DIR := .

# SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# LDFLAGS := -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# CXXFLAGS := -g -Wall -fpermissive -std=c++17 -IC:/SFML/include
# TARGET := Mandelbrot.out

# $(TARGET): $(OBJ_FILES)
#	$(CXX) -o $@ $^ $(LDFLAGS)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#	g++ $(CXXFLAGS) -c -o $@ $<

#run:
#	./$(TARGET)

# clean:
#	rm $(TARGET) *.o


SRC_DIR := ./code
OBJ_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CPPFLAGS := -g -Wall -fpermissive -std=c++17 -I/opt/homebrew/include
CXXFLAGS :=
TARGET := game.out

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o
