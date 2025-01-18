#pragma once
#include "globals.h"
#include <cstring>

//converts degrees to radians
double rad(double deg){
    return deg * pi / 180.0;
}

void debug_value(double value){

    std::string str = std::to_string(value);

    // Create a character array large enough to hold the string
    char charArray[100]; // Make sure it's large enough for the string and null terminator
		
    // Copy the string into the character array
    std::strcpy(charArray, str.c_str());
		
	pros::lcd::set_text(1, charArray);
}

void debug_value(int value){

    std::string str = std::to_string(value);

    // Create a character array large enough to hold the string
    char charArray[100]; // Make sure it's large enough for the string and null terminator
		
    // Copy the string into the character array
    std::strcpy(charArray, str.c_str());
		
	pros::lcd::set_text(1, charArray);
}

void debug_value_with_text(const std::string& text, double value) {
    // Convert the value to a string
    std::string valueStr = std::to_string(value);

    // Concatenate the custom text with the value
    std::string combinedStr = text + ": " + valueStr;

    // Create a character array large enough to hold the combined string
    char charArray[100]; // Ensure it's large enough for the string and null terminator

    // Copy the combined string into the character array
    std::strcpy(charArray, combinedStr.c_str());

    // Display the text on the LCD
    pros::lcd::set_text(1, charArray);
}

void debug_value_with_text(const std::string& text, int value) {
    // Convert the value to a string
    std::string valueStr = std::to_string(value);

    // Concatenate the custom text with the value
    std::string combinedStr = text + ": " + valueStr;

    // Create a character array large enough to hold the combined string
    char charArray[100]; // Ensure it's large enough for the string and null terminator

    // Copy the combined string into the character array
    std::strcpy(charArray, combinedStr.c_str());

    // Display the text on the LCD
    pros::lcd::set_text(1, charArray);
}
