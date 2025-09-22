# Native Mc-Tiers

This is a native desktop app for Windows that lets you see what tier a player is

so far its very barebones but later on I will add more to this =D


# How to build

make sure you have visual studios (espeically desktop C++ development) installed

you don't need VS itself, but you do need MSVC to compile this

when you have that installed, also make sure you have xmake installed

open the x64 native command prompt for VS(whatever version you have installed), or anywhere where msvc is located at

when that happens, clone this repository and run `run.bat`, and if everything is correct it should build


# Libraries used to make this


[Naett](https://github.com/erkkah/naett) (for HTTP)

[Raylib](https://www.raylib.com/) (for Windowing and Drawing)

[RayGUI](https://github.com/raysan5/raygui) (for making a decent GUI in Raylib)

[cJSON](https://github.com/DaveGamble/cJSON) (for JSON parsing)


# In the future

My goal is to make the UI less barebones and more feature-filled

I also want in the future to make a Linux/MacOS port, even though that won't be easy =D