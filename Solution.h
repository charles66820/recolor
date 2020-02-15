#ifndef __SOLUTION_H__
#define __SOLUTION_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

/**
 * @brief The structure pointer that stores the solution. it willbe useful to
 *transfer those data in a file.
 **/
typedef struct solution_s *solution;

/**
 * @brief find one possible solution and store it in the struct solution
 *
 * @param g game with cells to print
 */
solution find_one(cgame g);

/**
 * @brief seak for the number of solution
 *
 * @param g game with cells to print
 */
void nb_sol(cgame g);

/**
 * @brief find the solution who require the smallest amount of moves
 *
 * @param g game with cells to print
 */
void find_min(cgame g);