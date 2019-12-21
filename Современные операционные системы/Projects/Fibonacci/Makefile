SRC = src
BIN = bin
APP = app
TARGET = fibonacci

.PHONY: all clean install uninstall

all: $(TARGET)

clean:
		rm -rf $(TARGET) $(BIN)/*.o

$(BIN)/main.o: $(SRC)/main.cpp
		g++ -c -o $(BIN)/main.o $(SRC)/main.cpp

$(BIN)/fib.o: $(SRC)/fib.cpp
		g++ -c -o $(BIN)/fib.o $(SRC)/fib.cpp

$(TARGET): $(BIN)/main.o $(BIN)/fib.o
		g++ -o $(TARGET) $(BIN)/main.o $(BIN)/fib.o

install:
		install $(TARGET) $(APP)

unistall:
		rm -rf $(APP)/$(TARGET)
