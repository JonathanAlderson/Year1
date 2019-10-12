
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/main

SRC= main.c graphicsFunctions.c gameFunctions.c

# generic build details

CC =     gcc
CFLAGS = -g
LIBS =   -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  gameData.h gameFunctions.h graphicsFunctions.h SDLTextures.h
