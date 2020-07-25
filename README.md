Tetris
========

![Tetris ui](https://i.imgur.com/zN3gLA5.png)

Instructions to play the game:
- A, D: Move right and left
- S: Move faster down
- X: Move instantly down
- W: Hold the current tetromino. Can only be used again after the tetromino has landed
- Q, E: Rotate the tetromino clock and counterclock wise

The tetrominos fall down in a 10x20 grid. Your goal is to get full rows.
For each full row you get 10 points and if you have more than one at a time you get extra points.

The program is implemented in 3 classes to achieve ease if needed to implement new featuers.
The classes are MainWindow, Tetromino, and Square. The purposes of the class are as follow:
	MainWindow: Runs the main game loop, holds all the Squares etc.
	Tetromino: Holder for Squares with handy functions for moving, rotating etc.
	Square: The smallest instance in the game. Derives from the QGraphicItem and draws the squares, moves around etc.

The main goals in the design and implementation was ease to make new features.
The implementation is modular and uses OOP paradigms.

