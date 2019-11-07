#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES



#C'est la version minimal du cmake à utilisé
cmake_minimum_required (VERSION 2.6)

#C'est le nom du projet
project (recolor_text)

#Pour la compilation, -std=c99 pour compiler sous la norme c99, -g pour le debuggage, -Wall pour afficher les erreurs de compilation
set (CMAKE_C_FLAGS "-std=c99 -g -Wall")

#Implémentation des executables 
#   executable du jeu
add_executable (recolor_text recolor_text.c)
#   executable des tests de bug
add_executable (test_game_arblondeau test_game_arblondeau.c)
add_executable (test_game_cgoedefroit test_game_cgoedefroit.c)
add_executable (test_game_vandrault test_game_vandrault.c)

#Création de la librairie game
add_library (game game.c game_io.c)

#Définit les bibliothèques utilisé par les executables
#   librairie pour l'executable du jeu
target_link_libraries (recolor_text game)
#   librairie pour les executables de test de bug
target_link_libraries (test_game_arblondeau m game)
target_link_libraries (test_game_cgoedefroit m game)
target_link_libraries (test_game_vandrault m game)


#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES
#NE PAS COMMIT CE FICHIER SANS L'AUTORISATION DE CHARLES