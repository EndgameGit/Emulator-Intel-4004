OBJ = Intel4002.o Intel4001.o Intel4004.o Intel4004Stack.o CommandsPW.o Intelhex.o unittestXCH.o Get4004.o
SRC = $(OBJ:%.o=%.cpp)
DEPENDFILE = .depend
CC  = g++.exe
CFLAGS  = -Wall -std=c++17 -I. -g -O0
BIN = Intel4004testXCH.exe

# Position von Main-Source und Libs dürfen nicht getauscht werden sonst wird die LIB optimiert dazugelinkt und die Symbole fehlen
$(BIN): $(OBJ) 
	$(CC) -o $(BIN) $(OBJ)
	
	
# Regel kann ganz zum Schluss stehen, Wichtig! %.c und %.cpp nicht verwechseln
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
	
	