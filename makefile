CC = gcc
CFLAGS = -O2 -Wall

TARGET = program
SRC = main.c lab2.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	 $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	 $(CC) $(CFLAGS) -c $<

clean:
	 rm -f $(OBJ) $(TARGET)

test:
	 ./$(TARGET) program.txt -r "23-24" "2000"
