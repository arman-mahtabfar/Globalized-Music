#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("MUSIC AROUND THE WORLD");
    
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
        
        
        int pan_int = -80;
        sphere.panDeg(pan_int);
        sphere.rollDeg(-40);
        sphere.tiltDeg(10);
        
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
        cerr << "Error opening the desired puzzle file." << endl;
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
