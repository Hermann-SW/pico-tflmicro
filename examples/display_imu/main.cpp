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

  if (DeviceWho == ICM20948_DEVICE)
  {
    ST7735_FillRectangle(0, 0, 25, 137, ST7735_BLACK);
    ST7735_FillRectangle(0, 55, 80, 82, ST7735_BLACK);

    int r=45;
    int x0=30;
    int y0=120;
    int L=3;
    int o=90;

    for(int d=0; d<=120; ++d)
    {
      for(int l=(d%15==0)?-L:0; l<=(d%15==0)?L+1:0; ++l)
      {
        int x = x0+(r+l)*cos(d/180.0*M_PI);
        int y = y0-(r+l)*sin(d/180.0*M_PI);
        ST7735_DrawPixel(x, y, ST7735_WHITE);
      }
    }

    while (1)
    {
      IMU_ST_ANGLES_DATA an;
      IMU_ST_SENSOR_DATA gy, ac, ma;
      ICM20948::imuDataGet(&an, &gy, &ac, &ma);
      for(int l=0; l<=r-9; ++l)
      {
        int x = x0+l*cos(o/180.0*M_PI);
        int y = y0-l*sin(o/180.0*M_PI);
        ST7735_DrawPixel(x, y, ST7735_BLACK);
      }
      o = an.fRoll;
      for(int l=0; l<=r-9; ++l)
      {
        int x = x0+l*cos(o/180.0*M_PI);
        int y = y0-l*sin(o/180.0*M_PI);
        ST7735_DrawPixel(x, y, ST7735_WHITE);
      }
      sleep_ms(2);
    }
  }
}
