#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#define SIZE 12 //TODO: voire pour le suppriemer

struct game_s{
    color *tab; //le tableau contenant les cases du jeux (2D ?)
    unsigned int nb_moves_max; // nombre de coups max
    int current_moves; //nombre de coups actuels
    color *tab_init;
    unsigned int size;
};


enum color_e {RED, GREEN, BLUE, YELLOW, NB_COLORS};


game game_new(color *cells, unsigned int nb_moves_max) {
    if (cells == NULL) {
        fprintf(stderr, "Bad parameter");
        exit(EXIT_FAILURE);
    }

    game_s *g = malloc(sizeof(game_s));
    if (g == NULL) {
        fprintf(stderr, "Not enough memory");
        exit(EXIT_FAILURE);
    }

    g->nb_moves_max = nb_moves_max;
    g->current_moves = 0;
    g->size = SIZE;

    g->tab = malloc((SIZE*SIZE)*sizeof(color));
    if (g->tab == NULL) {
        fprintf(stderr, "Not enough memory");
        exit(EXIT_FAILURE);
    }

    g->tab_init = malloc((SIZE * SIZE) * sizeof(color));
    if (g->tab_init == NULL) {
        fprintf(stderr, "Not enough memory");
        exit(EXIT_FAILURE);
    }

    for (uint i = 0; i < SIZE*SIZE; i++) {
        g->tab[i] = cells[i];
        g->tab_init[i] = cells[i];
    }

    return g;
}

game game_new_empty(){return;}

void game_set_cell_init(game g, unsigned int x, unsigned int y, color c){}

void game_set_max_moves(game g, unsigned int nb_max_moves){}

unsigned int game_nb_moves_max(cgame g){
    if (g == NULL) exit(EXIT_FAILURE);
    return g->nb_moves_max;
}

color game_cell_current_color(cgame g, unsigned int x, unsigned int y){return BLUE;}

unsigned int game_nb_moves_cur(cgame g){
    if (g == NULL) exit(EXIT_FAILURE);

}

void game_play_one_move(game g, color c){} //flood fill algo

game game_copy(cgame g){return;}

void game_delete(game g){
    if (g == NULL) exit(EXIT_FAILURE);
    free(g);
}

bool game_is_over(cgame g){return true;}

void game_restart(game g){}