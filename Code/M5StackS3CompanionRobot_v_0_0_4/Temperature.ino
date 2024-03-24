
void initMLX90640() {
  // Get device parameters - We only have to do this once.
  // 获取设备参数——我们只需要做一次
  int status;
  uint16_t eeMLX90640[832];  // 32 * 24 = 768
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);
  if (status != 0) Serial.println("Failed to load system parameters");

  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
  if (status != 0) Serial.println("Parameter extraction failed");


  int SetRefreshRate;
  // Setting MLX90640 device at slave address 0x33 to work with 16Hz refresh
  // rate: 设置从地址0x33的MLX90640设备以16Hz刷新率工作:
  // 0x00 – 0.5Hz
  // 0x01 – 1Hz
  // 0x02 – 2Hz
  // 0x03 – 4Hz
  // 0x04 – 8Hz // OK
  // 0x05 – 16Hz // OK
  // 0x06 – 32Hz // Fail
  // 0x07 – 64Hz
  SetRefreshRate = MLX90640_SetRefreshRate(0x33, 0x05);
  // Once params are extracted, we can release eeMLX90640 array.
}


void readTemperature() {
  for (byte x = 0; x < speed_setting; x++)  // x < 2 Read both subpages
  {
    uint16_t mlx90640Frame[834];
    int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);
    if (status < 0) {
      Serial.print("GetFrame Error: ");
      Serial.println(status);
    }

    float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
    float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);
    float tr =
      Ta - TA_SHIFT;  // Reflected temperature based on the sensor ambient
                      // temperature.
    float emissivity = 0.95;
    MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr,
                         pixels);  // save pixels temp to array (pixels).
    int mode_ = MLX90640_GetCurMode(MLX90640_address);
    // amendment.
    MLX90640_BadPixelsCorrection((&mlx90640)->brokenPixels, pixels, mode_, &mlx90640);


    n_data = 0;
    temperature = 0;

     for (int x = 0; x < pixelsArraySize; x++) {
      if (x % COLS == 0)  // 32 values wide.  32宽值
      {
        for (int j = 0 + x, k = (COLS - 1) + x; j < COLS + x;
             j++, k--) {
          temperature = pixels[k] + temperature;
          n_data = n_data + 1;
        }
      }
    }
  }

  temperature = temperature / n_data;
}