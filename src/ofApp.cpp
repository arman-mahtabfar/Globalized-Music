#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("MUSIC AROUND THE WORLD");
    
    //set the background to black
    ofBackground(ofColor::black);
    
    //PURELY FOR FINDING TOTAL OFFEST ROTATION FROM ORIGIN
    total_pan = 0;
    total_roll = 0;
    total_tilt = 0;
    
    //enable the ability to draw the setbox.
    keyBox = true;
    
    //the input string is empty
    input_str = "";
    
    //get user input
    get_user_input = false;
    
    //user has not guessed correctly yet
    correct_answer = false;
    
    //enable rotation of globe
    rotate = true;
    
    //display the country on the globe
    displayCountry = false;
    
    //display the axis of the sphere
    displayAxis = true;
    
    //display normal lines of sphere
    drawNormals = false;
    
    //draw wire frame of sphere
    drawWireFrame = false;
    
    //These will change everytime we generate a random country.
    country_answer = "None";
    current_country = "None";
    
    
    //the last country that played does not exist so initialize its name to empty
    lastCountry.name = " ";
    
    
    
    //Load the 2d image of the globe
    countries = get_country_names("/Users/arman.mahtabfar/Desktop/of_v0.10.1_osx_release/apps/myApps/emptyExample/src/countries_name.txt");
    
    //load corresponding rotations of these countries
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
        OF_EXIT_APP(0);
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
    
    //if the rotate key indicates true, allow the sphere to spin.
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
    
    //Everytime I call draw I must also draw the image of the stars. but I first must do this by disabling the depth.
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
    if (displayAxis) {
        sphere.drawAxes(sphere.getRadius() + 70);
    }
    
    if (drawNormals) {
        sphere.drawNormals(sphere.getRadius() + 5);
    }
    
    mTex.unbind();
    
    if (drawWireFrame) {
        sphere.drawWireframe();
    }
    
    ofDisableDepthTest();
    ofFill();
    cam.end();
    
    //for the UI for readers to know what is happening
    if(keyBox) {
        stringstream key_box_string;
        key_box_string << "Keys: " << endl << endl;
        key_box_string << "(1): Toggle spin" <<endl;
        key_box_string << "(2): Reset view" <<endl;
        key_box_string << "(3): Guess"<<endl;
        key_box_string << "(RETURN): Display Country" << endl;
        key_box_string << "(5): Toggle Axis Display" <<endl;
        key_box_string << "(6): Roll (Around blue axis)" << endl;
        key_box_string << "(7): Pan (Around green axis)" << endl;
        key_box_string << "(8): Tilt (Around red axis)" << endl;
        key_box_string << "(9): Toggle Wire frame" << endl;
        key_box_string << "(0): Toggle Normal lines" << endl;
        key_box_string << "(h): Toggle Key Display"<<endl;
        key_box_string << "Current Country: " << country_answer <<endl;
        ofDrawBitmapStringHighlight(key_box_string.str().c_str(), 20, 20);
    }
    
    //lets them guess the correct country whose song is playing.
    if (get_user_input == true) {
        stringstream guessbox;
        guessbox << "Type the name of the country below: " <<endl << endl;
        guessbox << input_str << endl;
        guessbox << "Press RETURN to enter guess." << endl;
        ofDrawBitmapStringHighlight(guessbox.str().c_str(), 20, 700);

    }
    
    //if they are done guessing it should display either correct or incorrect at the center of the globe.
    if (displayCountry) {
        stringstream country_display;

        if (correct_answer) {
            country_display << "'" << country_answer <<"'" << " is CORRECT!";
        } else {
            country_display<< "'" << input_str <<"'" << " is INCORRECT!";

        }
        ofDrawBitmapStringHighlight(country_display.str().c_str(), 460, 378);
    }
    
    //Total score to be displayed at the top right.
    stringstream score;
    score << "Total Correct:" << total_correct << endl;
    score << "Total Played:" << total_played << endl;
    ofDrawBitmapStringHighlight(score.str().c_str(), 850, 20);



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //the user can type his response
    if (get_user_input == true) {
        if (key == OF_KEY_RETURN) {
            get_user_input = false;
        } else {
            if (key == OF_KEY_BACKSPACE) {
                if (input_str.size() > 0) {
                    input_str.pop_back();
                }
                return;
            }
            string add(1, (char)key);
            input_str.append(add);
            return;
        }
    }
    
    
    if (key == '3') {
        
        total_played++;
    
        currently_playing_round = true;
        
        //Allow for user input to guess country.
        get_user_input = true;
        
        input_str = "";
        
        //GENERATE random country/anthem
        
        Country rand_country = getRandom_country(countries);
        
        
        lastCountry = rand_country;
        
        
        country_answer = "?????";
        
        current_country = rand_country.name;
        
        displayCountry = false;

        
        sound.load(current_country + ".mp3");
        sound.play();
        
        //Get the sphere to stop rotating, and shine a light on the desired path.
        rotate = false;
        
        //reset position of globe
        sphere.setOrientation(ofQuaternion(0, ofVec3f(0,0,0)));
        
        //rotate to the current rand country
        sphere.panDeg(rand_country.pan_y);
        sphere.tiltDeg(rand_country.tilt_x);
        sphere.rollDeg(rand_country.roll_z);
        
    }
    
    
    if (key == '2') {
        //RESET (Continue spinning and stop music)
        
        sphere.setOrientation(ofQuaternion(0, ofVec3f(0,0,0)));
        //Continue to spin
        rotate = true;
        sound.stop();
        
        country_answer = "None";
        current_country = "None";
        displayCountry = false;
        
    }
    
    
    if (key == '1') {
        //Toggle SPINNING GLOBE
        rotate = !rotate;
    }
    
    
    if (key == OF_KEY_RETURN) {
        if (currently_playing_round) {
            currently_playing_round = false;
            
            //REVEAL the name of the country
            country_answer = current_country;
            
            string lower_case_country = current_country;
            lower_case_country.at(0) = (char)lower_case_country.at(0) + 32;
            
            if (lower_case_country == input_str) {
                total_correct++;
                correct_answer = true;
            } else {
                correct_answer = false;
            }
            
            displayCountry = true;
        }
    }
    
    if (key == 'h') {
        keyBox = !keyBox;
    }
    
    if (key == '5') {
        displayAxis = !displayAxis;
    }
    
    
    //ROTATES AROUND GREEN AXIS
    if (key == '7') {
        total_pan = total_pan + 5;
        sphere.panDeg(5);
    }
    
    //ROTATES AROUND BLUE AXIS
    if (key == '6') {
        total_roll = total_roll + 5;
        sphere.rollDeg(5);
    }
    
    //ROTATES AROUND RED AXIS
    if (key == '8') {
        total_tilt = total_tilt + 5;
        sphere.tiltDeg(5);

    }
    
    //Print rotate values, this is solely for me to manually input rotation data.
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
    
    
    if (key == '0') {
        drawNormals = !drawNormals;
    }
    
    if (key == '9') {
        drawWireFrame = !drawWireFrame;
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
    
    //this will set the camera to its orignal spot, fixing the issue of location spot
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
    //make sure they are not the same.
    if (countries.at(i).name == lastCountry.name) {
        return getRandom_country(countries);
    }
    return countries.at(i);
}


//--------------------------------------------------------------
vector<Country> ofApp::get_country_names(string filePath) {
    vector<Country> countries_in_file;
    
    ifstream stream;
    stream.open(filePath);
    if (stream.fail()) {
        cerr << "Error opening the desired data file." << endl;
        return countries_in_file;
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
        return toReturn;
    }
    
    
    string line_of_text;
    
    while (!stream.eof()) {
        getline(stream, line_of_text);
        vector<int> current_country_rot;
        
        vector<string> values_as_string = ofSplitString(line_of_text, ",");
        if (line_of_text.size() != 0) {
            for (unsigned int i = 0; i < values_as_string.size(); i++) {
                int toAdd = string_to_int(values_as_string.at(i));
                current_country_rot.push_back(toAdd);
            }
            
            if (current_country_rot.size() == 3) {
                toReturn.push_back(current_country_rot);
            }

        }
    }
    return toReturn;
}
