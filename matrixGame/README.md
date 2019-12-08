Bomberman  
  
This project is a treasure hunt (maze) type of game that uses the bomb mechanics from bomberman, but it's objective is different: you can't see the goal, but a RGB led shows you how close you are to the goal, in the manner of hot/cold.

![scheme](https://user-images.githubusercontent.com/49508930/70392336-c0bd6980-19e7-11ea-96c5-91d0b44a3abc.png)

Hardware:  
The hardware needed for this project is:  
* for output of the game state: 8x8 LED matrix for the maze, RGB led for the goal info, active Piezo Buzzer for some sounds (bomb, death, level completed) and the LCD for viewing the game info (level, time left, lives left, score)  
* for input of the controls: joystick for movement and bomb placing and a button for early detonation of bomb  
* for control: Arduino UNO board, MAX7219 Driver, a switch for on/off, wires, resistors, a potentiometer for the LCD, connector cable. 
