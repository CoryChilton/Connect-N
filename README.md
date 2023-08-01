# Connect N Bot

A Connect N game I coded in C++ using object-oriented programming. It is like Connect 4 but you can play with any size board and choose how many in a row it takes to win. You can play player vs. player, against a bot that plays poorly, against a bot that always plays perfectly, or even have bots play against each other!

### Video Example ([YouTube Example]())

### More information

The most difficult part of this project was coding the bot that always plays perfectly. It uses the minimax algorithm which is a recursive backtracking algorithm that is used in game theory to find the optimal move. Using minimax, given the current state of the game, the bot considers every possible combination of moves that could happen from both players until the game finishes, and then backtracks from those results assuming its opponent and itself always choses the move that would lead to the best result for themselves. From there it choses the move in the current game state that will lead to the best result. This algorithm is not perfect however, since it uses brute force it can also be temporally expensive when the board size grows large.
