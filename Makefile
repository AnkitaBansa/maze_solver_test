CC = gcc
CFLAGS = -Wall -Wextra
TARGET = solver
SRC = maze_solver.c
OBJ = $(SRC:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(TARGET)
re: fclean all
