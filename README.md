# Environment :

OS : macOS Mojave (10.4.6)  
IDE :  xCode (11.2.1) with OpenCV 3.0

# Objectives: 

The objective of this project is clear: you have to be able to move the mouse cursor... without touching the mouse!
In other words, it is necessary to make the mouse dynamic while keeping a distance with the computer.

To do this, we are going to move the cursor with our hand. Our program must be able to recognize and follow the hand. Around our hand, the program will draw a rectangle whose center corresponds to the position of the dynamic cursor.
Then we should be able to generate a left mouse click by color recognition.
Indeed, when the user wishes to make a left click, he must turn his hand over to reveal a blue color patch. Once the color has been detected, the system translates this into a left click.

You can see the demo here :  
Hand Tracking : https://youtu.be/-0gHWn1T9rI   
Mouse Moving : https://youtu.be/bNElZO8QxvI  
Mouse Clicking : https://youtu.be/5xloW0aQScs    

Note : I you are on macOS and want to execute the code. The program will take control of your mouse. If you do not wan to, you can uncomment the line 75 of handContour.cpp that call the mouse functions

# To do:
You will need to specify the path the the .xml classifier file. You can find it among the cpp and hpp files in the repository. So uncomment line 31 & 32 of main.cpp
