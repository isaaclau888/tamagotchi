# Falloutgotchi (Tamagotchi)
<img width="1920" height="1080" alt="Case_2026-Jun-07_06-28-46PM-000_CustomizedView33723155341_png" src="https://github.com/user-attachments/assets/ca0e2879-1739-46af-a073-22bd3a34fa03" />

Hi, this is a Tamagotchi project that I built with T-QT Pro and a LiPo Battery.
This is an easy project, but coding wasted a lot of time lol. 

If you ask me what a Tamagotchi is, I will tell you that it is just a pet living in a device that you need to take care of.
This is a completely open-source project. All the 3D parts and the BOM list are put in the folders. You may customise my project. 

## What's it for?
It's for you to take care of it and act like a pet owner. You can take it to school, home or even at work, wherever you like.

## How to build it?
Please print all the 3D parts. Also, connect the T-QT Pro to a battery. Then place the bottom case, put the bottom button part and the T-QT Pro, which is connected to the battery, inside. Afterwards, just put the top buttons inside the top case. Finally, combine both of them, and you can use it already.

## How can you use it?
1. Please download and install Arduino IDE from the official Arduino website.
2. Install ESP32 Board in Arduino IDE:
Open Arduino IDE and go to File > Preferences.
In the Additional Boards Manager URLs field, add the following URL:
https://dl.espressif.com/dl/package_esp32_index.json
Go to Tools > Board > Boards Manager, search for "ESP32", and click Install.
4. Open Library Manager(A stack of books on the left sidebar)
Search and install LovyanGFX
5. Select Your Board and Port:
After installing, select the LILYGO T-QT Pro ESP32-S3 board: Tools > Board > ESP32 Dev Module
Select the correct Port under Tools > Port.
5. Upload Code:
Write or load Tamagotchi_Game in the Arduino IDE.
Click the Upload button. After a few seconds, your code will be uploaded to the board.
6. And now you can use it, yay!!!

## Why did I make it?
I decided to make this because I want to try making one by myself. I would like to have a custom version of Tamagotchi and have a different game type. I have solved some problems, like the battery part. 

## How do you play the game?
Left button: The care button
Tap this to feed your pet a cup of coffee to replenish its hunger.
If your pet passes away, holding this button down for 2 full seconds acts as a reviver to restart the game.

Right button: The mode switch
Short Click: Toggles the Heads-Up Display on and off if you want a clean view of your pet's room.
Long Press(Hold for 1 second): Puts your pet to sleep or wakes it up.

The Stat Bar: It is located at the top of the screen. A full green bar means your pet is perfectly full. The bar will drain as time passes. It turns Yellow when stats are dropping, and flashes Red when it is below 30%.
Environment: You can see your custom care items like the poop or medicine layers; it appears directly in the room context over the background wallpaper.

4 Life States:
State 1: Sleeping
The pet is tucked under the sheets, breathing softly in a slow, 4-frame loop. Your pet enters this state when you long-press the RIGHT button.
When it is sleeping, its energy will recharge, and its hunger drops incredibly slowly. You cannot feed it coffee while it is asleep. Long-press the right button to wake it up.

State 2: Walking
Your pet is awake, walking around. This is the ideal state! It means your pet is healthy and its hunger bar is above 30%

State 3: Hungry
The health bar flashes Red; your pet waves its fork and spoon up and down.
When hunger drops below 30%, you must act fast. Just press the LEFT button to give it coffee. It will switch to the drinking animation before returning to the walking animation.

State 4: Game Over (RIP)
The whole thing vanishes completely, and the screen turns black, with a blinking "RIP" message that flashes alongside the text "Hold L to Reset".
If you let the hunger stat stay at 0% for more than 15 seconds, it dies. To start over with a fresh new pet, hold down that LEFT button for 2 seconds.

## How I made it?
I used Fusion 360 to make the case and buttons, Arduino IDE for the code part and last but not least, the T-QT Pro and the LiPo battery.

# Fallout Zine 
<img width="4405" height="6250" alt="Falloutgotchi (Tamagotchi) Fallout Zine" src="https://github.com/user-attachments/assets/d22b2e28-816f-446f-8513-b3beed760f0a" />
