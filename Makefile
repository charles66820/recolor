CC = gcc
CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I .
LDFLAGS = -lm -L. -lgame
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
EXEC = recolor_text

.PHONY : all
all : $(EXEC)

# crée la library game
libgame.a : game.o game_io.o
	ar -cr $@ $^

# crée les exécutables
recolor_text : recolor_text.o libgame.a
	$(CC) $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@

test_game_cgoedefroit : test_game_cgoedefroit.o libgame.a
	$(CC) $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@

# crée les fichier obj
include depends.txt

# nettoie le dossier des fichiers créés
.PHONY : clean
clean :
	rm -f $(OBJETS) *.a $(EXEC) depends.txt

.PHONY : test_game_cgoedefroit
test_cgoedefroit : test_game_cgoedefroit
	./test_game_cgoedefroit copy
	./test_game_cgoedefroit delete
	./test_game_cgoedefroit is_over
	./test_game_cgoedefroit restart

# défini les dépendance pour les fichier obj
depends.txt : $(SOURCES)
	$(CC) -M $(CPPFLAGS) $(LDFLAGS) $^ > depends.txt
