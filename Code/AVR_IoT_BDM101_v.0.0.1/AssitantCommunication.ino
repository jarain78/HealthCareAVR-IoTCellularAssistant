
void ecgSignal() {

  // Envia el vector al esclavo
  //Wire.beginTransmission(I2C_DEV_ADDR);  // Dirección del esclavo (ajusta según sea necesario)
  //Wire1.println('@');
  for (int i = 0; i < 127; i++) {
    Serial3.print(ecgBuffer[i]);
    Wire1.println(ecgBuffer[i]);
    //Wire1.println(i);
  }
  Serial3.println();
  //Wire.endTransmission();
  Wire1.flush();
}

void splitData(String data_i2c) {
  char *token;
  // Obtener el primer token
  token = strtok(data_i2c.c_str(), ",");

  // Iterar a través de los tokens
  while (token != NULL) {
    hearth_rate = token;
    Serial3.println(hearth_rate);
    // Obtener el siguiente token
    token = strtok(NULL, ",");
  }
}

void onRequest() {

  if (i2cData.toInt() == 0x01) {
    Wire1.println(String(90));
    Serial3.print("ECG... ");
    send_data = true;
    get_hr = false;
    Serial3.println(send_data);

    /*Wire1.println("Ini");
      int length = esg_str2send.length();
      for (int i = 0; i < length; i += 30) {  // Enviar 30 caracteres a la vez (ajusta según sea necesario)
      String chunk = esg_str2send.substring(i, i + 30);
      Serial3.println(chunk);
      Wire1.write(chunk.c_str());
      delay(10);  // Pausa breve para permitir que el receptor procese los datos
      }
      Wire1.write("");  // Indicar fin de la transmisión*/

  } else if (i2cData.toInt() == 0x02) {
    //Wire1.println(String(120));
    send_data = false;
    get_hr = true;
    Serial3.print("HR...");
    Serial3.println(send_data);

  } else if (i2cData.toInt() == 0x03) {
    //Wire1.println(String(85));
    send_data = false;
    get_hr = false;
    Serial3.print("SPO2...");
    Serial3.println(send_data);

  } else if (i2cData.toInt() == 0x04) {
    send_data = false;
    get_hr = false;
    Serial3.print("Diagnostic...");
    Wire1.println(ECG_Diagnostic);
  }

}

void onReceive(int len) {
  Serial3.printf("onReceive[%d]: ", len);
  while (Wire1.available()) {
    i2cData = Wire1.readStringUntil('\n');
    Serial3.print("Data: ");
    Serial3.print(i2cData);
    
  }
  Serial3.println();
}


void initAssistantCommunication() {
  Wire1.onReceive(onReceive);
  Wire1.onRequest(onRequest);
  Wire1.begin((uint8_t)I2C_DEV_ADDR, I2C_SDA, I2C_SCL);
  Wire1.setClock(400000UL);
}
