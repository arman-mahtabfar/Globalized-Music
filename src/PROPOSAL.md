## Arman Mahtabfar
## Professor Carl G. Evans
## CS 126: Software Design Studio
## 04/06/2019
# Final Project Proposal

As someone whose first exposure to software development was through the object oriented programming language known as Java, my concept of memory and memory allocation was minimal. Due to Java’s garbage collector that is automatically executed during runtime, there was no need for understanding memory allocation. In hopes of helping myself learn and understand more about memory allocation, I was hoping to implement a library that acts as a garbage collector, similar to Java. 

However, After trying to use the Boehm Garbage Collector, a complicated, and confusing external library with little documentation, I found that this project would be way too complicated and boring with little to do on the GUI end, because it would be difficulte to model how memory is allocated into certain spaces. Therefore, I am deciding to change my project, and create an UI where the user can go through a library of songs, completely at random, and then show a model of the world, and hopefully be able to point where in the world that song is from. So everytime they choose a new song, the pointer will point to a different position on that globe.

So, there are two libraries that I am going to implement into my project. The first is going to be the sound library. This library will be able to take a bunch of song files in the data folder, along with the country to which the songs belong, and play that song while the app is running. In my gui, I will show the name and country of the song. Features like being able to skip or pause songs will also be added. 

However, one of my main concerns is exactly how I am going to be able to get the song data? Should this be from an API? Should I find songs for several countries that I like and manually input them into the data folder along with their country name? This is hopefully what we can discuss in code review. 

The next library that I will be using is the 3d library. This is going to be used to create a physical globe of the world. My goal is to place an image represing the map of the world, onto the 3dprimitive sphere. This globe will rotate freely until songs are played.

Lastly, there are a few challenges using the 3d library for the globe: My main concern is how I am going to map countries with points on the globe? Can this be done through assigning country names to (lattitude,longitude) points on the shell of the sphere? How can I do this for all countries? How can I change where the gui points to on the globe? I will not only need to learn how to map the picture of the globe onto the sphere, but also how set coordinates on the map to coordinates of the shell.

