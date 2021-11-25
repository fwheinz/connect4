# Connect 4

The popular boardgame Connect 4

# Still to do:

- Fix a bug: The last column cannot be filled

- Test with other field sizes and win conditions (connect 5 for example)

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

# Submitting your modifications

It would be great if you submit your modified game for review. If you want to receive feedback,
put your email address into a comment inside the source file along with a
short description of the changes you have made. To perform the submission, use the command

make submit


Good luck ;)

