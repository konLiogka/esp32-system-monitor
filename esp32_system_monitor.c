#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include "bitmaps.h"

#define EPD_CS 		10
#define EPD_DC 		4
#define EPD_RST		5
#define EPD_BUSY    3
#define SPI_SCK 	6
#define SPI_MOSI 	7

uint8_t frame = 0;
char 	timeStr[16], cpuStr[16], ramStr[16];
char					buffer[64];
unsigned long lastUpdate = 0;
uint8_t 			hasSerialData = 0x00;


GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(
  GxEPD2_154_D67(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

void 
parseSerialData() {
	do {
		int len = Serial.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
		if (len <= 0) 		
		{
			hasSerialData = 0x00;
			return;
		} 

		buffer[len] = '\0';

		char *t = strtok(buffer, ",");
		char *c = strtok(NULL, ",");
		char *r = strtok(NULL, ",");

		if (!t || !c || !r)
		{
			hasSerialData = 0x00;
			return;
		} 

		strcpy(timeStr, t);
		strcpy(cpuStr, c);
		strcpy(ramStr, r);
		hasSerialData = 0x01;
	} while(Serial.available());
}

void 
setup() {
	Serial.begin(115200);
	Serial.setTimeout(100);

	SPI.begin(SPI_SCK, -1, SPI_MOSI, EPD_CS);

	display.init(115200);
	display.setRotation(0);
	display.setTextColor(GxEPD_BLACK);
}

void 
loop() {
  parseSerialData();

  if (millis() - lastUpdate < 2000) return;
  lastUpdate = millis();

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, bitmap + (frame * 5000), 200, 200, GxEPD_BLACK);

    if (hasSerialData == 0x01) {
      display.setFont(&FreeMonoBold24pt7b);
      display.setCursor(25, 32);
      display.print(timeStr);

      display.setFont(&FreeSansBold12pt7b);

      display.drawBitmap(0, 160, cpuIcon, 40, 40, GxEPD_BLACK);
      display.setCursor(43, 185);
      display.print(cpuStr);
      display.print("%");

      display.setCursor(115, 185);
      display.print(ramStr);
      display.print("%");
      display.drawBitmap(165, 155, ramIcon, 40, 40, GxEPD_BLACK);
    }

  } while (display.nextPage());

  frame++;
  if (frame >= BITMAPS) frame = 0;
	delay(3000);
}

