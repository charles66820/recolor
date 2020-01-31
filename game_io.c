#include <stdio.h>
#include "game.h"
#include <stdlib.h>

/**
 * @brief load a new game from a file
 *
 * @param filename name of file with the save
 * @return game
 * @pre @p filename != NULL
 */
game game_load(char *filename) { return NULL; }


void game_save(cgame g, char *filename) {
    if (g==NULL){
        printf("Invalid cgame pointer");
        exit(EXIT_FAILURE);
    }
    FILE* savefile = NULL;
    savefile = fopen(filename,"w");
    if (savefile != NULL){
        fprintf (savefile, "%u %u %u %b\n", game_width(g), game_height(g), game_nb_moves_max(g), game_is_wrapping(g));
        for (int y=0; y<game_height(g); y++){
            for (int x = 0; x<game_width(g); x++){
                fprintf(savefile,"%u", game_cell_current_color(g , x, y));
            }
            fprintf(savefile, "\n");
        }
        fclose(savefile);
    }
}