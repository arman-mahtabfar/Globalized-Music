# Project Log

## April 8, 2019

* Today, I created the project space using the open frameworks generator, and added the ofxGui library. After doing so, I am starting to understand how the OF libraries work, and how I am going to implement them in my goal of finishing the project. Currently, I am understand how memory allocation works, and how I can create a visual representation of it. Currently, I am also debating on using the 3D library/ which library I should use, depending on my moderator's response.
* Edited the Proposal.md file.
* Reading Boehm Garbage Collector Doc

## April 9, 2019

* Today, I began to experiment with the 3D library by editing the advance3D example that open frameworks provided. What I have noticed is that for every open frameworks project there is a class called ofBaseApp that is inhereted from the ofApp, that has crucial functions to the gui such as setup, update, and draw.
* Finally, I used the emptyExample that is automatically created in my OF space, and then I used functions like the ofBackground and ofsetwindow title to start modifying my example gui.
* I also started implementing the of3d primitives to draw a sphere when the app is run.
* Extremely confused on exactly what ofMesh and ofNode

## April 10, 2019
* Implemented an example use of the 3d library using a 3d primitive sphere.
* Played a song in the background to implement the sound library.


## April 12, 2019

* Today I implemented a simple song and 3d spinning object into my example project to get it working for the code review. I also recently changed my proposal because the garbage collector idea was way too complicated and did not seem interesting. Therefore, I am making an application that will play songs, and show the location of the country on a globe (the country where the song is from). This idea seemedmore interesting to me and could potentially be more fun.

## April 15, 2019

* Today I began my search for an api that would would provide songs to play (by country) that would play in the background. However, after looking at countless API's it would not only be difficult to play music by random countries, but also simply difficult to know what country it is from. Depending on what my moderator thinks, I think it would be best if I manually chose songs from the 7 continents to play. Still with the same functionality.
* After researching how to display an image onto a sphere, I found that I needed to use the OF texture library, given a jpg image of the earth. This will make sure that the outer layer of the sphere is an earth.
* Next I plan on learning and executing exactly how I should be able to use the texture class to place the image onto the sphere.

## April 16, 2019

*  Using OF 3d primitives and texture library, I was able to finally able to display a globe on the GUI.
* I am currently suck on how to enlarge the image of the globe because it is currently very small.
* Implementing a USA national mp3 file.
* I started getting errors when I would add lighting to the sphere. Therefore, I found that implementing no lighting appropriately lights the image so that it is visible and no longer needs to be worried about.
* My next problem was uploading a mp3 file along with the jpg of the earth both inside the data folder. I am confused on why this would throw an error if they dont have the same file path.
* After experimenting with Openframeworks library, I am still getting this error and am extremely frustrated. I used the same code that I made in my example for my last code review and it is not working for some reason.
* The problem I have with the mp3 player is that the existence of other files in the data folder make it impossible to read the files. The code compiles and the GUI runs, but it simply does not play the mp3 file that I call in the setup method.
* Added a feature so that the sphere spins along the y axis, making all of the globe visible.
* I am still unable to implement the music, and need to talk to my moderator about how to fix this. The only difference in code between this project and my example project is that there are other files in the data folder. Which is an issue I am unsure on how to resolve.
* I get a bad_ACCESS_ERROR when I change the rotation float to ann odd decimal. This is another problem that is not properly explained by the OF.

## April 17th, 2019

* After creating a different project space, and placing the code for my global music app in it, I found that the problem was actually with the project space created for my music project. This means that I will have to implement my code into a new project space and put this project in the git.

* Today I am focusing on setting the background of the UI to be stars, as if it were in a galaxy. They problem is that I am unsure on how to set a 2d image as the background of a 3d space. 
* I was finally able to figure it out. In order to set an image in the background I first disable the gL library depth, and then draw the image, and then enable the depth again in my draw method (All of which needs to be done before the sphere is drawn.)

* Next I am focusing on exactly how I am going to be able stop rotating the globe and point to the country that I want to.

* To do so, I have to use the setOrientation method for 3d primitive spheres, and ofQuaternion, which is essentially a 4d vector. I found the following OF forum for documentation help. https://forum.openframeworks.cc/t/sphere-orientation/20841

* There seems to be an issue with ofQuaternion, because rather than setting the sphere to a specific place it is simply changing the structure of the 3d globe.

* Instead, I think I am going to create an instance of a 3d vector and use that to call the lookAt method and have it point to that for each country. I am currently having trouble figuring out how these 3d refrences work in terms of getting them to point at a specific spot on the globe.

* I also need to resolve the issue with my project space, because currently all my code is in my emptyExample project, which was created by the OF.


## April 19, 2019

* I think the issue with my original projectspace was that there were problems with the data fold (it simply did not exist.). So to resolve the issue I created an instane of the data folder, and this seemed to work for the jpg images that I placed in there when I ran the program. The sphere was able to render the jpg image of the earth onto its outer layer, but the problem was when I tried playing mp3 files in the data folder. I am not sure why problem was resolved when I copied my code into a different project space, but it did work. Therefore, I am going to place the code that I wrote on the emptyExample ofApp.cpp into my git for grading.

* I am continuing my search for music API's , and If I am unable to find one, I am going to need to speak with my moderator about the best possible solution.

* After looking at different API's I think what would be more realistic is for me to play one song the entier time. However, I would instead be able to get a random song title, Display it on the UI, and then get the country that it is from, or even continent if all that is too dificult.

* The api that I think would be useful is the https://www.musixmatch.com/ api. Now I need to read documentation on how  to make api calls using c++. Maybe I can use GSON's library again.

## April 24th, 2019

* Today I have come to the conclusion that using an API to download songs from different countries is not practical for this project for multiple reasons. This includes the fact that it is hard to find an API that gives music in MP3 files, which is the only way the OF sound library will work with it, and the fact that API's dont have the copyrights to a lot of songs so this is going to be more difficult than expected.
* Therefore, my focus today was work on downloading mp3 files of national anthems for countries.
* Downloaded 10+ national anthem mp3 files into the data folder.
* All these mp3 files have the same file name structure, with their name having the first letter capitalized and the rest is just .mp3
* Worked on placing the names of the countries into a string vector, for the user to see what country's song is playing currently.
* In addition, there is going to be a key and im going to allow the users to see what country it is and simply display it on the UI.
* Eventually, I am going to want to make it so that when the user asks for the answer, it will display the name of the country on the key and the board.
* One slight problem I am coming across is trying to map the node sight to the actual proper country. I have a suspicion that I will also need to be able to do this manually in the ofApp cpp file.


## April 25th, 2019
* Today I focused on the UI aspect of the app by adding a key for users to know what keys to press when playing a random song.
* Used wasd characters for the user key interface display
* One key plays a random song from the data folder
* one key displays the country that the random song is from
* Two keys will either stop the globe from spinning, or make the globe spin and stopping the music.
* What I essentially am doing is to have the user to take a guess as to what the country in the 
* In addition, I am focusing on how to map the sight of the node. I am currently looking at the node class to figure out how to set a specific viewpoint to a country
* I Think it would be easier if I used the ofEasyCam class.
* Currently reading through OfCamera classes to see if there is any way that I can use it to change the view of the globe.
* As of now, I believe I have saved the hardest part of the project for last, and it is ultimately a matter of truly understanding how the node and cam class work, and how I can use that to point to a specific point on the globe.

## April 28th, 2019
* Today I added a feature in the ofAPP cpp file that ultimately elimantes the issue with the camera offsetting rotation because the camera is independent of the ofNode primitive inheretence of the sphere. What happens is that when the user changes the view of the camera in the 3d space by clicking on the mouse, they will be able to view parts of the globe, but it will reset to the position that they were initially at before in the rotation of  the equator.

* I fixed the problem of setting the sphere to a secific orientation. First I ignored mouse clicking that affects camera rotation by reseting the camera position when the mouse click is released. This way the user can still view the entire globe using the mouse to rotate the camera, but not changing its position in the long run.

* Now that the camera position remains relatively constant, I am able to rotate the sphere, depending on where the position of the country is, ofNode class roll, and tilt methods, without being bothered by camera position. I reset the position of the globe to a specific point before the rotation and tilt methods, so that I can call these methods for multiple countries at the same time.

* Added a feature to display the name of the country on the globe as well


## April 29th, 2019

* Today I focused on creating a text file with all the names of the mp3 files that correspond to country name.
* This used a ifstream to read the text file line by line
* For every line that wasnt empty I created an instance of a Country class
* Then I added that country to a vector of countries and randomly got a country name to load a random mp3 file.
* Every instance of country will contain a name, and a tild_x/pan/roll value to point to a specific point on the globe.
* Next, I am creating a text file that will add the corresponding tilt pan and roll values to countries so that the globe will properly point to a specific region close to where the country is.
* Before I create the new text file, I am going to focus on properly moving the git repository to my project. I talked to my moderator about this and he said that the error was odd, but the issue will be resolved if I simply remove the repository and md files to the proper project space. The project space on git does not properly read the data in the bin's data folder.

* Later today, I used key commands and print statements to figure out the pan tilt and roll int values that offset from the origin. Now I am going to focus on mapping those values to the country objects.

* Today I made a lot fo progress. I used the two text files to map the rotation to specific countries, by creating a vector of vector of ints for rotations ,and setting the rotations of each world as to the values of the vector inside the element of the first vector. Now, When I add more countries and rotation values, this will absolutely work. Tomorrow I am going to focus on testing.

* Added a toggle axis display key for user functionality.

## April 30th, 2019

* Today I added a test folder with a catch file and a cpp file to test the ofApp helper functions.

* I am going to focus on adding more counties and test cases.

* Finally added more test cases for all helper functions.

* Now I am going to add more countries.
* In total I have more than 20 countries to choose from random.
* Added more functionality with keys allowing user to draw wire frame and normal lines.
* Implemented a last country variable that avoid playing the same song twice.


## May 1st, 2019
* Today I added more functionality by letting the user guess what country the song is playing from, and then count their total score.
* I also changed the key box by making the functions numbers instead of letters so that the user can type.

* Added more to ui so that it tells user if they are correct or not.

* Avoided the user constantly pressing four to avoid cheating.

* Cleaned up code and added more comments
