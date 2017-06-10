#include <FreeRTOS.h>
#include <task.h>

#include <Arduino.h>
#include <usb_dev.h>

#include <SD.h>
#include <SPI.h>

const int chipSelect = BUILTIN_SDCARD;

volatile int sensor;
volatile bool lol=0;
//volatile int count=0;
String dataString = "";

#define Serial Serial1

void SerialTask(void* args) {

	if (!SD.begin(chipSelect)) {
		return;
	}

	while(1) {

		File dataFile = SD.open("datalolg.txt", FILE_WRITE);
		
		if (dataFile) {
			dataFile.println(dataString);
			dataFile.close();
		}
		else {
			return;
		}
//		count=0;
		dataString = "";
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}

}

void BufTask(void* args) {
	while(1) {
		dataString += (xTaskGetTickCount());
		dataString += "\t";
		dataString += String(sensor);
		dataString += "\n";
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

void SensorTask() {

	cli();
	sensor = analogRead(1);
//	count++;
	sei();

}
