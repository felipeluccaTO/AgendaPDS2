CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
BUILD_DIR = build
EXECUTABLE = programa
TEST_EXECUTABLE = test_programa

# Lista de todos os arquivos .cpp em src/core e src/menu
SRCS = $(wildcard $(SRC_DIR)/core/*.cpp) $(wildcard $(SRC_DIR)/menu/*.cpp)

# Gera uma lista de nomes de arquivos .o correspondentes
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Lista de todos os arquivos .cpp em test/core e test/storage
TEST_SRCS = $(wildcard $(TEST_DIR)/core/*.cpp) $(wildcard $(TEST_DIR)/storage/*.cpp)

# Gera uma lista de nomes de arquivos .o correspondentes para os testes
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp $(INC_DIR)/%.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE) $(TEST_EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

test_run: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

