#include <stdio.h>
#include <stdlib.h>

#define WALL 'X'
#define FREE_SPACE '*'
#define PATH 'o'


int solve_maze(char **maze, int width, int height, int x, int y) {
    if (x == width - 1 && y == height - 1) { 
        maze[y][x] = PATH;
        return 1;
    }

    if (x < 0 || x >= width || y < 0 || y >= height || maze[y][x] != FREE_SPACE) {
        return 0; 
    }

    maze[y][x] = PATH; 


    if (solve_maze(maze, width, height, x + 1, y) ||
        solve_maze(maze, width, height, x, y + 1) ||
        solve_maze(maze, width, height, x - 1, y) ||
        solve_maze(maze, width, height, x, y - 1)) {
        return 1;
    }

    maze[y][x] = FREE_SPACE; 
    return 0;
}


char **read_maze(FILE *file, int *width, int *height) {
    *width = 0;
    *height = 0;

    char ch;
    int current_width = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            if (*width == 0) *width = current_width;
            current_width = 0;
            (*height)++;
        } else {
            current_width++;
        }
    }
    rewind(file);

    char **maze = (char **)malloc(*height * sizeof(char *));
    for (int i = 0; i < *height; i++) {
        maze[i] = (char *)malloc((*width + 1) * sizeof(char)); 
    }

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            maze[i][j] = fgetc(file);
        }
        fgetc(file); 
    }

    return maze;
}


void print_maze(char **maze, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            putchar(maze[i][j]);
        }
        putchar('\n');
    }
}


void free_maze(char **maze, int height) {
    for (int i = 0; i < height; i++) {
        free(maze[i]);
    }
    free(maze);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <maze_file1> [<maze_file2> ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int file_index = 1; file_index < argc; file_index++) {
        printf("Processing maze from file: %s\n", argv[file_index]);

        FILE *file = fopen(argv[file_index], "r");
        if (!file) {
            perror("Failed to open file");
            continue;
        }

        int width, height;
        char **maze = read_maze(file, &width, &height);
        fclose(file);

        if (solve_maze(maze, width, height, 0, 0)) {
            printf("Solved Maze:\n");
            print_maze(maze, width, height);
        } else {
            printf("No solution found for this maze.\n");
        }

        free_maze(maze, height);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
