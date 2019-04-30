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

TEST_CASE("Get country names") {
    vector<Country> countries = app.get_country_names("/Users/arman.mahtabfar/Desktop/of_v0.10.1_osx_release/apps/myApps/emptyExample/src/countries_name.txt");
    
    REQUIRE(countries.at(0).name == "Usa");
    REQUIRE(countries.at(countries.size() - 1).name == "Australia");
    REQUIRE(countries.at(4).name == "Nigeria");
    REQUIRE(countries.at(3).name == "Ghana");
    
    
    vector<Country> empty = app.get_country_names("Slfkjsal;dkfj");
    
    REQUIRE(empty.size() == 0);
    
    
}

TEST_CASE("Get country_rot") {
    vector<vector<int>> country_rotations = app.get_countryRot("/Users/arman.mahtabfar/Desktop/of_v0.10.1_osx_release/apps/myApps/emptyExample/src/country_rot.txt");
    
    
    int america_pan = country_rotations.at(0).at(0);
    int america_roll = country_rotations.at(0).at(2);
    
    REQUIRE(america_pan == 280);
    REQUIRE(america_roll == 320);
    
    int australia_pan = country_rotations.at(country_rotations.size() - 1).at(0);
    int australia_tilt = country_rotations.at(country_rotations.size() - 1).at(1);
    int australia_roll = country_rotations.at(country_rotations.size() - 1).at(2);
    
    REQUIRE(australia_pan == 40);
    REQUIRE(australia_tilt == 325);
    REQUIRE(australia_roll == 0);
    
    
    int kenya_pan = country_rotations.at(5).at(0);
    int kenya_tilt = country_rotations.at(5).at(1);
    int kenya_roll = country_rotations.at(5).at(2);

    REQUIRE(kenya_pan == 145);
    REQUIRE(kenya_tilt == 0);
    REQUIRE(kenya_roll == 0);

    vector<vector<int>> empty = app.get_countryRot("lksdfjlsk;dj;");
    REQUIRE(empty.size() == 0);
    
    
}


