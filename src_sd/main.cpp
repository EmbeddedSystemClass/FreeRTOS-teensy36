#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <IntervalTimer.h>

// extern tasks declared elsewhere in program
void LEDTask(void* args);
void SerialTask(void* args);
void BufTask(void* args);
void SensorTask();

IntervalTimer myTimer;

int main() {
  // create the tasks
  xTaskCreate(LEDTask, "LT", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(SerialTask, "ST", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  //xTaskCreate(SerialTask, "ST", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(BufTask, "ST", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//  xTaskCreate(SensorTask, "pT", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  myTimer.begin(SensorTask, 1000);
  // start scheduler, main should stop functioning here
  vTaskStartScheduler();

  for(;;);

  return 0;
}

