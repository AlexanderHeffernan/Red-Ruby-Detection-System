#include <iostream>
#include "E101.h"

using namespace std;

int main() {
	// Initialise the camera
  	int err = init(0);
  	cout<<"Error: "<<err<<endl;
  	open_screen_stream();

	// Variable to check if startup check has been performed
  	bool startUpCheck = false;

	// Variables to store initial position
  	int xPos;
  	int yPos;
  
  	// Loop for 1000 runs  
  	for (int countrun = 0; countrun < 1000; countrun++) {
		take_picture();
		update_screen();
		
		int redPixels = 0;
		int totalPixels = 76800;
		int nonRedPixels = 0;
		int currentPosX = 100000;
		int currentPosY = 100000;
		
		int firstY = -1;
		int lastY = -1;
		// Loop through rows of the image
		for(int row = 0; row < 240; row++) {
			int firstX = -1;
			int lastX = -1;
			bool foundRed = false;
			// Loop through columns of the image
			for(int col=0; col < 320; col++) {
				// Check if pixel is red
				bool redness = (double)get_pixel(row,col,0) > 2 * (double)get_pixel(row,col,1) && (double)get_pixel(row,col,0) > 2 * (double)get_pixel(row,col,2);
				if(redness == true) {
					if(firstX == -1) { firstX = col; }
					foundRed = true;
				}
				else if (firstX != -1 && lastX == -1) { lastX = col - 1; }
				currentPosX += (lastX-firstX)/2;
				totalPixels++;
			}
			if(foundRed == true && firstY == -1) { firstY = row; }
			else if (firstY != -1 && lastY == -1) { lastY = row - 1; }
			redPixels += lastX - firstX;
			nonRedPixels += firstX + (320-lastX);
			currentPosY += (lastY-firstY)/2;
		}
		currentPosX /= 320;
		currentPosY /= 240;

		// Perform startup check after the first run
		if(startUpCheck == false && countrun > 0) {
			// Check if a certain number of red pixels are present on startup
			if(redPixels > 2500) {
				cout<<"Ruby Present on start up: true"<<endl;
			}
			else {
				cout<<"Ruby Present on start up: false"<<endl;
				return 0;
			}
			startUpCheck = true;
			// Store the initial position
			xPos = currentPosX;
			yPos = currentPosY;
		}

		// Check for alarm conditions after the first run
		if(countrun > 0) {
			if (abs(currentPosX - xPos) > 50 || abs(currentPosY - yPos) > 50 || currentPosX == 100000 || currentPosY == 100000) {
			    cout << "ALARM!" << endl;
			    return 0;
			}
		}
		sleep1(100); // slow down a bit to make display easier
	  }  
	  close_screen_stream();
	  return 0;
}
