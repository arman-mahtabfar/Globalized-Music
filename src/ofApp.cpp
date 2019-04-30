#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("MUSIC AROUND THE WORLD");
    
    
    //PURELY FOR FINDING TOTAL OFFEST ROTATION FROM ORIGIN
    total_pan = 0;
    total_roll = 0;
    total_tilt = 0;
    
    //set the background to black
    ofBackground(ofColor::black);
    
    //enable the ability to draw the setbox.
    keyBox = true;
    
    //enable rotation of globe
    rotate = true;
    
    //display the country on the globe
    displayCountry = false;
    
    country_answer = "None";
    current_country = "None";
    
    
    
    //Load the 2d image of the globe
    countries = get_country_names("/Users/arman.mahtabfar/Desktop/of_v0.10.1_osx_release/apps/myApps/emptyExample/src/countries_name.txt");
    
    country_rot = get_countryRot("/Users/arman.mahtabfar/Desktop/of_v0.10.1_osx_release/apps/myApps/emptyExample/src/country_rot.txt");
    
    
    //match the countries to country rotation.
    if (countries.size() == country_rot.size()) {
        for (unsigned int i = 0; i < countries.size(); i++) {
            countries.at(i).pan_y = country_rot.at(i).at(0);
            countries.at(i).tilt_x = country_rot.at(i).at(1);
            countries.at(i).roll_z = country_rot.at(i).at(2);

        }
    } else {
        std::cout << "You do not have the matching data files for countries.";
        

    }
    
    
    

    //laod the image of the stars for the background.
    stars.load("stars.jpg");
    
    
    //Set depth for gui
    ofDisableAlphaBlending();
    
    //This sets the 3d UI for the globe
    ofEnableDepthTest();
    
    
    //upload the image to the sphere
    ofDisableArbTex();
    ofLoadImage(mTex,"earth.jpg");
    
    //set the size of the sphere for the GUI
    sphere.setRadius(250);
    spinY = (0.2f);
    
    
    //This is to add lighting to increase visibility of spinning sphere.
    ofSetSmoothLighting(true);
    light1.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    light1.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    light2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    light2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    //set the radius and resolution of the sphere.
    ofSetSphereResolution(24);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (rotate) {
        sphere.rotateDeg(spinY, 0.0 , 1.0, 0.0);
    }
    
    
    //This helps make the stars much easier to see.
    light1.setPosition((ofGetWidth()*.3)+ cos(ofGetElapsedTimef()*.3)*(ofGetWidth()*.3), ofGetHeight()/2, 350);
    light2.setPosition((ofGetWidth()*.7)+ cos(ofGetElapsedTimef()*.7)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -100);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    ofPushStyle();
    glDisable(GL_DEPTH_TEST);
    stars.draw(0,0);
    glEnable(GL_DEPTH_TEST);
    ofPopStyle();
    
    //called time we draw a sphere.
    cam.begin();
    
    //bind text to the sphere.
    mTex.bind();
    
    //draw the sphere
    sphere.draw();
    sphere.drawAxes(sphere.getRadius() + 40);
    mTex.unbind();
    
    ofDisableDepthTest();
    ofFill();
    cam.end();
    
    if(keyBox) {
        stringstream key_box_string;
        key_box_string << "Keys: " << endl << endl;
        key_box_string << "(w): Stop rotating" <<endl;
        key_box_string << "(a): Reset" <<endl;
        key_box_string << "(s): Play random anthem"<<endl;
        key_box_string << "(d): Display Country" << endl;
        key_box_string << "Current Country: " << country_answer <<endl;
        key_box_string << "(r): Roll (Around blue axis)" << endl;
        key_box_string << "(p): Pan (Around green axis)" << endl;
        key_box_string << "(t): Tilt (Around red axis)" << endl;
        key_box_string << "(h): Toggle Key Display"<<endl;
        ofDrawBitmapStringHighlight(key_box_string.str().c_str(), 20, 20);
    }
    
    if (displayCountry) {
        stringstream country_display;
        country_display << country_answer;
        ofDrawBitmapStringHighlight(country_display.str().c_str(), 498, 378);
    }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //the music will play in the background once s is pressed.
    if (key == 's') {
        
        
        //GENERATE random country/anthem
        
        Country rand_country = getRandom_country(countries);
        
        country_answer = "?????";
        
        current_country = rand_country.name;
        
        displayCountry = false;

        
        sound.load(current_country + ".mp3");
        sound.play();
        
        //Get the sphere to stop rotating, and shine a light on the desired path.
        rotate = false;
        
        //Now I want the globe to point to a specific point (America)
        
        sphere.setOrientation(ofQuaternion(0, ofVec3f(0,0,0)));
        
        
        sphere.panDeg(rand_country.pan_y);
        sphere.tiltDeg(rand_country.tilt_x);
        sphere.rollDeg(rand_country.roll_z);
        
        std::cout << rand_country.pan_y << endl;
        std::cout << rand_country.tilt_x<< endl;
        std::cout << rand_country.roll_z<< endl;


    }
    
    
    if (key == 'a') {
        //RESET (Continue spinning and stop music)
        
        sphere.setOrientation(ofQuaternion(0, ofVec3f(0,0,0)));
        //Continue to spin
        rotate = true;
        sound.stop();
        
        country_answer = "None";
        current_country = "None";
        displayCountry = false;
        
    }
    
    
    if (key == 'w') {
        //STOP SPINNING GLOBE
        rotate = false;
    }
    
    
    if (key == 'd') {
        //REVEAL the name of the country
        
        country_answer = current_country;
        
        displayCountry = true;
    }
    
    if (key == 'h') {
        keyBox = !keyBox;
    }
    
    
    //ROTATES AROUND GREEN AXIS
    if (key == 'p') {
        total_pan = total_pan + 5;
        sphere.panDeg(5);
    }
    
    //ROTATES AROUND BLUE AXIS
    if (key == 'r') {
        total_roll = total_roll + 5;
        sphere.rollDeg(5);
    }
    
    //ROTATES AROUND RED AXIS
    if (key == 't') {
        total_tilt = total_tilt + 5;
        sphere.tiltDeg(5);

    }
    
    //Print rotate values
    if (key == 'b') {
        total_tilt = total_tilt % 360;
        total_pan = total_pan % 360;
        total_roll = total_roll % 360;

        std::cout << "PAN: " << total_pan << endl;
        std::cout << "TILT: " << total_tilt << endl;
        std::cout << "ROLL:" << total_roll << endl;
    }
    
    //Reset Rotation Values. Purely for finding data for the country rotation text file.
    if (key == 'l') {
        sphere.setOrientation(ofQuaternion(0, ofVec3f(0,0,0)));
        total_tilt = 0;
        total_roll = 0;
        total_pan = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //sphere.setOrientation(ofQuaternion(0, ofVec3f(0,0,0)));
    cam.reset();
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}




//--------------------------------------------------------------
Country ofApp::getRandom_country(vector<Country> countries) {
    unsigned int i = rand() % countries.size();
    return countries.at(i);
}


//--------------------------------------------------------------
vector<Country> ofApp::get_country_names(string filePath) {
    vector<Country> countries_in_file;
    
    ifstream stream;
    stream.open(filePath);
    if (stream.fail()) {
        cerr << "Error opening the desired data file." << endl;
        terminate();
    }
    
    string line_of_text;
    
    while (!stream.eof()) {
        getline(stream, line_of_text);
        if (line_of_text.size() != 0) {
            Country country;
            country.name = line_of_text;
            countries_in_file.push_back(country);
        }
    }
    return countries_in_file;
}

//--------------------------------------------------------------
int ofApp::string_to_int(string line_of_txt) {
    int toReturn = stoi(line_of_txt);
    return toReturn;
}



//--------------------------------------------------------------
vector<vector<int>> ofApp::get_countryRot(string filePath) {
    vector<vector<int>> toReturn;
    ifstream stream;
    
    
    stream.open(filePath);
    if (stream.fail()) {
        cerr << "Error opening the desired data file." << endl;
        terminate();
    }
    
    
    string line_of_text;
    
    while (!stream.eof()) {
        getline(stream, line_of_text);
        vector<int> current_country_rot;
        
        vector<string> values_as_string = ofSplitString(line_of_text, ",");
        for (unsigned int i = 0; i < values_as_string.size(); i++) {
            int toAdd = string_to_int(values_as_string.at(i));
            current_country_rot.push_back(toAdd);
        }
        
        if (current_country_rot.size() == 3) {
             toReturn.push_back(current_country_rot);
        }
    }
    return toReturn;
}
