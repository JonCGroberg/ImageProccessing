CC = g++
CFLAGS =  -std=c++11
BUILD_DIR = ../
OUTPUT_DIR = output
SRC_DIR = src
SRC = $(SRC_DIR)/*.cpp
TARGET = project2.out

clear-build-run: clearOutput clear build run

clear:
	@echo "Clearing target file..."
	@rm -f TARGET
build:
	@echo "Building $(TARGET)..."
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
run: build
	@echo "Running $(TARGET)...\n"
	@./$(BUILD_DIR)/$(TARGET)
clearOutput:
	@echo "Clearing output files..."
	@rm -f $(OUTPUT_DIR)/*