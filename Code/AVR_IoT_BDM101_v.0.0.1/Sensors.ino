


void intiAllSensors(void) {

  // Initialize MCP9808 library
  // const int8_t error = Mcp9808.begin(0x18); // Rev1
  const int8_t error = Mcp9808.begin(); // Rev2
  if (error) {
    Serial3.println("Error: could not start MCP9808 library");
  }

  // Initialize LISM3MDL
  // Try to initialize!
  if (! lis3mdl.begin_I2C(LIS3MDL_I2CADDR_DEFAULT, &Wire1)) {          // hardware I2C mode, can pass in address & alt Wire

    Serial3.println("Failed to find LIS3MDL chip");
    while (1) {
      delay(10);
    }
  }
  Serial3.println("LIS3MDL Found!");

  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
  Serial3.print("Performance mode set to: ");
  switch (lis3mdl.getPerformanceMode()) {
    case LIS3MDL_LOWPOWERMODE: Serial3.println("Low"); break;
    case LIS3MDL_MEDIUMMODE: Serial3.println("Medium"); break;
    case LIS3MDL_HIGHMODE: Serial3.println("High"); break;
    case LIS3MDL_ULTRAHIGHMODE: Serial3.println("Ultra-High"); break;
  }

  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  Serial3.print("Operation mode set to: ");
  // Single shot mode will complete conversion and go into power down
  switch (lis3mdl.getOperationMode()) {
    case LIS3MDL_CONTINUOUSMODE: Serial3.println("Continuous"); break;
    case LIS3MDL_SINGLEMODE: Serial3.println("Single mode"); break;
    case LIS3MDL_POWERDOWNMODE: Serial3.println("Power-down"); break;
  }

  lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
  // You can check the datarate by looking at the frequency of the DRDY pin
  Serial3.print("Data rate set to: ");
  switch (lis3mdl.getDataRate()) {
    case LIS3MDL_DATARATE_0_625_HZ: Serial3.println("0.625 Hz"); break;
    case LIS3MDL_DATARATE_1_25_HZ: Serial3.println("1.25 Hz"); break;
    case LIS3MDL_DATARATE_2_5_HZ: Serial3.println("2.5 Hz"); break;
    case LIS3MDL_DATARATE_5_HZ: Serial3.println("5 Hz"); break;
    case LIS3MDL_DATARATE_10_HZ: Serial3.println("10 Hz"); break;
    case LIS3MDL_DATARATE_20_HZ: Serial3.println("20 Hz"); break;
    case LIS3MDL_DATARATE_40_HZ: Serial3.println("40 Hz"); break;
    case LIS3MDL_DATARATE_80_HZ: Serial3.println("80 Hz"); break;
    case LIS3MDL_DATARATE_155_HZ: Serial3.println("155 Hz"); break;
    case LIS3MDL_DATARATE_300_HZ: Serial3.println("300 Hz"); break;
    case LIS3MDL_DATARATE_560_HZ: Serial3.println("560 Hz"); break;
    case LIS3MDL_DATARATE_1000_HZ: Serial3.println("1000 Hz"); break;
  }

  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
  Serial3.print("Range set to: ");
  switch (lis3mdl.getRange()) {
    case LIS3MDL_RANGE_4_GAUSS:
      Serial3.println("+-4 gauss"); break;
    case LIS3MDL_RANGE_8_GAUSS:
      Serial3.println("+-8 gauss"); break;
    case LIS3MDL_RANGE_12_GAUSS:
      Serial3.println("+-12 gauss"); break;
    case LIS3MDL_RANGE_16_GAUSS:
      Serial3.println("+-16 gauss"); break;
  }

  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true, // enable z axis
                          true, // polarity
                          false, // don't latch
                          true); // enabled!


  // Initialize LSM6DSOX

  if (!sox.begin_I2C(LSM6DS_I2CADDR_DEFAULT, &Wire1)) {
    while (1) {
      delay(10);
    }
  }

  Serial3.println("LSM6DSOX Found!");

  // sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  Serial3.print("Accelerometer range set to: ");
  switch (sox.getAccelRange()) {
    case LSM6DS_ACCEL_RANGE_2_G:
      Serial3.println("+-2G");
      break;
    case LSM6DS_ACCEL_RANGE_4_G:
      Serial3.println("+-4G");
      break;
    case LSM6DS_ACCEL_RANGE_8_G:
      Serial3.println("+-8G");
      break;
    case LSM6DS_ACCEL_RANGE_16_G:
      Serial3.println("+-16G");
      break;
  }

  // sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );
  Serial3.print("Gyro range set to: ");
  switch (sox.getGyroRange()) {
    case LSM6DS_GYRO_RANGE_125_DPS:
      Serial3.println("125 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_250_DPS:
      Serial3.println("250 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_500_DPS:
      Serial3.println("500 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_1000_DPS:
      Serial3.println("1000 degrees/s");
      break;
    case LSM6DS_GYRO_RANGE_2000_DPS:
      Serial3.println("2000 degrees/s");
      break;
    case ISM330DHCX_GYRO_RANGE_4000_DPS:
      break; // unsupported range for the DSOX
  }

  // sox.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial3.print("Accelerometer data rate set to: ");
  switch (sox.getAccelDataRate()) {
    case LSM6DS_RATE_SHUTDOWN:
      Serial3.println("0 Hz");
      break;
    case LSM6DS_RATE_12_5_HZ:
      Serial3.println("12.5 Hz");
      break;
    case LSM6DS_RATE_26_HZ:
      Serial3.println("26 Hz");
      break;
    case LSM6DS_RATE_52_HZ:
      Serial3.println("52 Hz");
      break;
    case LSM6DS_RATE_104_HZ:
      Serial3.println("104 Hz");
      break;
    case LSM6DS_RATE_208_HZ:
      Serial3.println("208 Hz");
      break;
    case LSM6DS_RATE_416_HZ:
      Serial3.println("416 Hz");
      break;
    case LSM6DS_RATE_833_HZ:
      Serial3.println("833 Hz");
      break;
    case LSM6DS_RATE_1_66K_HZ:
      Serial3.println("1.66 KHz");
      break;
    case LSM6DS_RATE_3_33K_HZ:
      Serial3.println("3.33 KHz");
      break;
    case LSM6DS_RATE_6_66K_HZ:
      Serial3.println("6.66 KHz");
      break;
  }

  // sox.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  Serial3.print("Gyro data rate set to: ");
  switch (sox.getGyroDataRate()) {
    case LSM6DS_RATE_SHUTDOWN:
      Serial3.println("0 Hz");
      break;
    case LSM6DS_RATE_12_5_HZ:
      Serial3.println("12.5 Hz");
      break;
    case LSM6DS_RATE_26_HZ:
      Serial3.println("26 Hz");
      break;
    case LSM6DS_RATE_52_HZ:
      Serial3.println("52 Hz");
      break;
    case LSM6DS_RATE_104_HZ:
      Serial3.println("104 Hz");
      break;
    case LSM6DS_RATE_208_HZ:
      Serial3.println("208 Hz");
      break;
    case LSM6DS_RATE_416_HZ:
      Serial3.println("416 Hz");
      break;
    case LSM6DS_RATE_833_HZ:
      Serial3.println("833 Hz");
      break;
    case LSM6DS_RATE_1_66K_HZ:
      Serial3.println("1.66 KHz");
      break;
    case LSM6DS_RATE_3_33K_HZ:
      Serial3.println("3.33 KHz");
      break;
    case LSM6DS_RATE_6_66K_HZ:
      Serial3.println("6.66 KHz");
      break;
  }
}

void loopIMU() {
  lis3mdl.read();      // get X Y and Z data at once

  // Then print out the raw data
  //Serial3.print("X:  ");
  //Serial3.print(lis3mdl.x);
  //Serial3.print("    Y:  ");
  //Serial3.print(lis3mdl.y);
  //Serial3.print("    Z:  ");
  //Serial3.println(lis3mdl.z);

  /* Or....get a new sensor event, normalized to uTesla */
  sensors_event_t event;
  lis3mdl.getEvent(&event);
  /* Display the results (magnetic field is measured in uTesla) */
  //Serial3.print("X: ");
  //Serial3.print(event.magnetic.x);
  //Serial3.print("    Y: ");
  //Serial3.print(event.magnetic.y);
  //Serial3.print("    Z: ");
  //Serial3.print(event.magnetic.z);
  //Serial3.println(" uTesla ");

  magn = String(event.magnetic.x) + "," + String(event.magnetic.y) + "," + String(event.magnetic.z);

}

void loopTemperature()
{
  const float celsius = Mcp9808.readTempC();
  const float fahrenheit = Mcp9808.readTempF();

  //Serial3.printf("Temperature (*C): %f\r\n", (double)celsius);
  //Serial3.printf("Temperature (*F): %f\r\n", (double)fahrenheit);

  temp = String(celsius) + "," + String(fahrenheit);

}


void loopLSM6DSOX() {
  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);

  //Serial3.print("Temperature ");
  //Serial3.print(temp.temperature);
  //Serial3.println(" deg C");

  /* Display the results (acceleration is measured in m/s^2) */
  /*Serial3.print("Accel X: ");
    Serial3.print(accel.acceleration.x);
    Serial3.print("    Y: ");
    Serial3.print(accel.acceleration.y);
    Serial3.print("    Z: ");
    Serial3.print(accel.acceleration.z);
    Serial3.println(" m/s^2 ");*/

  acc = String(accel.acceleration.x) + "," + String(accel.acceleration.y) + "," + String(accel.acceleration.z);

  /* Display the results (rotation is measured in rad/s) */
  /*Serial3.print("Gyro X: ");
  Serial3.print(gyro.gyro.x);
  Serial3.print("    Y: ");
  Serial3.print(gyro.gyro.y);
  Serial3.print("    Z: ");
  Serial3.print(gyro.gyro.z);
  Serial3.println(" radians/s ");
  Serial3.println();*/

  gyros = String(gyro.gyro.x) + "," + String(gyro.gyro.y) + "," + String(gyro.gyro.z);


  //  // Serial3 plotter friendly format

  //  Serial3.print(temp.temperature);
  //  Serial3.print(",");

  //  Serial3.print(accel.acceleration.x);
  //  Serial3.print(","); Serial3.print(accel.acceleration.y);
  //  Serial3.print(","); Serial3.print(accel.acceleration.z);
  //  Serial3.print(",");

  // Serial3.print(gyro.gyro.x);
  // Serial3.print(","); Serial3.print(gyro.gyro.y);
  // Serial3.print(","); Serial3.print(gyro.gyro.z);
  // Serial3.println();
  //  delayMicroseconds(10000);

}
