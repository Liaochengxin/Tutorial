# 源文件和目标文件
SRC_DIR = src
INCLUDE_DIR = include
GOOGLE_TEST_DIR = /opt/homebrew/opt/googletest

# 编译器和选项
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./$(INCLUDE_DIR) -I$(GOOGLE_TEST_DIR)/include 


TARGET = cgpa_calculator
TEST_TARGET = cgpa_tests

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Course.cpp
TEST_SRC = $(SRC_DIR)/unit_test.cpp $(SRC_DIR)/Course.cpp

GTEST_LIBS = -lgtest -lgtest_main -pthread

all: $(TARGET) $(TEST_TARGET)

# 编译主程序
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译测试程序
$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

# 运行测试
test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

