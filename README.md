# Morse Code Communicator

Author: Jeremy Shaffar
Class: CS 126

## Rational
While computers have tremedously evolved in terms of secure communication, and increasingly complex algorithms have been developed in order to encrypt sensitive and nonsensitive communication, almost no form of communication is completely secure. Provided you don't have/want an internet connection, and don't have a microphone or need for a text to speech program, this program provides an extremily simple way in order to transfer files or communicate between two eligible computers.

## Description
This program attempts to simulate morse code, or any other code that is provided, in a similiar way to help to computers communicate without a network. Computer A will read a document or user input (computer will decide whether input is a file path), and convert that text into morse code. Computer A will then play a note when speaking and stop when not. Morse code is dettermined exclusively by dots and dashes, as well as space between both letters and words of different lengths, and you can customize them in the source code (although they must be set for the same length on each computer, and the default is prefered, as it has the highest accuracy). Computer B will pick up on the changing in sound of Computer A, through the help of the cinder audio elements and its own microphone specifically the timespan in which the sound changes. It will then convert these morse code timestamps back into a file at the perscribed path that the user would like. 

## Background
I find the concept of computer security very interesting, although I haven't really studied it I always wanted to look into it more. Although Morse Code isn't a particualarly secure or effective mode of communication, it can easily be extended into more sophisticated forms of communications, albeit it might heavily slow down. Eventually I want to learn enough about encryption to implmenent more sophisticated codes. 

## Dependencies
Currently only tested on windows with vs2015
### Libraries
- Cinder
- https://github.com/nlohmann/json
- catch2 for testing

## Extensions and Adjustments
This program can also be extended to more sophisticated codes, that extend from code.h, the only condition being that they rely on timestamps and sound. To improve the accuracy, the microphone sensitivity and timestamp values can be editted, both values in constants.h.
