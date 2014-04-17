CC = g++
CFLAGS  = -Wall
SRC = ./src/*.cpp
PROGNAME = minigolf
OBJDIR = ./objects/
OBJ = ./objects/*.o
REMOVE = ./$(PROGNAME).exe ./$(PROGNAME) ./objects/
LINKERS = -lfreeglut -lglu32 -lopengl32

all: program

objects:
	@$(CC) -c $(SRC)
	@mkdir -p objects
	@mv -f ./*.o ./objects/

program: objects
	@$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJ) $(LINKERS)

clean:
	@rm -f -r $(REMOVE)