# Connect 4

The popular boardgame Connect 4

# Still to do:

- Check win conditions on diagonals from upper right to lower left
- Check draw condition when the field is full and no player has won
- Show which player's turn it is
- Create a nice animation when a stone is dropped
- Add a computer opponent

For the computer opponent, following strategies are feasible:
- Choose a random column that is not full
- Choose a column where the stone lands adjacent to an own stone (or random, if not possible)
- Also check, if the stone in that field can still lead to a win (i.e. other needed fields are unoccupied)

A more sophisticated strategy is the minimax-algorithm:
https://de.wikipedia.org/wiki/Minimax-Algorithmus

Good luck ;)

