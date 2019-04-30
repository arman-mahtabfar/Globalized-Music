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
        vector<Country> get_country_names(string filePath);
        int string_to_int(string line_of_txt);
        vector<vector<int>> get_countryRot(string filePath);

    
    
    //Determines if we want to display keys for UI or not.
    bool keyBox;
    
    
    //this will be true if we wish to rotate the sphere.
    bool rotate;
    
    bool displayCountry;
    
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
    
    
    
    float spinY;
    string current_country;
    
    string country_answer;
    
    vector<Country> countries;
    
    vector<vector<int>> country_rot;
    
    int total_pan;
    int total_tilt;
    int total_roll;
    
};
