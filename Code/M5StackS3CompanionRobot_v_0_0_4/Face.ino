
void touch() {
  auto t = CoreS3.Touch.getDetail();

  if (prev_x != t.x || prev_y != t.y) {
    //CoreS3.Display.fillRect(0, CoreS3.Display.height() / 2,
    //                        CoreS3.Display.width(),
    //                        CoreS3.Display.height() / 2, BLACK);

    //CoreS3.Display.drawString("X:" + String(t.x) + " / " + "Y:" + String(t.y), CoreS3.Display.width() / 2, 10);

    prev_x = t.x;
    prev_y = t.y;
    //CoreS3.Display.drawPixel(prev_x, prev_y);
    Serial.print(prev_x);
    Serial.print(" ");
    Serial.println(prev_y);
  }
}

void eyes(int pupil_x, int pupil_y) {
  int dx = 50;
  int x = (CoreS3.Display.width() / 2);   //rand() % CoreS3.Display.width();
  int y = (CoreS3.Display.height() / 2);  //rand() % CoreS3.Display.height();
  int r = (CoreS3.Display.width() >> 4) + 2;
  uint16_t c = rand();

  int x1 = x - dx;
  int x2 = x + dx;

  pupilAnimation(x1, x2, y);

  eyes(x1, x2, y);

  //bored(x1, x2, y, 40);  // Bored OK
  //delay(1000);
  //angry(x1, x2, y, 40, 15);

  pupils(pupil_x, pupil_y);
  //pupils(pupil_center_x, pupil_center_y);

  //pupils(70, 150);
  img.pushSprite(0, 0);

  //blink(x1, x2, y);
}

void eyes(int x1, int x2, int y) {
  // Eye Left
  img.fillEllipse(x1, y, 40, 70, CoreS3.Display.color332(255, 255, 255));
  // Eye Right
  img.fillEllipse(x2, y, 40, 70, CoreS3.Display.color332(255, 255, 255));
}

void pupils(int pupil_x, int pupil_y) {
  img.fillEllipse(pupil_x, pupil_y, 15, 30, CoreS3.Display.color332(0, 0, 0));
  img.fillEllipse(pupil_x + 100, pupil_y, 15, 30, CoreS3.Display.color332(0, 0, 0));
}

void pupilTest() {

  float a = 10 * cos(radians(i));  // Semieje mayor de 50
  float b = 20;                    // * sin(radians(i));  // Semieje menor de 30

  stepsX = map(a, -10, 10, 86, 134);   // Mapear valores para los pasos
  stepsY = map(b, -20, 20, 111, 120);  // Mapear valores para los pasos

  if (i > 180) {
    i = 180.0f;
    index_animation = random(0, max_state);
  }
  i = i + interval;
}


void blink(int x1, int x2, int y) {
  // Eye Left
  img.fillEllipse(x1, y, 40, 70, CoreS3.Display.color332(0, 0, 0));
  // Eye Right
  img.fillEllipse(x2, y, 40, 70, CoreS3.Display.color332(0, 0, 0));
  img.pushSprite(0, 0);
}


void pupilAnimation(int x1, int x2, int y) {

  if (index_animation == 0) {


    float a = 10 * cos(radians(i));  // Semieje mayor de 50
    float b = 20 * sin(radians(i));  // Semieje menor de 30

    stepsX = map(a, -20, 20, 86, 134);   // Mapear valores para los pasos
    stepsY = map(b, -35, 35, 111, 120);  // Mapear valores para los pasos

    //Serial.print("Index Animation: ");
    //Serial.println(index_animation);

    if (i > 45) {
      i = 0.0f;
      index_animation = random(0, max_state);
      //blink(x1, x2, y);
      //delay(10);
      //
    }
    i = i + interval;

  } else if (index_animation == 1) {

    //Serial.print("Index Animation: ");
    //Serial.println(index_animation);

    stepsX = pupil_center_x;  //70;
    stepsY = pupil_center_y;  //121;

    if (i > 3) {
      index_animation = random(0, max_state);
      i = 0;
      //blink(x1, x2, y);
      //delay(10);
    }
    i = i + 1;
    delay(1000);
  } else if (index_animation == 2) {


    //Serial.print("Index Animation: ");
    //Serial.println(index_animation);

    float a = 10 * cos(radians(i));  // Semieje mayor de 50
    float b = 20;                    // * sin(radians(i));  // Semieje menor de 30

    stepsX = map(a, -10, 10, 86, 134);   // Mapear valores para los pasos
    stepsY = map(b, -20, 20, 111, 120);  // Mapear valores para los pasos

    if (i > 180) {
      i = 180.0f;
      index_animation = random(0, max_state);
      blink(x1, x2, y);
      delay(10);
    }
    i = i + interval;
  } else if (index_animation == 3) {

    float a = 10;                    // * cos(radians(i));  // Semieje mayor de 50
    float b = 20 * sin(radians(i));  // * sin(radians(i));  // Semieje menor de 30

    stepsX = map(a, -10, 10, 86, 134);   // Mapear valores para los pasos
    stepsY = map(b, -20, 20, 111, 120);  // Mapear valores para los pasos

    if (i > 359) {
      i = 180.0f;
      index_animation = random(0, max_state);
      blink(x1, x2, y);
      delay(100);
    }
    i = i + interval;
  } else if (index_animation == 4) {


    //Serial.print("Index Animation: ");
    //Serial.println(index_animation);

    float a = 10 * cos(radians(i));  // * cos(radians(i));  // Semieje mayor de 50
    float b = 20 * sin(radians(i));  // * sin(radians(i));  // Semieje menor de 30

    stepsX = map(a, -10, 10, 86, 134);   // Mapear valores para los pasos
    stepsY = map(b, -20, 20, 111, 120);  // Mapear valores para los pasos

    if (i > 270) {
      i = 0.0f;
      index_animation = random(0, max_state);
      blink(x1, x2, y);
      delay(10);
    }
    i = i + interval;
  } else if (index_animation == max_state) {


    //Serial.print("Index Animation: ");
    //Serial.println(index_animation);

    float a = 10;                    // * cos(radians(i));  // * cos(radians(i));  // Semieje mayor de 50
    float b = 20 * tan(radians(i));  // * sin(radians(i));  // Semieje menor de 30

    stepsX = map(a, -10, 10, 86, 134);   // Mapear valores para los pasos
    stepsY = map(b, -20, 20, 111, 120);  // Mapear valores para los pasos

    if (i > 270) {
      i = 0.0f;
      index_animation = random(0, max_state);
      
      blink(x1, x2, y);
      delay(10);
    }
    i = i + interval;
  }
}


void screenReadECG() {
}
