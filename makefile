PROG = projet

SRC = main.c gameInit.c playerHandler.c printingScreen.c basicFonction.c cards_attribution.c Piles.c ending.c saves.c

all: $(PROG) 
	./$(PROG)

#Program compilating
$(PROG): $(SRC) include.h player.h gameInit.h
	gcc -Wall -o $(PROG) $(SRC)

#cleaning
clean:
	rm -f $(PROG)
