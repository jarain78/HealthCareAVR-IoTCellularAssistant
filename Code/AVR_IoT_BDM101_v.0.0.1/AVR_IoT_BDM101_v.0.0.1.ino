#include "Config.h"

//MAX30105 particleSensor;

// Message Format
// {"sensor_id": [AVR-IoT], "bio_signal":[421,413,390,379,386,394,391,275,281,278,267,252,241,241,250,261,267,273,291,324,363,394,412,421,429,436,441,445,450,452,440,404,350,297,261,243,231,216,202,203,222,251,270,267,252,239,233,221,192,154,128,123,129,128,122,128,152,186,210,219,219,210,188,157,131,119,116,107,88,73,73,85,94,96,98,106,109,96,71,47,27,-8,-78,-179,-279,-347,-381,-398,-415,-434,-453,-467,-479,-485,-485,-480,-476,-470,-455,-421,-370,-309,-246,-189,-142,-107,-79,-49,-14,17,29,15,-10,-25,-17,5,25,38,53,77,105,121,109,73,37,16,9,4,], "pre_diagnostic":["O"],  "HR":[113], "QOS":[1],  "temperature":[163.94,327.09], "accelerometer":[0.15,0.00,1.99], "gyroscope":[2.59,0.04,0.00], "magentometer":[475.18,0.00,0.00]}


void setup() {

  Serial2.swap(1);

  pinConfigure(5, PIN_DIR_OUTPUT);
  pinConfigure(6, PIN_DIR_OUTPUT);

  Serial3.begin(115200);
  Serial2.begin(57600);

  digitalWrite(BDM101_RESET, HIGH);
  digitalWrite(BDM101_CS, HIGH);
  Serial3.println("AVR-IoT_ECG...");

  Serial2.flush();

  initHttp();

  initAssistantCommunication();
  //intiAllSensors();
  //initHR();
  //initMLX90640();

  Serial3.println("End Configuration");

}

void loop() {

  if (send_data == true) {
    read_bdm_101();
  }

  //readMLX90640();
  
  //if (get_hr == true) {
  //  getHR();
  //}
  //Serial3.println("LOOP");
  delay(2);

  /* else {
    Serial3.println();
    Serial3.println();
    Serial3.println(esg_str2send);

    for (int i = 0; i < nData; i++) {
      Serial3.println(ecgBuffer[i]);
    }

    Serial3.println();
    Serial3.println();
    delay(20);
    send_data = false;
    }*/

  /*if (get_ecg==true) {
    splitString(esg_str);
    send_data = false;
    }*/

  /*if (get_ecg) {
    Serial3.println("Getting-ECG");

    get_ecg = false;
    Serial3.println();
    Serial3.println("End-Getting-ECG");
    }*/

}
