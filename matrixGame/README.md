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


Hardware:  
The hardware needed for this project is:  
* for output of the game state: 8x8 LED matrix for the maze, RGB led for the goal info, active Piezo Buzzer for some sounds (bomb, death, level completed) and the LCD for viewing the game info (level, time left, lives left, score)  
* for input of the controls: joystick for movement and bomb placing and a button for early detonation of bomb  
* for control: Arduino UNO board, MAX7219 Driver, wires, resistors, a potentiometer for the LCD, connector cable. 
