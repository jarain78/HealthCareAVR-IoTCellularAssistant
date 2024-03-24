
// Menu

static void get_ecg(bool holding) {
  setupMenu();
  String data = String(0x01);
  Serial.println("Get ECG -- Cmd: " + data);
  ecgScreen();

  sendI2C_Command(data);
  click_sound_effect();
  data_rx = "";
  //vTaskSuspend(hrspo2Handler);
}

static void get_ppg(bool holding = false) {
  setupMenu();
  //b_plot = false;
  String data = String(0x02);
  Serial.println("Get PPG -- Cmd: " + data);
  getHR();
  hearthRateScreen();
  sendI2C_Command(data + "," + String(beatTotalAvg / contaBeat));
  click_sound_effect();
  data_rx = "";
  contaBeat = 0;
  beatTotalAvg = 0;
  //vTaskResume(hrspo2Handler);
}

static void get_temperature(bool) {
  setupMenu();
  //b_plot = false;
  String data = String(0x03);
  Serial.println("Get Temperature -- Cmd: " + data);
  vTaskResume(temperatureHandler);

  sendI2C_Command(data);
  click_sound_effect();
  data_rx = "";
  //vTaskSuspend(hrspo2Handler);
}

static void get_spo2(bool) {
  setupMenu();
  //b_plot = false;
  String data = String(0x03);
  Serial.println("Get SPO2 -- Cmd: " + data);
  spo2Screen();
  sendI2C_Command(data);
  click_sound_effect();
  data_rx = "";
  //vTaskSuspend(hrspo2Handler);
}

static void get_diagnostic(bool) {
  setupMenu();
  //b_plot = false;
  String data = String(0x04);
  int data1 = 0x04;
  Serial.println("Get ECG Signal -- Cmd: " + data);
  diagnosticScreen();
  click_sound_effect();
  sendI2C_Command(data);

  // vTaskSuspend(hrspo2Handler);
}

/*static void get_image(bool) {
  //b_plot = true;
  Serial.println("Get Camera");
  vTaskResume(cameraHandler);
}*/

/*static void plot(bool) {
  //b_plot = true;
  Serial.println("Plot");
  img.createSprite(menu_w + 100, menu_h + 100);
  img.fillSprite(WHITE);
  img.pushSprite(130, 20);

  delay(20);
  vTaskResume(plotHandler);
}*/

static void exit_assistant(bool) {
  //b_plot = false;
  click_sound_effect();
  Serial.println("Assistant");
  img.clear();
  img.deleteSprite();
  img.deletePalette();
  img.createSprite(CoreS3.Display.width(), CoreS3.Display.height());
  img.fillSprite(BLACK);
  eyes(stepsX, stepsY);
  vTaskResume(eyeHandler);
  vTaskSuspend(menuHandler);
}

struct menu_item_t {
  const char* title;
  void (*func)(bool);
};

static const menu_item_t menus[] = {
  { "ECG", get_ecg },
  { "HR", get_ppg },
  { "Tempe", get_temperature },
  { "Diagniosti", get_diagnostic },
  { "Exit", exit_assistant },
  //{ "ch vol d", c_volume_down },
};
static constexpr const size_t menu_count = sizeof(menus) / sizeof(menus[0]);

void setupMenu() {
  img.createSprite(CoreS3.Display.width(), CoreS3.Display.height());
  img.fillSprite(BLACK);

  /*if (CoreS3.Display.width() < 100) {
    menu_x = 0;
    menu_y = 10;
    menu_w = CoreS3.Display.width() - 8;
  } else {
    CoreS3.Display.setFont(&fonts::DejaVu18);
  }*/
  CoreS3.Display.setFont(&fonts::DejaVu18);

  menu_padding = (CoreS3.Display.height() - menu_y) / menu_count;
  menu_h = menu_padding - 2;

  CoreS3.Display.setEpdMode(epd_mode_t::epd_fastest);
  CoreS3.Display.fillScreen(TFT_DARKGRAY);

  //CoreS3.Display.print("AVR-IoT ECG");

  CoreS3.Display.startWrite();
  for (size_t i = 0; i < menu_count; i++) {
    draw_menu(i, i == cursor_index);
  }
  CoreS3.Display.endWrite();
}


void hold_menu(bool holding) {
  if (menus[cursor_index].func != nullptr) {
    menus[cursor_index].func(holding);
  }
}

void create_menu() {
  if (!CoreS3.Display.displayBusy()) {


    int32_t b = (255 * (CoreS3.Display.height() - menu_y)) >> 8;
    int32_t m_vol = 2;
    int32_t c_vol = 2;

    CoreS3.Display.startWrite();
    CoreS3.Display.fillRect(menu_x + menu_w + 1, menu_y, 3, b - m_vol, CoreS3.Display.getBaseColor());
    CoreS3.Display.fillRect(menu_x + menu_w + 5, menu_y, 3, b - c_vol, CoreS3.Display.getBaseColor());
    CoreS3.Display.fillRect(menu_x + menu_w + 1, menu_y + b, 3, -m_vol, ~CoreS3.Display.getBaseColor());
    CoreS3.Display.fillRect(menu_x + menu_w + 5, menu_y + b, 3, -c_vol, ~CoreS3.Display.getBaseColor());
    CoreS3.Display.endWrite();
  }

  CoreS3.delay(2);
  CoreS3.update();

  auto touch_count = CoreS3.Touch.getCount();
  for (size_t i = 0; i < touch_count; i++) {
    auto detail = CoreS3.Touch.getDetail(i);
    if (((size_t)detail.x - menu_x) < menu_w) {
      size_t index = (detail.y - menu_y) / menu_padding;
      if (index < menu_count) {
        if (detail.wasPressed()) {
          select_menu(index);
        } else if (index == cursor_index) {
          if (detail.wasClicked()) {
            hold_menu(false);
          } else if (detail.isHolding()) {
            hold_menu(true);
          }
        }
      }
    }
  }
}


void draw_menu(size_t index, bool focus) {
  CoreS3.Display.startWrite();
  auto baseColor = CoreS3.Display.getBaseColor();
  CoreS3.Display.setColor(focus ? baseColor : ~baseColor);
  CoreS3.Display.drawRect(menu_x, menu_y + index * menu_padding, menu_w, menu_h);
  CoreS3.Display.drawRect(menu_x + 1, menu_y + index * menu_padding + 1, menu_w - 2, menu_h - 2);
  CoreS3.Display.setColor(focus ? ~baseColor : baseColor);
  CoreS3.Display.fillRect(menu_x + 2, menu_y + index * menu_padding + 2, menu_w - 4, menu_h - 4);
  CoreS3.Display.setTextDatum(textdatum_t::middle_center);
  CoreS3.Display.setTextColor(focus ? baseColor : ~baseColor, focus ? ~baseColor : baseColor);
  CoreS3.Display.drawString(menus[index].title, menu_x + (menu_w >> 1), menu_y + index * menu_padding + (menu_h >> 1));
  CoreS3.Display.endWrite();
}

void select_menu(size_t index) {
  CoreS3.Display.startWrite();
  draw_menu(cursor_index, false);
  cursor_index = index;
  draw_menu(cursor_index, true);
  CoreS3.Display.endWrite();
}


// This function represents the various screens where we display the SPO2 level, the PPG, and the diagnostic result.

void ecgScreen() {
  img.createSprite(menu_w + 100, menu_h + 100);
  img.fillSprite(WHITE);
  img.setFont(&fonts::DejaVu18);
  img.setTextColor(c7, c1);
  img.drawString("Please hold on ", 20, 20);
  img.drawString("for a moment while ", 20, 40);
  img.drawString("we acquire your ECG signal!", 20, 60);

  //CoreS3.Display.print("AVR-IoT ECG");
  img.pushSprite(130, 20);
  data_rx = "";
}

// The hearthRateScreen function displays the heart rate information on the screen.

void hearthRateScreen() {
  img.createSprite(menu_w + 100, menu_h + 100);
  img.fillSprite(WHITE);
  img.setFont(&fonts::DejaVu18);
  img.setTextColor(c7, c1);
  img.drawString("Hearth Rate!", 20, 20);
  img.drawString(String(beatTotalAvg / contaBeat), 20, 40);
  //CoreS3.Display.print("AVR-IoT ECG");
  img.pushSprite(130, 20);
  data_rx = "";
}

void temperatureScreen() {
  img.createSprite(menu_w + 100, menu_h + 100);
  img.fillSprite(WHITE);
  img.setFont(&fonts::DejaVu18);
  img.setTextColor(c7, c1);
  img.drawString("Temperature!", 20, 20);

  readTemperature();

  img.drawString(String(temperature), 20, 40);
  //CoreS3.Display.print("AVR-IoT ECG");
  img.pushSprite(130, 20);
  data_rx = "";
}

void spo2Screen() {
  img.createSprite(menu_w + 100, menu_h + 100);
  img.fillSprite(WHITE);
  img.setFont(&fonts::DejaVu18);
  img.setTextColor(c7, c1);
  img.drawString("SPO2!", 20, 20);
  img.drawString(data_rx, 20, 40);
  //CoreS3.Display.print("AVR-IoT ECG");
  img.pushSprite(130, 20);
  data_rx = "";
}

void diagnosticScreen() {
  img.createSprite(menu_w + 100, menu_h + 100);
  img.fillSprite(WHITE);
  img.setFont(&fonts::DejaVu18);
  img.setTextColor(c7, c1);
  img.drawString("ECG diagnosis!", 20, 20);
  img.drawString(data_rx, 20, 40);
  //CoreS3.Display.print("AVR-IoT ECG");
  img.pushSprite(130, 20);
  data_rx = "";
}



/*void plot() {

  static constexpr int shift = 6;

  int32_t w = CoreS3.Display.width();
  if (w > record_length - 1) {
    w = record_length - 1;
  }


  CoreS3.Display.display();
  CoreS3.Display.fillCircle(150, 180, 8, RED);
  //CoreS3.Display.drawString("Read Data", 220, 180);

  for (int32_t x = 0; x < w; ++x) {
    img.writeFastVLine(x, prev_y_plot[x], prev_h_plot[x], TFT_BLACK);
    int32_t y1 = (data[x] >> shift);
    int32_t y2 = (data[x + 1] >> shift);
    if (y1 > y2) {
      int32_t tmp = y1;
      y1 = y2;
      y2 = tmp;
    }
    int32_t y = ((CoreS3.Display.height()) >> 1) + y1;
    int32_t h = ((CoreS3.Display.height()) >> 1) + y2 + 1 - y;
    prev_y_plot[x] = y;
    prev_h_plot[x] = h;
    img.writeFastVLine(x, prev_y_plot[x], prev_h_plot[x], WHITE);
    img.pushSprite(130, 20);
  }
  CoreS3.Display.display();
  CoreS3.Display.fillCircle(150, 180, 8, GREEN);
  //CoreS3.Display.drawString("End", 220, 180);

  b_plot = false;
}*/
