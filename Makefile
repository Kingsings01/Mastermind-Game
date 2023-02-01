TARGET = my_mastermind
OBJ = my_mastermind.o
SRC = my_mastermind.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ):	$(SRC)
	gcc	$(CFLAGS) -c $(SRC)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all