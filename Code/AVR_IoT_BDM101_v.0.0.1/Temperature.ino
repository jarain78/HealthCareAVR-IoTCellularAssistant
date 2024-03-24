

/*void initMLX90640() {
  delay(100);

  Serial3.println("Adafruit MLX90640 Simple Test");
  
  if (! mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire1)) {
    Serial3.println("MLX90640 not found!");
    while (1) delay(10);
  }
  Serial3.println("Found Adafruit MLX90640");

  Serial3.print("Serial number: ");
  Serial3.print(mlx.serialNumber[0], HEX);
  Serial3.print(mlx.serialNumber[1], HEX);
  Serial3.println(mlx.serialNumber[2], HEX);

  //mlx.setMode(MLX90640_INTERLEAVED);
  mlx.setMode(MLX90640_CHESS);
  Serial3.print("Current mode: ");
  if (mlx.getMode() == MLX90640_CHESS) {
    Serial3.println("Chess");
  } else {
    Serial3.println("Interleave");
  }

  mlx.setResolution(MLX90640_ADC_18BIT);
  Serial3.print("Current resolution: ");
  mlx90640_resolution_t res = mlx.getResolution();
  switch (res) {
    case MLX90640_ADC_16BIT: Serial3.println("16 bit"); break;
    case MLX90640_ADC_17BIT: Serial3.println("17 bit"); break;
    case MLX90640_ADC_18BIT: Serial3.println("18 bit"); break;
    case MLX90640_ADC_19BIT: Serial3.println("19 bit"); break;
  }

  mlx.setRefreshRate(MLX90640_2_HZ);
  Serial3.print("Current frame rate: ");
  mlx90640_refreshrate_t rate = mlx.getRefreshRate();
  switch (rate) {
    case MLX90640_0_5_HZ: Serial3.println("0.5 Hz"); break;
    case MLX90640_1_HZ: Serial3.println("1 Hz"); break;
    case MLX90640_2_HZ: Serial3.println("2 Hz"); break;
    case MLX90640_4_HZ: Serial3.println("4 Hz"); break;
    case MLX90640_8_HZ: Serial3.println("8 Hz"); break;
    case MLX90640_16_HZ: Serial3.println("16 Hz"); break;
    case MLX90640_32_HZ: Serial3.println("32 Hz"); break;
    case MLX90640_64_HZ: Serial3.println("64 Hz"); break;
  }
}

void readMLX90640() {
  
  delay(500);
  if (mlx.getFrame(frame) != 0) {
    Serial3.println("Failed");
    return;
  }
  Serial3.println();
  Serial3.println();
  for (uint8_t h = 0; h < 24; h++) {
    for (uint8_t w = 0; w < 32; w++) {
      float t = frame[h * 32 + w];
#ifdef PRINT_TEMPERATURES
      Serial3.print(t, 1);
      Serial3.print(", ");
#endif
#ifdef PRINT_ASCIIART
      char c = '&';
      if (t < 20) c = ' ';
      else if (t < 23) c = '.';
      else if (t < 25) c = '-';
      else if (t < 27) c = '*';
      else if (t < 29) c = '+';
      else if (t < 31) c = 'x';
      else if (t < 33) c = '%';
      else if (t < 35) c = '#';
      else if (t < 37) c = 'X';
      Serial3.print(c);
#endif
    }
    Serial3.println();
  }
}*/
