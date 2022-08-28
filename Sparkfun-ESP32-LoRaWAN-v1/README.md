# LoRaWAN framework for Sparkfun ESP32 Gateway

LoRaWAN implementation for the RMF95 radio module, specifically on the Sparkfun ESP32 Single-Channel Gateway. In order for this code to work, we must interface it with The Things Network, various library dependencies, and PlatformIO

INTERFACING INSTRUCTIONS:
1. Setup PlatformIO for VSCode, following the instruction [here](https://www.youtube.com/watch?v=JmvMvIphMnY). Though this is a bit of a long video, I recommend watching it in its entirely tp fully understand the nuance of PlatformIO.
2. Once PlatformIO is set up, navigate to to desired location for the repository and clone the Github repository as usual. Board information for the Sparkfun Pro RF is included in the repository.
3. The required library dependencies can be found in the lib folder. These are automatically copied in your code when the repository is cloned.

FLASHING FIRMWARE INSTRUCTIONS:
Since there is no main.cpp file in this repository, simply flash the firmware using the "Platformio: Upload" button at the bottom left of the screen.
