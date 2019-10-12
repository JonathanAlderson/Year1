
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/main

SRC= main.c growTree.c destroyTree.c writeTree.c buildTree.c tests.c valueTree.c indicator.c

# generic build details

CC=      cc
COPT=    -g
CFLAGS= -lm

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(COPT) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: growTree.h destroyTree.h writeTree.h buildTree.h treeStructure.h tests.h valueTree.h indicator.h
