# Chess in C with ASCII Design
This is a simple implementation of the classic board game Chess in the C programming language. The game is designed with ASCII graphics, making it playable on any terminal or command prompt.

## Getting Started
To play the game, first, make sure you have a C compiler installed on your system. Then, download or clone the repository, navigate to the project directory, and run the following command in your terminal:

``` 
gcc chess.c -o chess 
```
This will compile the program and create an executable file called chess. To start the game, simply run the following command:

```bash
./chess
```

## How to Play
The game is played between two players on an 8x8 board. Each player has 16 pieces, consisting of one king, one queen, two rooks, two knights, two bishops, and eight pawns.

The objective of the game is to checkmate your opponent's king, which means putting it in a position where it is under attack and cannot escape capture.

To move a piece, enter the coordinates of the piece you want to move, followed by the coordinates of the square you want to move it to. For example, to move a pawn from e2 to e4, enter first location to old square and enter second location to new square.Like:
```
oldSquare: e2
newSquare: e4
```

The game follows standard chess rules, including castling, en passant, and pawn promotion. If you are unfamiliar with the rules, you can find them online or in a chess book.

ASCII Design
The game is designed with ASCII graphics, using simple characters to represent the chess pieces and board. The pieces are represented as follows:

### for black pieces
- King: BK
- Queen: BQ
- Rook: BR
- Knight: BN
- Bishop: BB
- Pawn: BP

### for white pieces
- King: WK
- Queen: WQ
- Rook: WR
- Knight: WN
- Bishop: WB
- Pawn: WP

The board is represented as an 8x8 grid of characters, with white squares represented as # and black squares represented as .. The rows are numbered 1-8, and the columns are labeled a-h.

# Conclusion
This implementation of Chess in C with ASCII design is a fun project for any chess enthusiast or programming hobbyist. It is a great way to learn the basics of programming and game development, and can be easily modified and customized to add new features and functionality.