CXX := g++
FLAGS := -std=c++20 -I./include


TARGET := ray_trace
TARGET_IMAGE := scaled_image

SRC_DIR := src
BUILD_DIR := build
OUTPUT_DIR := output


SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)
	
render: $(TARGET) | $(OUTPUT_DIR)
	./$(TARGET) > ./$(OUTPUT_DIR)/image.ppm
	@convert ./$(OUTPUT_DIR)/image.ppm -resize 300% ./$(OUTPUT_DIR)/$(TARGET_IMAGE).png
	display ./$(OUTPUT_DIR)/$(TARGET_IMAGE).png

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(OUTPUT_DIR)


-include $(DEP)

.PHONY: all clean