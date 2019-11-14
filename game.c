#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#define SIZE 12

struct game_s{
    color *tab; //le tableau contenant les cases du jeux (2D ?)
    uint nb_moves_max; // nombre de coups max
    uint current_moves; //nombre de coups actuels
    color *tab_init;
    uint size;
};


enum color_e {RED, GREEN, BLUE, YELLOW, NB_COLORS};


game game_new(color *cells, uint nb_moves_max){return;}

game game_new_empty(){return;}

void game_set_cell_init(game g, uint x, uint y, color c){}

void game_set_max_moves(game g, uint nb_max_moves){
    if (g == NULL || nb_max_moves <= 0) exit(EXIT_FAILURE);
    g->nb_moves_max = nb_max_moves;
    return;
}

uint game_nb_moves_max(cgame g){
    if (g == NULL) exit(EXIT_FAILURE);
    return g->nb_moves_max;
}

color game_cell_current_color(cgame g, uint x, uint y){return BLUE;}

uint game_nb_moves_cur(cgame g){
    if (g == NULL) exit(EXIT_FAILURE);
    return g->current_moves;
}

void game_play_one_move(game g, color c){} //flood fill algo

game game_copy(cgame g){return;}

void game_delete(game g){
    if (g == NULL) exit(EXIT_FAILURE);
    free(g->tab);
    free(g->tab_init);
    free(g);
}

bool game_is_over(cgame g){return true;}

void game_restart(game g){} 