CC = g++
CFLAGS =  -std=c++17 -g
BUILD_DIR = build
OUTPUT_DIR = output
SRC_DIR = src
SRC = $(SRC_DIR)/*.cpp
TARGET = main

clear-build-run: clearOutput clear build run

clear:
	@echo "Clearing $(BUILD_DIR) directory..."
	@rm -rf $(BUILD_DIR)
build:
	@echo "Building $(TARGET)..."
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$(TARGET)
run: build
	@echo "Running $(TARGET)...\n"
	@./$(BUILD_DIR)/$(TARGET)
clearOutput:
	@echo "Clearing output files..."
	@rm -f $(OUTPUT_DIR)/*