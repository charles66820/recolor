# Minimal require version of CMake needed
cmake_minimum_required (VERSION 2.6)

option(ENABLE_DEBUG "debug options" ON)

# The project name followed by the programming language use
project (recolor_text C)

# for the compilation, -std=c99 to compile under the standard c99, -g for the debuggage, -Wall to show compilation bug, --coverage to check if all the test go in all the code
if(ENABLE_DEBUG)
    set(CMAKE_C_FLAGS "-g -Wall -std=c99 --coverage") # mode debug
else()
    set(CMAKE_C_FLAGS "-O3 -std=c99") # mode -03 to optimise the compilation
endif()

# for generate bin and lib files in generated folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "generated")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "generated")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "generated")
set(EXECUTABLE_OUTPUT_PATH "generated")

# copy data folder to generated folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
enable_testing()

### Implementation of all executable
# Creation of the library game
add_library (game game.c game_io.c)
target_link_libraries(game m)

# executable of the game
add_executable (recolor_text recolor_text.c)
target_link_libraries (recolor_text game)

# executable of the bug finder
add_executable (test_game_arblondeau test_game_arblondeau.c)
target_link_libraries (test_game_arblondeau game)

add_executable (test_game_cgoedefroit test_game_cgoedefroit.c)
target_link_libraries (test_game_cgoedefroit game)

add_executable (test_game_vandrault test_game_vandrault.c)
target_link_libraries (test_game_vandrault game)

# Those line launch the test to find the bug
add_test(test_vandrault_new generated/test_game_vandrault new)
add_test(test_vandrault_new_empty generated/test_game_vandrault new_empty)
add_test(test_vandrault_set_cell_init generated/test_game_vandrault set_cell_init)
add_test(test_vandrault_set_max_moves generated/test_game_vandrault set_max_moves)
add_test(test_vandrault_height generated/test_game_vandrault height)
add_test(test_vandrault_wrapping generated/test_game_vandrault wrapping)

add_test(test_arblondeau_nb_moves_max generated/test_game_arblondeau game_nb_moves_max)
add_test(test_arblondeau_nv_moves_cur generated/test_game_arblondeau game_nb_moves_cur)
add_test(test_arblondeau_cell_current_color generated/test_game_arblondeau game_cell_current_color)
add_test(test_arblondeau_play_one_move generated/test_game_arblondeau game_play_one_move)
add_test(test_arblondeau_width generated/test_game_arblondeau game_width)
add_test(test_arblondeau_new_empty_ext generated/test_game_arblondeau game_new_empty_ext)

add_test(test_cgoedefroit_copy generated/test_game_cgoedefroit copy)
add_test(test_cgoedefroit_delete generated/test_game_cgoedefroit delete)
add_test(test_cgoedefroit_is_over generated/test_game_cgoedefroit is_over)
add_test(test_cgoedefroit_restart generated/test_game_cgoedefroit restart)
add_test(test_cgoedefroit_new_ext generated/test_game_cgoedefroit new_ext)

set_tests_properties(test_vandrault_new test_vandrault_new_empty test_vandrault_set_cell_init test_vandrault_set_max_moves test_vandrault_height test_vandrault_wrapping test_arblondeau_nb_moves_max test_arblondeau_nv_moves_cur test_arblondeau_cell_current_color test_arblondeau_play_one_move test_arblondeau_width test_arblondeau_new_empty_ext test_cgoedefroit_copy test_cgoedefroit_delete test_cgoedefroit_is_over test_cgoedefroit_restart test_cgoedefroit_new_ext PROPERTIES TIMEOUT 10 PARALLEL_LEVEL 8)
