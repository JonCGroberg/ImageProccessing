CC = g++
CFLAGS =  -std=c++11
BUILD_DIR = build
OUTPUT_DIR = output
SRC_DIR = src
SRC = $(SRC_DIR)/*.cpp
TARGET = project2.out

clear-build-run: clearOutput clear build run

clear:
	@echo "Clearing $(Target)..."
	@rm -rf $(Target)
build:
	@echo "Building $(TARGET)..."
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
run: build
	@echo "Running $(TARGET)...\n"
	@./$(TARGET)
clearOutput:
	@echo "Clearing output file..."
	@rm -f OUTPUT_DIR/*