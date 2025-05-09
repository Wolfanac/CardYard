<<<<<<< HEAD
PROG = projet2
=======
PROG = projet3
>>>>>>> 8b5eabd1e985c6c89ec3072f0ea3ebc775eb007c

SRC = main.c gameInit.c playerHandler.c printingScreen.c basicFonction.c cards_attribution.c Piles.c ending.c saves.c

all: $(PROG) 
	./$(PROG)

#Program compilating
$(PROG): $(SRC) include.h player.h gameInit.h
	gcc -Wall -o $(PROG) $(SRC)

#cleaning
clean:
	rm -f $(PROG)
