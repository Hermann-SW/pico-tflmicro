#include <stdio.h>
#include "pico/stdlib.h"
#include "LCD_st7735.h"


#define TfLiteStatus int
class tflite { public: class ErrorReporter { public: }; };
#define TF_LITE_REPORT_ERROR(er, str)  printf(str);
#define kTfLiteError -1
#define kTfLiteOk 0

#include "../magic_wand_ble/imu_provider.h"


int main(int argc, char *argv[]) {
  stdio_init_all();

  ST7735_Init();
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
  sleep_ms(2000);

  ST7735_FillRectangle(0, 137, 80, 22, ST7735_RED);

  ST7735_WriteString(5, 138, "IMU device", Font_7x10, ST7735_WHITE, ST7735_BLUE);

  SetupIMU(NULL);

  ST7735_WriteString(5, 149, 
    (DeviceWho == ICM42622_DEVICE) ? "ICM42622" : "ICM20948",
                     Font_7x10,  ST7735_WHITE, ST7735_BLUE);
}
