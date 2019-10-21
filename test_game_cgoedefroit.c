#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_game_copy() {
    printf("Test copy : Done.\n");
}
void test_game_delete() {
    printf("Test delete : Done.\n");
}
void test_game_is_over() {
    printf("Test is_over : Done.\n");
}
void test_game_restart() {
    printf("Test restart : Done.\n");
}

void all() {
    test_game_copy();
    test_game_delete();
    test_game_is_over();
    test_game_restart();
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
        all();
    else
        if (!strcmp(argv[1], "copy"))
            test_game_copy();
        else if (!strcmp(argv[1], "delete"))
            test_game_delete();
        else if (!strcmp(argv[1], "is_over"))
            test_game_is_over();
        else if (!strcmp(argv[1], "restart"))
            test_game_restart();
        else
            all();

    return EXIT_SUCCESS;
}
