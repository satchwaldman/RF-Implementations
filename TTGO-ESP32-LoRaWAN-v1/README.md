# TTGO ESP32 

INTERFACING INSTRUCTIONS:
1. Setup PlatformIO for VSCode, following the instruction [here](https://www.youtube.com/watch?v=JmvMvIphMnY). Though this is a bit of a long video, I recommend watching it in its entirely tp fully understand the nuance of PlatformIO.
2. Once PlatformIO is set up, navigate to to desired location for the repository and clone the Github repository as usual. Board information for the Sparkfun Pro RF is included in the repository.
3. Once the repository is cloned, open it in VSCode. After a few seconds, VSCode should automatically add two folders: .pio and .vscode. We will leave the .vscode folder alone but we must make changes to the .pio folder to include the library dependencies.
4. At this stage, the .pio folder should contain a folder called build, which in turn contains a folder called ttgo-lora32-v21 as well as a project.checksum file.
5. Add a folder called libdeps to the .pio folder.
6. Within the libdeps folder, add another folder called ttgo-lora32-v21.
7. Within this new ttgo-lora32-v21 folder, we will add both the libraries itself and an integrity.dat file. 
8. The library dependencies are found in the lib folder. Simply drag each library dependency into the aforementioned build>libdeps>ttgo-lora32-v21 folder.
10. That's it! Any files in src that had undefined called to header files should now be resolved.
