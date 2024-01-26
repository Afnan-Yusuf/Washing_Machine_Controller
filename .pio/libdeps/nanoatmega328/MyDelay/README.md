# MyDelay Library #

This library is designed to simplfy using the builtin Arduino mills function without all the setup.

## About this Library ##

To start create a MyDelay variable. From here you are able to set a delay time, a delay time, a
function to run and a repeat count or nothing at all.

To check it if the delay time has past, call the update function which will check time and 
run the set function.

Using the start function, you are able to restart the timer for delay. The stop function will terminate a timer 
before the repeat count has been reached.  This allows you more
control over when and how often a delay with trigger.

The delay time can be change using setDelay using a time in miliseconds. 

Written by Marshall G Gates
MIT license, check license.md for more information

Based on noDelay library by Mario Avenoso of [mtechcreations.com](http://mario.mtechcreations.com/programing/nodelay-arduino-library/)


