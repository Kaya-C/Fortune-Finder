<!-- There should be a README.md file in the GitHub repo that explains how to use the app(s) you built,
with examples of usage, instructions on compilation and package installations that might be
necessary to compile the project, etc. When we grade your code deliveries, we will start with the
README.md and the --help flags, and use that as a guide to the functionality we are grading. -->

# 🌟 Fortune Finder 🌟
Fortune Finder is a terminal-based logic game inspired by Minesweeper. Your goal is to uncover treasures hidden in the grid while avoiding bombs. Use logic, strategy, and hint tiles to guide your decisions! Good Luck!

## Compilation (Installations)
__"gcc" compiler__ is required to build the executable. Then to create the executable, run:
```bash
make fortuneFinder
```
## Usage
### Run the game
To play the game, run:
```bash
./fortuneFinder
```
### Command-Line Flags
*Flags are Optional*
- --help	Shows instructions on how to play.
- --mode easy	Starts the game in Easy mode (default).
- --mode hard	Starts the game in Hard mode.
- --test easy   Starts TESTING the game in Easy mode.
- --test hardd  Strats TESTING the game in Hard mode.
- Note: If no mode is given, Easy mode is used automatically.

## How to Play
Here are a few example commands you can run:
```bash
$ ./fortuneFinder
```
```text
Starting game in easy mode.
Score has been reset to 0.

Enter a box number between 1 and 25 (or 0 to quit): 2
------------------------------
|  1 ||  . ||  3 ||  4 ||  5 |
------------------------------
|  6 ||  7 ||  8 ||  9 || 10 |
------------------------------
| 11 || 12 || 13 || 14 || 15 |
------------------------------
| 16 || 17 || 18 || 19 || 20 |
------------------------------
| 21 || 22 || 23 || 24 || 25 |
------------------------------
There are 2 treasures and 0 bombs besides you

Your current score: 0/6
There are 4 bombs and 5 hints in total.
```
### Legend (Type of cells)
\* = Treasure  
B = Bomb  
? = Hint Box  
#### Difficulty Modes
|  Mode	     | Grid Size | Treasures | Bombs	| Hints  | 
| ---------- | --------- | ----------| ------ | ------ |
|  Easy	     | 5 x 5     | 6         | 4      | 5      |  
|  Hard	     | 6 x 6     | 5         | 8      | 3      |          	    

#### The Rules of the Game
- Revealing a treasure increases your score.
- Revealing a bomb ends the game immediately.
- Revealing a hint gives the posibility on occurance of bombs/treasures nearby.
- Collect all treasures to win the game.

## Credits
**Course:** SFWR ENG 2XC3 - Software Development Basics  
**Date:** 2025-11-28   
**Group Members:**
| Name       | Student # | Github ID    | Role Title   |
| ---------- | --------- | ------------ | ------------ |
| Parnia Yazdinia      | 400567795    | parniayzdin     | Main Program & Input validation    |
| Joanna Fan        | 400555855    | JoooannaF       | Score and Feedback displayer    |
| Catherine Joseph    | 400576163    | Catherine-Jo   | Game Initializer       |
| Zain Khalbous      | 400546696    | khalbouz     | Map Display     |
