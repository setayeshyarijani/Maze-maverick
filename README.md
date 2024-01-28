This program, authored by Kimia and Setayesh with student IDs 400551016 and 402442441, displays the game in which the user has the ability to build mazes with different difficulty levels, solve the maze and see the results of past games and use previously added maps.
This program has different sections such as:
 1-create map in two level : easy & hard .
 2-play game with exist maps or custome map .
 3-see the right path of exist map or custome map .
 4-see the information of user such as :the number of games , the number of wins , total user gametime , ...
 5-history of past and finished games .

Now, explanations about the various functions of the program:

 1-create map:
  In this function, by entering the number 1 for easy and 2 for difficult, you can create a custom map.
  1. For the easy map, you need to enter the number of blocks for length and width. The values of the cells range from 3 to 3, and the number of zero cells ranges from 2 to 5.
  2. In the difficult part, the input includes length, width, the range of cell values, and the range of the number of zero cells.
  Based on the given inputs, a custom map is created, and the name of the map is also taken as input.
   
 2-findPath :
  This code is a recursive function findPath that aims to find a path through a grid from point (0, 0) to point (n-1, m-1). It employs a random walk algorithm to explore possible paths.
  1. It marks the current cell (x, y) as visited by setting a[x][y] = 1.
  2. If the current position is at the end of the grid (`x == n - 1 && y == m - 1`) and the path length is equal to the maximum allowed length (`pathLength == step`), it sets flag = 0 to indicate the path is found and returns.
  3. If the path length exceeds the maximum allowed length (`pathLength > step - 1`), it marks the current cell as not part of the valid path (`a[x][y] = 2`) and returns.
  4. It defines a vector of possible moves (`moves`) representing four directions: down, right, up, and left.
  5. It shuffles the moves vector to randomize the exploration order.
  6. It iterates over each possible move:
   - It calculates the new position after the move.
   - If the new position is valid (within the grid boundaries and not already visited), it recursively calls findPath with the new position.
   - If flag becomes 0 (indicating the path is found), it returns immediately.
  7. If no valid moves are available from the current position, it marks the current cell as not part of the valid path (`a[x][y] = 2`) and decrements the path length before returning.
  Overall, this function explores random paths through the grid until it finds a path from (0, 0) to (n-1, m-1) with the specified maximum length or exhausts all possible paths.
  
 3-solveMaze :
  This function solvemaze() is responsible for allowing the user to solve a maze. Here's a breakdown of its functionality:
  1. It clears the screen and prints the title "Solve maze" in red.
  2. It prompts the user to choose one of three options: 
   - Choose from existing maps
   - Import a custom map
   - Back to the menu
  3. If the user chooses to select from existing maps:
   - It displays a list of available maps from the "mapslist.txt" file.
   - It prompts the user to enter the name of the desired map.
   - It opens the selected map file if it exists.
  4. If the user chooses to import a custom map, it prompts them to enter the address of the custom map and opens it.
  5. If the user chooses to go back to the menu, the function returns.
  6. It initializes two 2D vectors: mapvalues to store the values of the maze, and b to mark visited cells during pathfinding.
  7. It reads the values of the maze from the file into the mapvalues vector.
  8. It initializes the b vector to mark all cells as unvisited (initialized to value `2`).
  9. It calls the resultpath() function to find the path through the maze, passing necessary parameters.
  10. It prints the maze with the solution path highlighted in blue.

 4-resultPath :
  This function resultpath is used to recursively find a valid path through a maze represented by a 2D grid. Here's a breakdown of its functionality:
  1. It marks the current cell (x, y) as visited by setting a[x][y] = 1 and updates the sum of values along the path.
  2. If the current position is at the end of the grid (`x == n - 1 && y == m - 1`) and the path length is equal to the maximum allowed length (`pathLength == step`) and the sum along the path equals twice the value of the destination cell, it sets flag = 0 to indicate the path is found and returns.
  3. If the path length exceeds the maximum allowed length (`pathLength > step - 1`), it marks the current cell as not part of the valid path (`a[x][y] = 2`), updates the sum, and returns.
  4. It checks each move for validity and recurses into resultpath() for valid moves.
  5. If flag becomes 0 (indicating the path is found), it returns immediately.
  6. If no valid moves are available from the current position, it marks the current cell as not part of the valid path (`a[x][y] = 2`), updates the sum, and decrements the path length before returning.
  Overall, this function recursively explores the maze to find a valid path within the specified constraints.

 5-isValid :
  This function isValid checks whether a given position (x, y) is valid within the boundaries of a grid represented by a 2D vector a, and if the cell is not marked as visited (`a[x][y] != 1`). Here's how it works:
  1. Return Value:
   - It returns true if the cell (x, y) is within the grid boundaries (`x >= 0 && x < n && y >= 0 && y < m`) and is not marked as visited (`a[x][y] != 1`).
   - Otherwise, it returns false.
  2. Overall:
   - This function is used in maze-solving algorithms to determine if a move to a certain position (x, y) is valid, considering both the grid boundaries and  whether the cell has been visited before. If the function returns true, it indicates that the move is permissible, and if it returns false, the move is considered invalid.
 
 6-playground :
  This function playground() allows the user to play a maze game. Here's a brief explanation:
  1. It clears the screen and displays "Playground" in red.
  2. It prompts the user to choose from existing maps, import a custom map, or go back to the menu.
  3. If the user selects an existing map, it displays the available maps and prompts for a choice. It then opens the selected map file.
  4. If the user imports a custom map, it prompts for the map's address and opens it.
  5. It enters a loop to handle the game:
   - It displays the map's current status, with the user's position highlighted.
   - It allows the user to move within the maze using WASD keys.
   - It breaks the loop if the user reaches the end of the maze, presses Escape, or runs into a wall.
   - It updates the sum of values along the path as the user moves.
  6. After the game ends, it displays the result (win or lose) and waits for the user to press Enter to continue.
  7. It calculates the game time.
  8. It updates the user's information and game history.
  This function effectively handles user interaction, maze navigation, and game outcome determination.
   
 7-saveMap :
  This function savemap is designed to save a maze map into a file.
  1. It takes in the dimensions of the maze (`n` rows and m columns), the number of steps taken to solve it (`step`), and the maze itself (`mazemap` vector). 
  2. It prompts the user for a map name, updates a list of maps in a file, and saves the maze configuration into a text file with the provided map name in a specific directory. Finally, it writes the maze configuration and the number of steps into the file in a specific format.

 8-updateUser :
  This function updates user data stored in a text file. It takes parameters for the user's name, game result ("Win" or otherwise), and game time. 
  1. It opens a file corresponding to the user's name.
  2. If the user exists (file is open), it reads their previous game data, increments game counts, updates win count and game time accordingly, and then writes the updated data back to the file.
  3. If the user is new (file is not open), it creates a new file for the user, initializes game data based on the result, and writes it to the file.

 9-updateHistory : 
  This function updates a history file with the details of a recent game.
  1. It reads the existing history file, prepends the new game details to it (limiting to the last 10 games), and then writes the updated history back to the file. 
  2. The game details include the date, username, map name, game time, and result of the game.
 
 10-user :
  This function prompts the user to enter their username, then attempts to open a file corresponding to that username in the "Users" directory. 
  1. If the user exists, it reads and displays their total games played, total wins, game time, and total game time. If the user doesn't exist, it notifies the user that no user was found.

 11-history :
  This function displays the contents of the "history.txt" file, located in the "History" directory, on the console.
  1. It prints the title "History" in red, then reads each line of the file and prints it to the console. Finally, it closes the file.