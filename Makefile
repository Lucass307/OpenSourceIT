# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# ------------------------------------------

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CFLAGS += $(SDL_CFLAGS)
LDFLAGS += $(SDL_LDFLAGS)

CC= gcc
ifdef OS # Windows' case
SDLDEFINES= -DSDL_MAIN_HANDLED
SDLLIBS= -lmingw32 -lSDLmain
else
SDLDEFINES= 
SDLLIBS= 
endif
CFLAGS= -O2 -Wall -Werror -ansi -Wno-unused-result -g $(SDLDEFINES)
CLIBS= $(SDLLIBS) -lm -lSDL -lSDL_gfx
EXE= executable
OBJ= obj/
SRC= src/
INCL= include/
FILEC:= $(wildcard $(SRC)*.c)
FILEH:= $(wildcard $(INCL)*.h)
FILEO:= $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))

$(EXE) : $(FILEO)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o : $(SRC)%.c $(INCL)%.h
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)
	rm -rf $(EXE) 
