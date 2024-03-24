
void eye_task(void *pvParameter) {

  while (1) {

    //Serial.println("Tarea Ojos");

    CoreS3.update();
    eyes(stepsX, stepsY);

    if (CoreS3.Touch.getDetail(0).wasClicked()) {
      setupMenu();
      //img.deletePalette();
      //img.fillSprite(BLACK);
      //img.pushSprite(0, 0);
      img.deleteSprite();
      img.deletePalette();

      vTaskResume(menuHandler);
      vTaskSuspend(eyeHandler);
      //CoreS3.Display.init();
      //initECG = true;
    }
    vTaskDelay(1);
  }
}

void menu_task(void *pvParameter) {
  ///setupSlave();

  //CoreS3.Display.fillScreen(TFT_DARKGRAY);
  //vTaskDelay(100);

  img.deleteSprite();
  setupMenu();

  while (1) {
    create_menu();

    /*Serial.println((bool)bytesReceived);
    //Read 16 bytes from the slave
    bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);
    //Serial.printf("requestFrom: %u\n", bytesReceived);
    if ((bool)bytesReceived) {  //If received more than zero bytes

      while (Wire.available()) {

        String mensaje = Wire.readStringUntil('\n');

        //ecg_buffer[k] = mensaje.toInt();
        Serial.println("Mensaje recibido: " + mensaje);
        CoreS3.Display.drawString(mensaje, 220, 180);

        if (mensaje.toInt() == 90) {
          CoreS3.Display.display();
          CoreS3.Display.fillCircle(150, 190, 8, GREEN);
        } else {
          CoreS3.Display.display();
          CoreS3.Display.fillCircle(150, 180, 8, RED);
        }
      }
      uint8_t temp[bytesReceived];
      //Serial.println(Wire.read());
      Wire.readBytes(temp, bytesReceived);
      //Serial.println(temp);
      log_print_buf(temp, bytesReceived);
      bytesReceived = 0;
    }*/

    vTaskDelay(10);
  }
}

void hr_spo2_task(void *pvParameter) {
  int n_samples = 0;
  while (1) {
    getHR();
    if (n_samples == 500) {
      vTaskSuspend(hrspo2Handler);
    }
    n_samples = n_samples + 1;
  }
}

void temperature_task(void *pvParameter) {

  //vTaskSuspend(menuHandler);


  while (1) {
    Serial.println("Temperature Task");
    vTaskDelay(10);
    temperatureScreen();
    delay(100);
    vTaskSuspend(temperatureHandler);

    //loopCamera();
  }
}


/*void camera_task(void *pvParameter) {

  //vTaskSuspend(menuHandler);


  while (1) {
    Serial.println("Tarea Camera");
    vTaskDelay(10);
    takePicture();
    delay(100);
    vTaskSuspend(cameraHandler);

    //loopCamera();
  }
}*/


// Tareas Menu

/*void ecg_task(void *pvParameter) {

  vTaskSuspend(menuHandler);
  while (1) {
    Serial.println("Tarea ECG");
    vTaskDelay(10);


    vTaskResume(menuHandler);
    vTaskSuspend(ecgHandler);
  }
}


void ppg_task(void *pvParameter) {

  while (1) {

    Serial.println("Tarea PPG");
    vTaskDelay(1);
  }
}

void spo2_task(void *pvParameter) {

  while (1) {

    Serial.println("Tarea SPO2");
    vTaskDelay(1);
  }
}*/

/*void plot_task(void *pvParameter) {

  int k = 0;

  while (1) {
    data[k] = random(0, 130);
    if (k == record_length) {
      k = 0;
      //plot();
    }
    k = k + 1;
    Serial.println("Tarea PLOT");
    vTaskDelay(1);
    //Serial.println("Tarea Menu");
    //Serial.println(b_plot);

    /*if (b_plot == true) {

      for (int k = 0; k < record_length; k++) {
        data[k] = random(0, 130);
        //Serial.println(data[k]);
      }
      plot();
    }
  }
}*/
