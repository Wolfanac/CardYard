# CardYard
CY project - 1st year

# Objective
End the game with the lowest total score. The game end when a player revealed all the cards of his board or if the principal deck is empty. At this point, players that didn't played their turn can play then the one with the lowest score wins the game
Use a card deck going from -2 to 12 (140 cards summed up). The values can be edited afterwards.
Every player gets an amount of cards determined at the beginning of the game.
At the start, each player reveal 2 cards of its choice.
The leftover cards form the principal deck.Every player begin with an empty discard pile.
During your turn, you pick a card from the principal deck, you then have 2 options:
-Either you swap it with a card of your board (revealed or not), that you discard afterwards.
-Or take the card on top of your discard pile and swap it the same way.
Every swapped cards are revealed.
When a column of your board contain uniquely indentical cards, they are destroyed (removed from the game).
When a player have revealed all its card, the turn must be finished. Then, every players reveal their last cards and count their scores. The player with the lowest score wins the game.


# Requirements
A Linux terminal with atleast 3Mb of storage (works with WSL)
https://learn.microsoft.com/en-us/windows/wsl/install


# Installation
Once you are in your terminal, write the following command:
**git clone https://github.com/Wolfanac/CardYard.git**
Enter the file with the **cd** command and compile everything by writing **make**

# Utilisation
You will have the chance to use a drawn card from the main pile by typing draw and write the position the card you want to swap ("I want to use the -2 i just drawn on my 12 at the third position, i will then have to type "draw" and "3")
The process is the same if you want to use a card of a discard pile, you will just have to type the position of the player's discard pile beforehand ("I want to use the -2 the first player just discarded on my 12 and the third position, i will then have to type "discard" and "1" and "3")

You can save at the end of each turn by typing S,and Y to confirm the beginning of the saving process.You will have a chance to load your previous game at the beginning of the character creation in your next game.

# Built with
### C language
https://cours.cyu.fr/course/view.php?id=334
https://cours.cyu.fr/course/view.php?id=340

# Documentation
https://www.unicode.org/charts/PDF/U2600.pdf
