/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <iostream>
#include "E101.h"

using namespace std;

int main() {
  int err = init(0);
  cout<<"Error: "<<err<<endl;
  open_screen_stream();
  
  bool startUpCheck = false;
  
  int xPos;
  int yPos;
  
  // make 1000 runs  
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
	for(int row = 0; row < 240; row++) {
		int firstX = -1;
		int lastX = -1;
		bool foundRed = false;
		for(int col=0; col < 320; col++) {
			//double redness = (double)get_pixel(row,col,0)/(double)get_pixel(row,col,3);
			//if(redness > minimumRedness) {
			bool redness = (double)get_pixel(row,col,0) > 2 * (double)get_pixel(row,col,1) && (double)get_pixel(row,col,0) > 2 * (double)get_pixel(row,col,2);
			if(redness == true) {
				if(firstX == -1) {
					firstX = col;
				}
				foundRed = true;
			}
			else {
				if(firstX != -1 && lastX == -1) {
					lastX = col - 1;
				}
			}
			currentPosX += (lastX-firstX)/2;
			totalPixels++;
		}
		if(foundRed == true) {
			if(firstY == -1) {
				firstY = row;
			}
		}
		else {
			if(firstY != -1 && lastY == -1) {
				lastY = row - 1;
			}
		}
		redPixels += lastX - firstX;
		nonRedPixels += firstX + (320-lastX);
		currentPosY += (lastY-firstY)/2;
	}
	currentPosX /= 320;
	currentPosY /= 240;
	if(startUpCheck == false && countrun > 0) {
		if(redPixels > 2500) {
			cout<<"Ruby Present on start up: true"<<endl;
		}
		else {
			cout<<"Ruby Present on start up: false"<<endl;
			return 0;
		}
		startUpCheck = true;
		xPos = currentPosX;
		yPos = currentPosY;
		//cout<<" Start XPos: "<<currentPosX<<endl;
		//cout<<", Start YPos: "<<currentPosY<<endl;
		//cout<<", Start RedPixels: "<<redPixels<<endl;
	}
	
	if(countrun > 0) {
		if(currentPosX > xPos) {
			if(currentPosX-xPos > 50) {
				cout<<"ALARM!"<<endl;
				//cout<<" countrun: "<<countrun<<endl<<endl;
				//cout<<" XPos: "<<currentPosX<<endl;
				//cout<<", YPos: "<<currentPosY<<endl;
				//cout<<", RedPixels: "<<redPixels<<endl;
				return 0;
			}
		}
		else {
			if(xPos-currentPosX > 50) {
				cout<<"ALARM!"<<endl;
				//cout<<" countrun: "<<countrun<<endl<<endl;
				//cout<<" XPos: "<<currentPosX<<endl;
				//cout<<", YPos: "<<currentPosY<<endl;
				//cout<<", RedPixels: "<<redPixels<<endl;
				return 0;
			}
		}
		if(currentPosY > yPos) {
			if(currentPosY-yPos > 50) {
				cout<<"ALARM!"<<endl;
				//cout<<" countrun: "<<countrun<<endl<<endl;
				//cout<<" XPos: "<<currentPosX<<endl;
				//cout<<", YPos: "<<currentPosY<<endl;
				//cout<<", RedPixels: "<<redPixels<<endl;
				return 0;
			}
		}
		else {
			if(yPos-currentPosY > 50) {
				cout<<"ALARM!"<<endl;
				//cout<<" countrun: "<<countrun<<endl<<endl;
				//cout<<" XPos: "<<currentPosX<<endl;
				//cout<<", YPos: "<<currentPosY<<endl;
				//cout<<", RedPixels: "<<redPixels<<endl;
				return 0;
			}
		}
		
		if(currentPosX == 100000 || currentPosY == 100000) {
			cout<<"ALARM!"<<endl;
			return 0;
		}
	}
	sleep1(100); // slow down a bit to make display easier
  }  
  close_screen_stream();
  return 0;
}
