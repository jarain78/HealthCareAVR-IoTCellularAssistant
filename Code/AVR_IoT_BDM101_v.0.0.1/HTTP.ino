
void initHttp() {
  LedCtrl.begin();
  LedCtrl.startupCycle();

  Log.begin(115200);
  //Log.info(F("Starting HTTP example"));

  // Start LTE modem and connect to the operator
  if (!Lte.begin()) {
    Log.error(F("Failed to connect to the operator"));
    serverIsConnected = false;
    return;
  }

  Log.infof(F("Connected to operator: %s\r\n"), Lte.getOperator().c_str());

  // --- HTTP ---

  Log.info(F("---- Testing HTTP ----"));

  if (!HttpClient.configure(DOMAIN, 80, false)) {
    Log.info(F("Failed to configure http client\r\n"));
  }

  Log.info(F("Configured to HTTP"));
}


//void getHttp() {
//  response = HttpClient.get("/avr_iot");
//  Log.infof(F("GET - HTTP status code: %u, data size: %u\r\n"), response.status_code, response.data_size);
//}

void postHttp(String data2post) {

  String headset = serverService + "api_key:" + api_key + "/sensor_id:" + sensor_id + "/data" ;

  response_post = HttpClient.post(headset.c_str(), data2post.c_str()); //"{\"Hello\": \"I'm the AVR-IoT-Cellular-Mini\"}");
  Log.infof(F("POST - HTTP status code: %u, data size: %u\r\n"), response_post.status_code, response_post.data_size);

  // Add some extra bytes for termination
  String body = HttpClient.readBody(response_post.data_size + 16);

  if (body != "") {
    //Log.infof(F("Body: %s\r\n"), body.c_str());
    Serial3.print("Body: ");
    Serial3.println(body);
  }

}


void getHttp() {
  String headset = "/ecg"; //"api_key:" + api_key + "/sensor_id:" + sensor_id + "/data" ;

  response_get = HttpClient.get(headset.c_str());
  //Log.infof(F("GET - HTTP status code: %u, data size: %u\r\n"), response_get.status_code, response_get.data_size);
  // Add some extra bytes for termination
  String body = HttpClient.readBody();//response_get.data_size);
  

  if (body != "") {
    ECG_Diagnostic = body;
    Serial3.println(ECG_Diagnostic);
  }

}

//****************************
//Creating Payload to be Post
//****************************

void createPOST_PayLoad(String ecg_Data) {

  loopIMU();
  loopTemperature();
  loopLSM6DSOX();

  ECG_Payload = "{\"sensor_id\": \"AVR-IoT\", \"bio_signal\":[" + ecg_Data + "], \"pre_diagnostic\": \"Diagnostic: Ok\",  \"HR\":[" + hearth_rate +  "], \"QOS\":[" + quality_signal + "],  \"temperature\":[" + temp + "], \"accelerometer\":[" + acc + "], \"gyroscope\":[" + gyros + "], \"magentometer\":[" + magn + "]}";
  if (serverIsConnected) {

    //splitString(ecg_Data);

    postHttp(ECG_Payload);
    esg_str2send = ecg_Data;

    delay(500);
    Serial3.println(ECG_Payload);
    ECG_Diagnostic = "Diagnostic: Ok";
    delay(500);

    ECG_Payload = "";
    //Serial2.flush();
    getHttp();
  }

}

//****************************
//Creating Diagnostic
//****************************

void createGET_Diagnostic() {
  if (serverIsConnected) {
    getHttp();
  }

}

/*void splitString(String strTest) {
  StringSplitter *splitter = new StringSplitter(strTest, ',', 128);  // new StringSplitter(string_to_split, delimiter, limit)
  int itemCount = splitter->getItemCount();
  Serial.println("Item count: " + String(itemCount));

  for (int i = 0; i < itemCount; i++) {
    String item = splitter->getItemAtIndex(i);
    Serial3.println("Item @ index " + String(i) + ": " + String(item));
  }

  Serial3.println(F("End of program."));
  }*/
