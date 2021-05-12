CC = gcc
LIB_DIR = lib
LIB_FILES = $(LIB_DIR)/algorithms.o
OBJ_FILES = main.o algotest.o 
TARGET = main
LIBS = -lm -lpthread
all: $(TARGET) 

$(TARGET): $(OBJ_FILES) $(LIB_FILES)
	$(CC) -o $(TARGET) $(OBJ_FILES) $(LIB_FILES) $(LIBS)


$(LIB_DIR)/algorithms.o:
	make -C lib algorithms.o

clean:
	rm -f $(OBJ_FILES) $(TARGET)
	make -C lib clean