CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++17

TARGET = ccwc


$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o


main.o: Main.cpp
	$(CC) $(CFLAGS) -c -o main.o Main.cpp


clean:
	rm -f main.o $(TARGET)
