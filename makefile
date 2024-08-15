CC= g++
CPP_FLAGS= -pedantic
LINKER_FLAGS= -lSDL2 -lSDL2_image
SRC_DIR= ./src/
OBJ_NAME= $(SRC_DIR)main.o $(SRC_DIR)Game.o
OUTPUT= output
OUTPUT_BIN= game.out

# Create output directory
$(shell mkdir -p $(OUTPUT))

all: $(OUTPUT_BIN)

game.out: $(OBJ_NAME)
	$(CC) $(OBJ_NAME) -o $(OUTPUT)/$(OUTPUT_BIN) $(LINKER_FLAGS)

%.o: $(SRC_DIR)%.cpp
	$(CC) $<  $(CPP_FLAGS) -o $(OBJ_NAME)

clean:
	rm -rf $(OUTPUT) $(SRC_DIR)*.o