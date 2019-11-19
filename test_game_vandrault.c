#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"

//tests//

bool test_game_new(){
    color cells[SIZE*SIZE] = {
        0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0,
        0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
        1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2,
        2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
        2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0,
        0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
        1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
        1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
        0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0,
        1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
        1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2,
        2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

    game g1 = game_new(cells, 12); // test of game_new on valid parameters
    if (g1==NULL){
        return false;
    }
    if (game_nb_moves_max(g1)!=12){
        return false;
    }
    if (sizeof(cells)!=SIZE*SIZE*sizeof(int)){
        return false;
    }
    for (int i=0; i<SIZE*SIZE; i+=1){
        if (game_cell_current_color(g1,i%12,i/12)!=cells[i]){
            return false;
        }
    }
    game_delete(g1);
    return true;    
}

bool test_game_new_empty(){
    game g = game_new_empty(); //test of game_new_empty
    if (g==NULL){
        return false;
    }
    if (game_nb_moves_max(g)!=0){
        return false;
    }
    game_play_one_move(g, 0);
    for (int i=0; i<SIZE*SIZE; i++){
        if (game_cell_current_color(g,i%12,i/12)!=0){
            return false;
        }
    }
    game_delete(g);
    return true;

}

bool test_game_set_cell_init(){
    color cells[SIZE*SIZE] = {
        0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0,
        0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
        1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2,
        2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
        2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0,
        0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
        1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
        1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
        0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0,
        1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
        1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2,
        2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

    game g1 = game_new(cells, 12); //test of game_set_cell_init on valid parameters
    if (g1==NULL){
        return false;
    }
    game_play_one_move(g1, 2);
    game_set_cell_init(g1,5,8,1);
    if (game_cell_current_color(g1,5,8)!=1){
        return false;
    }
    game_delete(g1);
    return true;
}

bool test_game_set_max_moves(){
    color cells[SIZE*SIZE] = {
        0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0,
        0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
        1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2,
        2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
        2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0,
        0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
        1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2,
        1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
        0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0,
        1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
        1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2,
        2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

    game g1 = game_new(cells, 12); //test of game_set_max_moves on valid parameters
    if (g1==NULL){
        return false;
    }
    game_set_max_moves(g1,14);
    if (g1==NULL){
        return false;
    }
    if (game_nb_moves_max(g1)!=14){
        return false;
    }
    game_delete(g1);
    return true;
}

//main//

int main (int argc,char *argv[]){
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    bool ok = false;

    if (!strcmp(argv[1], "new"))
        ok = test_game_new();
    else if (!strcmp(argv[1], "new_empty"))
        ok = test_game_new_empty();
    else if (!strcmp(argv[1], "set_cell_init"))
        ok = test_game_set_cell_init();
    else if (!strcmp(argv[1], "set_max_moves"))
        ok = test_game_set_max_moves();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // print test result
    if (ok) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}