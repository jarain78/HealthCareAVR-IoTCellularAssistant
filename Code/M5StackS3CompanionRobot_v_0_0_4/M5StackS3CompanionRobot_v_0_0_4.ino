// https://github.com/DiegoPaezA/ESP32-freeRTOS/blob/master/Task_FreeRTOS/main.c
#include "Config.h"


void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols, float *dest, uint8_t dest_rows, uint8_t dest_cols);


void setup() {

  auto cfg = M5.config();
  CoreS3.begin(cfg);


  {  /// I2S Custom configurations are available if you desire.
    auto spk_cfg = CoreS3.Speaker.config();

    if (spk_cfg.use_dac || spk_cfg.buzzer) {
      /// Increasing the sample_rate will improve the sound quality
      /// instead of increasing the CPU load.
      spk_cfg.sample_rate =
        192000;  // default:64000 (64kHz)  e.g. 48000 , 50000 , 80000 ,
                 // 96000 , 100000 , 128000 , 144000 , 192000 , 200000
    }
    /*
            spk_cfg.pin_data_out=8;
            spk_cfg.pin_bck=7;
            spk_cfg.pin_ws=10;     // LRCK

            /// use single gpio buzzer, ( need only pin_data_out )
            spk_cfg.buzzer = false;

            /// use DAC speaker, ( need only pin_data_out ) ( only GPIO_NUM_25
        or GPIO_NUM_26 ) spk_cfg.use_dac = false;
            // spk_cfg.dac_zero_level = 64; // for Unit buzzer with DAC.

            /// Volume Multiplier
            spk_cfg.magnification = 16;
        //*/
    CoreS3.Speaker.config(spk_cfg);
  }
  CoreS3.Speaker.begin();
  img.clear();

  //CoreS3.Display.setBrightness(24);
  img.createSprite(CoreS3.Display.width(), CoreS3.Display.height());
  img.fillSprite(BLACK);

  Wire.onReceive(onReceive);
  //Wire.onRequest(onRequest);
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000UL);

  Wire.flush();

  initHR();
  initMLX90640();
  
  //setupBle();
  //setupCamera();

  xTaskCreate(&menu_task, "MENU_TASK", 2 * 1024, NULL, 1, &menuHandler);
  vTaskSuspend(menuHandler);


  xTaskCreate(&eye_task, "EYE_TASK", 2 * 2048, NULL, 2, &eyeHandler);

  xTaskCreate(&temperature_task, "TEMPERATURE_TASK", 2 * 2048, NULL, 3, &temperatureHandler);
  vTaskSuspend(temperatureHandler);

  //xTaskCreate(&camera_task, "CAMERA_TASK", 2 * 2048, NULL, 3, &cameraHandler);
  //vTaskSuspend(cameraHandler);


  //xTaskCreate(&hr_spo2_task, "HR_SPO2_TASK", 1 * 1024, NULL, 3, &hrspo2Handler);
  //vTaskSuspend(hrspo2Handler);



  // Menu
  //xTaskCreate(&ecg_task, "ECG_TASK", 1024, NULL, 3, &ecgHandler);
  //xTaskCreate(&ppg_task, "PPG_TASK", 1024, NULL, 4, &ppgHandler);
  //xTaskCreate(&spo2_task, "SPO2_TASK", 1024, NULL, 5, &spo2Handler);
  //xTaskCreate(&plot_task, "PLOT_TASK", 2 * 1024, NULL, 6, &plotHandler);
  //vTaskSuspend(plotHandler);

  //vTaskSuspend(ecgHandler);
  //vTaskSuspend(ppgHandler);
  //vTaskSuspend(spo2Handler);
}


void loop() {
  //getHR();
  vTaskDelay(1);
}
