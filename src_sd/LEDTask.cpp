
#include <kinetis.h>

#include <FreeRTOS.h>
#include <task.h>

#include <Arduino.h>

int ledPin = 13;

/** calibration factor for delayMS */
#define CAL_FACTOR (F_CPU/6007)
/** delay between led error flashes
 * \param[in] millis milliseconds to delay
 */

void LEDTask(void* args) {
  pinMode(ledPin, OUTPUT);

  int delay1 = 500 / portTICK_PERIOD_MS;

  for(;;){
    digitalWrite(ledPin, LOW);
    vTaskDelay(delay1);
    digitalWrite(ledPin, HIGH);
    vTaskDelay(delay1);
  }
}

