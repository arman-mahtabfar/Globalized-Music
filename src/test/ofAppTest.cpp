//
//  ofAppTest.cpp
//  emptyExample
//
//  Created by Arman Mahtabfar on 4/30/19.
//

#define CATCH_CONFIG_MAIN
#include <stdio.h>
#include "catch.hpp"
#include "ofApp.h"
#include "country.hpp"

ofApp app;

TEST_CASE("test string to int") {
    string ints_as_string = "1234";
    
    int converted = app.string_to_int(ints_as_string);
    
    REQUIRE(converted == 1234);
}


TEST_CASE("get random country") {
    vector<Country> countries;
    
    Country america;
    america.name = "Usa";
    america.pan_y = 70;
    america.tilt_x = 60;
    america.roll_z = 80;

    countries.push_back(america);
    Country canada;
    canada.pan_y = 70;
    canada.tilt_x = 60;
    canada.roll_z = 80;
    canada.name = "Canada";
    countries.push_back(canada);

    Country rand = app.getRandom_country(countries);
    
    REQUIRE(rand.name.size() != 0);
    REQUIRE(rand.pan_y == 70);
    REQUIRE(rand.tilt_x == 60);
    REQUIRE(rand.roll_z == 80);
}


