#pragma once

#include "ofMain.h"
#include "country.hpp"
#include <vector>
#include <random>
#include "iostream"
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        Country getRandom_country(vector<Country> countries);
    
        //parses a text file with the corresponding country names from the mp3 file
        vector<Country> get_country_names(string filePath);
    
        //converts a string to int
        int string_to_int(string line_of_txt);
    
        //gets the 3 int values for a countries rotation and places them in a vector. That value is for each country which is then placed into another vector representing the total countries.
        vector<vector<int>> get_countryRot(string filePath);

    
    
    //Determines if we want to display keys for UI or not.
    bool keyBox;
    
    
    //this will be true if we wish to rotate the sphere.
    bool rotate;
    
    //Draw axis of sphere
    bool displayAxis;
    
    //Display the current country of the song that is playing
    bool displayCountry;
    
    
    //draw normal lines of the sphere
    bool drawNormals;
    
    
    //draw wire frame of the sphere.
    bool drawWireFrame;
    
    //sound
        ofSoundPlayer sound;
    //sphere
        ofSpherePrimitive sphere;
        ofPlanePrimitive plane;
    
    //lights
        ofLight light1;
        ofLight light2;
        ofTexture mTex;
        ofEasyCam cam;
    
    //background of the universe
        ofImage stars;
    
    ofNode originalView;
    
    
    //determines how fast rotation is
    float spinY;
    
    //the name of the current country the user is listening to
    string current_country;
    
    
    //The visual answer on the gui that will be given to the user
    string country_answer;
    
    //all of the countries from the data file
    vector<Country> countries;
    
    
    //all of the pan tilt and rotation values for each country as integers
    vector<vector<int>> country_rot;
    
    //the last country whose song was played.
    Country lastCountry;
    
    string input_str;
    
    bool get_user_input;
    
    
    //BELOW ARE VALUES USED SOLELY FOR DATA MINING
    int total_pan;
    int total_tilt;
    int total_roll;
    
    
    int total_correct;
    int total_played;
    
};
