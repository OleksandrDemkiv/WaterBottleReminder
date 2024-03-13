# Water bottle reminder

This is a simple reminder to drink water regularly with a lot of functions for better user experience.

## Required components

 -	Arduino Yún / Uno
 -	Grove -- Base Shield (https://wiki.seeedstudio.com/Base_Shield_V2/)
 -	Grove -- LCD RGB Backlight (https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/)
 -	Grove -- Dual Button (https://wiki.seeedstudio.com/Grove-Dual-Button/)
 -	Adafruit -- Load Cell (This is 20kg, you can choose any one you want) (https://www.adafruit.com/product/4543)
 -	SparkFun -- HX711 Load Cell Amplifier (https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all)

## Files

In this branch you can find only .ino files, which will be just taken as one file in Arduino IDE when uploading. The only thing you need is to add required libraries.
*this is why there is file named "songz", it's just to have it compiled in proper way.

## Required libraries 

 - Grove -- LCD RGB Backlight (https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/)
 - HX711 Arduino Library (https://github.com/bogde/HX711)
 - Pitches.h (https://gist.github.com/mikeputnam/2820675)
 - MillisDelay (https://github.com/ansonhe97/millisDelay)


# Usage

## Main functions

 - Recording every intake of water:
	 - Displays data in ml for last intake;
	 - Stores all of the data (how much you drank every time);
	 ---
- Timer with alarm:
	- Rings each period of time to remind you to drink water;
	- Period and alarm sound are set in menu mode;
	 ---
 - Sleep mode
	 - Turns of the screen to save energy consumption;
	 - Timer stays on to remind on time;
	 ---
 - Menu mode
	 - Allows you to customize all of the program (background color, alarm sound, etc.);

## Startup

At the startup the program will as you to clean the platform and then put weight on it to start working.

## Main screen usage

- To drink water you simply lift the bottle and drink the water, when you are done, put the bottle back on the platform and press *red button*.
- To put the system to a sleep mode press *blue button*.
- To go to menu, press *red button* and *blue button* at the same time.

## Sleep mode

- Press *blue button* to enter it.
- To exit:
	- press *either of the buttons*;
	- lift up the bottle (in this case it will prompt you to press *red button* when you have finished drinking process);
	- if timer goes on, sleep mode turns of automatically;

## Menu mode

- Press *two buttons* together to enter it.
- The options are: Timer setup,  Do not disturb,  Change song,  Change color.
- To navigate: use *blue button* to go to next option, or use *red button* to choose an option.
- To exit press *two buttons* at the same time.

## Menu mode options and navigation

- Timer setup
	- Use *blue button* to add 30 minutes;
	- Use *red button* to minus 30 minutes;
	- Use *two buttons* to exit and save the result;
	**Note** if you have entered zero, timer time will stay the same as it was;
---
- Do not disturb
	- Use *blue button* to change between on and off;
	- Use *red button* to save and exit;
---
- Change song
	- Use *blue button* to navigate between sections;
	- Use *red button* to choose a section;
	- Use *two buttons* to exit;

- In section menu
	- Use *blue button* to navigate between songs;
	- Use *red button* to choose a song;

---

- Change color
	- Use *blue button* to navigate between colors;
	- Use *red button* to choose a color;
