SRC = src
BIN = bin
APP = app
TARGET = fibonacci

.PHONY: all clean install uninstall

all: $(TARGET)

clean:
		rm -rf $(TARGET) $(BIN)/*.o

$(BIN)/main.o: $(SRC)/main.cpp
		g++ -pthread -c $(SRC)/main.cpp -o $(BIN)/main.o

$(BIN)/fib.o: $(SRC)/fib.cpp
		g++ -pthread -c $(SRC)/fib.cpp -o $(BIN)/fib.o

$(TARGET): $(BIN)/main.o $(BIN)/fib.o
		g++ -pthread -o $(TARGET) $(BIN)/main.o $(BIN)/fib.o

install:
		install $(TARGET) $(APP)

unistall:
		rm -rf $(APP)/$(TARGET)
