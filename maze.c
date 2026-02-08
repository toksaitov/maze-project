#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM_NAME "maze"

typedef struct node
{
    size_t x, y;
    struct node *next;
} node_t;

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;

    FILE *output_fd = NULL;

    double **maze = NULL;
    int **visited = NULL;
    node_t *stack = NULL;

    srand(0); // NOLINT(cert-msc51-cpp), we want a predictable sequence

    if (argc != 4) {
        fprintf(
            stderr,
            "Usage:\n"
            "\t%s <maze width up to 16384> <maze height up to 16384> <path to the output `.pbm` file>\n",
            PROGRAM_NAME
        );

        status = EXIT_FAILURE;
        goto end;
    }

    long size = strtol(argv[1], NULL, 10);
    if (size < 0) {
        fputs("Maze width should not be a negative number\n", stderr);

        status = EXIT_FAILURE;
        goto end;
    }
    size_t maze_width = (size_t) size;
    size_t maze_width_with_walls = 1 + maze_width * 2;

    size = strtol(argv[2], NULL, 10);
    if (size < 0) {
        fputs("Maze height should not be a negative number\n", stderr);

        status = EXIT_FAILURE;
        goto end;
    }
    size_t maze_height = (size_t) size;
    size_t maze_height_with_walls = 1 + maze_height * 2;

    const char *output_file = (const char *) argv[3];
    output_fd = fopen(output_file, "w");
    if (!output_fd) {
        perror("Failed to open the output `.pbm` file for writing");

        status = EXIT_FAILURE;
        goto end;
    }

    if (fprintf(output_fd, "P1\n%ld %ld\n", maze_width_with_walls, maze_height_with_walls) < 0) {
        perror("Failed to write the PBM header with the type and size information to the output `.pbm` file");

        status = EXIT_FAILURE;
        goto end;
    }

    maze = malloc(maze_width_with_walls * sizeof(maze));
    if (!maze) {
        perror("Failed to allocate memory to store columns of the maze");

        status = EXIT_FAILURE;
        goto end;
    }
    for (size_t x = 0; x < maze_width_with_walls; ++x) {
        maze[x] = malloc(maze_height_with_walls * sizeof(*maze));
        if (!maze[x]) {
            perror("Failed to allocate memory to store a column of the maze");

            status = EXIT_FAILURE;
            goto end;
        }

        for (size_t y = 0; y < maze_height_with_walls; ++y) {
            maze[x][y] = 1;
        }
    }

    visited = malloc(maze_width * sizeof(*visited));
    if (!visited) {
        perror("Failed to allocate memory to store columns of the visited cell flags");

        status = EXIT_FAILURE;
        goto end;
    }
    for (size_t x = 0; x < maze_width; ++x) {
        visited[x] = calloc(maze_height, sizeof(**visited));
        if (!visited[x]) {
            perror("Failed to allocate memory to store a column of the visited cell flags");

            status = EXIT_FAILURE;
            goto end;
        }
    }

    long neighbour_dx[] = {  0, 1, 0, -1 };
    long neighbour_dy[] = { -1, 0, 1,  0 };
    long curr_x = 0, curr_y = 0;

    stack = malloc(sizeof(*stack));
    if (!stack) {
        perror("Failed to allocate memory to store the backtracking stack");

        status = EXIT_FAILURE;
        goto end;
    }
    node_t *node = malloc(sizeof(*node));
    if (!node) {
        perror("Failed to allocate memory to store a node of the backtracking stack");

        status = EXIT_FAILURE;
        goto end;
    }
    node->x = curr_x; node->y = curr_y;
    node->next = NULL; stack->next = node;
    visited[curr_x][curr_y] = 1;
    maze[1 + curr_x * 2][1 + curr_y * 2] = 0;

    node_t *popped_node = NULL;
    while (stack->next != NULL) {
        popped_node = stack->next;
        stack->next = popped_node->next;

        long unvisited_dx[4]; long unvisited_dy[4];
        size_t unvisited = 0;
        for (size_t i = 0; i < 4; ++i) {
            curr_x = (long) popped_node->x + neighbour_dx[i];
            curr_y = (long) popped_node->y + neighbour_dy[i];
            if (curr_x >= 0 && curr_x < (long) maze_width  &&
                curr_y >= 0 && curr_y < (long) maze_height &&
                    !visited[curr_x][curr_y]) {
                unvisited_dx[unvisited] = neighbour_dx[i];
                unvisited_dy[unvisited] = neighbour_dy[i];
                ++unvisited;
            }
        }

        if (unvisited > 0) {
            popped_node->next = stack->next;
            stack->next = popped_node;

            size_t i = rand() % unvisited; // NOLINT(cert-msc50-cpp)
            curr_x = (long) popped_node->x + unvisited_dx[i];
            curr_y = (long) popped_node->y + unvisited_dy[i];

            node = malloc(sizeof(*node));
            if (!node) {
                perror("Failed to allocate memory to store a node of the backtracking stack");

                status = EXIT_FAILURE;
                goto end;
            }
            node->x = curr_x; node->y = curr_y;
            node->next = stack->next; stack->next = node;
            visited[curr_x][curr_y] = 1;
            maze[1 + curr_x * 2][1 + curr_y * 2] = 0;

            size_t wall_x = (1 + popped_node->x * 2) + unvisited_dx[i];
            size_t wall_y = (1 + popped_node->y * 2) + unvisited_dy[i];
            maze[wall_x][wall_y] = 0;
        } else {
            free(popped_node);
            popped_node = NULL;
        }
    }

    for (size_t y = 0; y < maze_height_with_walls; ++y) {
        for (size_t x = 0; x < maze_width_with_walls; ++x) {
            fprintf(output_fd, "%d ", (int) maze[x][y]);
        }
        fputs("\n", output_fd);
    }

end:
    if (stack) {
        while ((node = stack->next) != NULL) {
            stack->next = node->next;
            free(node);
        }
        free(stack);
        stack = NULL;
    }

    if (visited) {
        for (size_t x = 0; x < maze_width; ++x) {
            if (visited[x]) {
                free(visited[x]);
                visited[x] = NULL;
            }
        }
        free(visited);
        visited = NULL;
    }

    if (maze) {
        for (size_t x = 0; x < maze_width_with_walls; ++x) {
            if (maze[x]) {
                free(maze[x]);
                maze[x] = NULL;
            }
        }
        free(maze);
        maze = NULL;
    }

    if (output_fd) {
        fclose(output_fd);
        output_fd = NULL;
    }

    return status;
}
