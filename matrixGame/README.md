Bomberman  
  
This project is a treasure hunt (maze) type of game that uses the bomb mechanics from bomberman, but it's objective is different: you can't see the goal, but a RGB led shows you how close you are to the goal, in the manner of hot/cold.

![scheme](https://user-images.githubusercontent.com/49508930/70392336-c0bd6980-19e7-11ea-96c5-91d0b44a3abc.png)  
  
How to play:  
There are 15 levels in total, and they all have the same objective: find the hidden treasure.  
You are the blinking dot, and all the other visible dots are walls, which you can not pass through.  
The edge of the matrix is also like a wall: you can't pass it.  
You can move through the maze using the joystick, horizontally and vertically.
This means you can't go diagonally if the direct adjacent spots (horizontal and vertical) are walls.
The RGB LED helps you in finding the treasure by showing how far you are from it (blue - far, white - in between, red - close, blinking red - on the treasure)  
Go to the next level by pressing the green push button when you are on the treasure (RGB LED is blinking)  
If you press the green button when you're not on the treasure, you lose a life, and the current level is restarted.  
You have a total of 3 lives. If you run out of lives, it's game over!  
Each level has a time limit of 35 seconds. The faster you finish the level, the more points you gain for your score.  
If the level timer runs out, you lose a life and the level is restarted.  
You can place a bomb by pressing the joystick push button. It will show blinking and you will hear a sound that indicates how much time it has left until it will detonate.  
The bomb takes 3 seconds to detonate, and the detonation lasts for a couple of seconds, and you will see the affected area: the directy adjacent points on the matrix (only horizontally and vertically, in the shape of a "+").
If your player is in the detonation affected area, you lose a life.  
You can only place a single bomb at a time. If you want a second bomb, you need to wait for the detonation to end, and so on.
There are 3 types of level: levels which do not require any bomb in order to finish, levels that require at least one bomb, but the treasure is on an empty spot, and levels in which the bomb is always inside a wall.  
The score multiplier increases when you reach the more difficult levels.  
If you finish a level, you will hear a specific sound, for winning or losing.  
You can change the starting level in the settings. You can also change your name, so that it will show up in highscores if you get there.  
If you finish level 14 (they start at 0), you completed the game.  

Hardware:  
The hardware needed for this project is:  
* for output of the game state: 8x8 LED matrix for the maze, RGB led for the goal info, active Piezo Buzzer for some sounds (bomb, death, level completed) and the LCD for viewing the game info (level, time left, lives left, score)  
* for input of the controls: joystick for movement and bomb placing and a button for early detonation of bomb  
* for control: Arduino UNO board, MAX7219 Driver, wires, resistors, a potentiometer for the LCD, connector cable. 
