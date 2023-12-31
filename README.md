<h1>Space Shooter Game Description</h1>
  <p>
    The code represents a basic implementation of a Space Shooter game in C++. The game is played within a console window and involves controlling a spaceship, shooting aliens, and earning points.
  </p>
  <p>
    The code begins by including the necessary header files, such as 'iostream', 'fstream', 'windows.h', etc. These headers provide the required functionalities for input/output, file handling, console manipulation, and timing.
  </p>
  <p>
    The code defines various functions that handle different aspects of the game. These functions include `printShip` to display the ship, `printBorder` to draw the border and game elements, `makeAlien` to generate aliens randomly, `makeBullet` to create bullets when the player shoots, and several other functions to move objects, check for collisions, and update the game state.
  </p>
  <p>
    The <code>start</code> function is the main function responsible for running the game. It initializes the game variables, sets the initial positions of the ship and aliens, and enters a loop that continues until the game ends. Within this loop, the function checks for user input, moves the ship accordingly, handles shooting bullets, updates the positions of aliens and bullets, checks for collisions, and updates the game state. The loop also adjusts the game speed based on the player's progress.
  </p>
  <p>
    The game ends when the player loses all their lives or reaches the maximum score. After the game ends, the code displays a game over or victory message, shows the player's score and stage, and updates the highest score if necessary.
  </p>
