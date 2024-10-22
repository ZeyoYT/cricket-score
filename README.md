# Cricket Match Simulation

This project is a Cricket Match Simulation program written in C++. It allows users to simulate a cricket match between two teams, track player performances, and display the match scores. The simulation includes features such as random match outcomes, score tracking, and team management.

## Features
1. **Team and Player Management:**
   - Allows creation of two teams with unique player names.
   - Each team consists of 11 players, and their scores are tracked.

2. **Score Simulation:**
   - Random outcomes for every ball, including scores (1, 2, 3, 4, 6), wickets, no-balls, and wides.
   - Automatic score calculation for individual players and the entire team.

3. **Extra Runs:**
   - Tracks extra runs through no-balls and wides.

4. **Innings Simulation:**
   - Simulates overs for each team and generates a match score.

5. **User Interaction:**
   - Menu options to play the game, display team scores, and exit.

## Requirements
- C++11 or later.
- Standard C++ libraries (`iostream`, `cstdlib`, `ctime`, `string`, `map`, `set`, `list`, `vector`, `iomanip`).

## How to Use
1. **Compiling the Program:**
   - Use a C++ compiler (e.g., g++) to compile the program:
     ```bash
     g++ cricket_simulation.cpp -o cricket_simulation
     ```

2. **Running the Program:**
   - Execute the compiled program:
     ```bash
     ./cricket_simulation
     ```

3. **User Inputs:**
   - Enter team names when prompted.
   - Enter the number of overs for the game.
   - Follow the menu options to either play the game or view team scores.

## Main Classes

### 1. `Players`
Handles player score tracking and generates a score table.
- **Methods:**
  - `playerNameList()`: Returns a list of player names.
  - `player(name, score)`: Adds or updates the player's score.
  - `generateScoreTable()`: Prints the scorecard.
  - `incrementExtraScore()`: Increments extras such as no-balls and wides.

### 2. `CricketTeam`
Inherits from `Players` and manages the team.
- **Methods:**
  - `getTeamName()`: Returns the team name.
  - `setIsBatting()`: Sets whether the team is batting.

### 3. `Cricket`
Simulates the match between two teams.
- **Methods:**
  - `play()`: Simulates the game with a given number of overs.
  - `simulateInnings()`: Simulates each innings for the team.
