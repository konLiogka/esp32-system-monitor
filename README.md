# esp32-system-monitor
Simple ESP32 project and tutorial for using an epaper display as a tiny system monitor

![20260103_163943](https://github.com/user-attachments/assets/c6780582-9e2b-4ee7-ae7f-fbb6a8403bcf)
![20260103_163941](https://github.com/user-attachments/assets/7cc3209e-dd9f-4e3a-9f5f-d54b46e2de5d)


**COMPATIBLE WITH LINUX (BASH)**
I've developed the script for sending data over serial in bash. Use your own implementation for Windows shell.

The epaper display shows the preloaded bitmap images, day time, CPU and RAM info. If the bash script isnt sending anything it just shows the bitmap images.

For ease of use, I've chosen using a serial interface for powering on the esp32 and display AND sending the data over serial communication.

The bitmap images were generated using image2cpp (https://jlamch.net/MXChipWelcome/).

## Implementation

**Hardware:**
- ESP32 C3 super mini
- WeAct 1.54" BW e-paper display (SSD1681)

**Software:**
- Arduino IDE with Adafruit BusIO, Adafruit GFX Library and GxEPD2 libraries installed

**3D print file for the Macintosh case:**
https://www.printables.com/model/1539894-esp32-154-epaper-display-mini-macintosh-case


## System Setup

- Give permission to the script.
```bash
chmod +x ./esp32_system_monitor.sh
```
- Make the bash script run when a user logs in. Different depending on X or Wayland.

## Arduino IDE

- Copy the c code inside the .ino file
- Copy the bitmaps.h file inside the sketch folder (same folder as the .ino file)
- Install the required libraries for the esp32
- Go to Tools > Board > esp32 and select ESP32C3 DEV MODULE
- Build & upload to the esp32



