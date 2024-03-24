
uint32_t k = 0;
bool readOk = false;

int datosRecibidos[128];

/*void onReceive(int len) {

  Serial.print("MSG Len: ");
  Serial.println(len);

  // Se llama cuando el maestro envía datos
  int i = 0;
  while (Wire.available()) {
    datosRecibidos[i] = Wire.read();
    i++;
  }

  for (int i = 0; i < len; i++) {
    CoreS3.Display.print(String(datosRecibidos[i]));

    Serial.print(datosRecibidos[i]);
    Serial.print(", ");
  }
  Serial.println();
  Wire.flush();
}*/

void onReceive(int len) {
  Serial.printf("onReceive[%d]: ", len);
  while (Wire.available()) {
    i2cData = Wire.readStringUntil('\n');
    Serial.print("Data: ");
    Serial.print(i2cData);
    CoreS3.Display.print(i2cData);
  }
  Serial.println();
}


void sendI2C_Command(String cmd) {
  Wire.flush();

  //Write message to the slave
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.println(cmd);
  uint8_t error = Wire.endTransmission(true);

  //Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);

  if ((bool)bytesReceived) {  //If received more than zero bytes
    uint8_t temp[bytesReceived];
    data_rx = Wire.readStringUntil('\n');
    Serial.println(data_rx);
    /*while (Wire.available()) {
      Serial.print(Wire.readStringUntil('\n'));
      Serial.print(", ");
    }
    Serial.println();
    Serial.println(data_rx);*/
  }
}

/*void sendI2C_Command_1(int cmd) {
  //Write message to the slave
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(cmd);
  Wire.endTransmission();
}*/

/*void sendI2C_Command_2(String cmd) {
  Wire.flush();
  //Write message to the slave
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.println(cmd);
  uint8_t error = Wire.endTransmission(true);

  //Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR_XIAO, 128);
  //Serial.printf("requestFrom: %u\n", bytesReceived);

  if ((bool)bytesReceived) {  //If received more than zero bytes
    uint8_t temp[bytesReceived];
    Serial.println(Wire.readStringUntil('\n'));

    //Wire.readBytes(temp, bytesReceived);
    //Serial.println(temp);
    //log_print_buf(temp, bytesReceived);
  }
}*/

//****************************************************************************
// This function initializes the MAX30105 sensor and retrieves data from it. *
// The MAX30105 sensor is a versatile sensor capable of measuring heart rate *
// blood oxygen saturation, and other biometric data.                        *
//****************************************************************************


void initHR() {

  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))  //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1)
      ;
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup();                     //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);  //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);   //Turn off Green LED

  //initMAX();
}

void getHR() {

  for (int i = 0; i < 2000; i++) {
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
        rates[rateSpot++] = (byte)beatsPerMinute;  //Store this reading in the array
        rateSpot %= RATE_SIZE;                     //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0; x < RATE_SIZE; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }

    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);

    beatTotalAvg = beatTotalAvg + beatAvg;
    contaBeat++;
    
    if (irValue < 50000)
      Serial.print(" No finger?");

    Serial.println();
  }
}
