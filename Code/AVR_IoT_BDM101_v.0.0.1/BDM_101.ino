
void parsePayload() {

  uint8_t bytesParsed = 0;  // Número de bytes procesados
  uint8_t code;
  uint8_t lengthBytes;  // Número actual de bytes de Value incluidos en DataRow
  uint8_t extendedCodeLevel;
  int16_t rawValue = 0;  // Datos de ECG

  while (bytesParsed < Uart2_Len) {
    extendedCodeLevel = 0;
    while (Uart2_Buffer[3 + bytesParsed] == EXCODE) {
      extendedCodeLevel++;
      bytesParsed++;
    }
    code = Uart2_Buffer[3 + bytesParsed];
    bytesParsed++;
    if (code >= 0x80) {
      lengthBytes = Uart2_Buffer[3 + bytesParsed];
      bytesParsed++;
    } else
      lengthBytes = 1;

    switch (code) {
      case 0x80:
        if (sig_quality >= 0) {
          rawValue = Uart2_Buffer[3 + bytesParsed];
          rawValue <<= 8;
          rawValue |= Uart2_Buffer[4 + bytesParsed];

          ecg_value = rawValue;

          ecgBuffer[x_time] = ecg_value;

          if (get_ecg == true) {
            LedCtrl.on(Led::USER);
            //Wire1.beginTransmission(I2C_DEV_ADDR);
            //Wire1.println(String(rawValue));
            //uint8_t error = Wire1.endTransmission(true);
            n_get_ecg = n_get_ecg + 1;
          } else {
            LedCtrl.off(Led::USER);
          }

          if (n_get_ecg == 2) {
            send_data = false;
            get_ecg = false;
          }


          esg_str += String(rawValue) + ",";

          if (x_time > nData) {
            stop_flag = 1;
            stop_flag = 0;
            x_time = 0;

            int last_coma = esg_str.lastIndexOf(',');

            if(last_coma != -1){
              esg_str.remove(last_coma, 1);
            }
            
            createPOST_PayLoad(esg_str);
            esg_str = "";
          }
          x_time = x_time + 1;
          quality_signal = 1;
        } else {
          // La calidad de la señal no es buena, limpiar la pantalla o realizar otra acción
          // Por ejemplo, para limpiar la pantalla:
          // LCD_Clear(WHITE);
          // Serial3.println(-1);
          quality_signal = -1;
        }
        break;
      case 0x02:
        // Datos de calidad de la señal, 0 representa mala calidad mientras que 200 representa buena calidad
        sig_quality = Uart2_Buffer[3 + bytesParsed];
        break;
      case 0x03:
        // Datos de frecuencia cardíaca
        // Mostrar la frecuencia cardíaca en el monitor serie (Serial3)
        //Serial3.print("HeartRate");
        //Serial3.println(Uart2_Buffer[3 + bytesParsed]);
        hearth_rate = Uart2_Buffer[3 + bytesParsed];
        break;
    }
    bytesParsed += lengthBytes;
  }
}

void read_bdm_101() {
  if (Serial2.available()) {
    while (Serial2.available() > 0 && stop_flag == 0) {
      Uart2_Buffer[Uart2_Rx] = Serial2.read();
      //Serial3.println(Uart2_Rx);
      Uart2_Rx++;

      if (Uart2_Rx < 3) {
        if (Uart2_Buffer[Uart2_Rx - 1] != SYNC_BDM101) {
          //Serial3.print("\t");
          Uart2_Rx = 0;
          Uart2_Sta = 0;
        } else {
          //Serial3.println("Syncronization Ok...");
        }

      } else if (Uart2_Rx == 3) {

        Uart2_Len = Uart2_Buffer[Uart2_Rx - 1];

      } else if (Uart2_Rx < 4 + Uart2_Len) {
        checksum += Uart2_Buffer[Uart2_Rx - 1];

      } else {

        Uart2_check = Uart2_Buffer[Uart2_Rx - 1];
        checksum &= 0xFF;
        checksum = ~checksum & 0xFF;

        if (checksum != Uart2_check) {
          Uart2_Rx = 0;
          Uart2_Sta = 0;
          checksum = 0;
        } else {

          Uart2_Sta = 1;
        }
      }

      if (Uart2_Sta) {
        Uart2_Rx = 0;
        Uart2_Sta = 0;
        checksum = 0;
        parsePayload();

      }
    }
  }

}
