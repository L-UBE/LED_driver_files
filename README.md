# LED_driver_files


Main stuff to care about. 

ioc file: lines out a lot of changes from the original PCB design. turned off a lot of pins and made them GND for twisted pair wirings. 

PL9823.h: initial version of the LED driver. you can see a lot of small modifications over time, in the order of how the functions are defined. 

PL9823_v2.h: the second version of the LED driver. So far there are going to be three main functions 

- PL9823_Presetinit(): 
This function calculates all the colors preset values into the format that DMA likes. Preset colors can be changed from COLORS. There are 16 colors good to be set. 

- PL9823_sendchannel():
This function will take in a array, and send it to the directed channel. Most likely it wouldn't be used, but in case we still need to use this functionality, I still kept it as a reference. This can take in all kind of color values, but calculates them on the run. 

- PL9823_sendchannelPreset():
This function will take in a byte array, with each byte containing color values for two LEDs. This will be parsed into two LEDs, and the entire DMA transfer data will be set by using memcpy efficiently. 


PL9823_v3.h: the third version of the LED driver. Delay was significantly reduced, and parallel sending is available. Speed is increased by 2x. 
- Implemented brightness control for colors. 


Pl9823_v4.h: the forth version of the LED driver. Still testing. Not sure if will work.
