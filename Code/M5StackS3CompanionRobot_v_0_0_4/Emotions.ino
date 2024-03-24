
void neutral() {
}

void bored(int x1, int x2, int y, int factor) {
  img.fillEllipse(x1, y - factor, 40, 35, CoreS3.Display.color332(0, 0, 0));
  img.fillEllipse(x2, y - factor, 40, 35, CoreS3.Display.color332(0, 0, 0));
}

void angry(int x1, int x2, int y, int factor, int factor1) {
  img.fillEllipse(x1 + factor1, y - 40, 30, 35, CoreS3.Display.color332(0, 0, 0));
  img.fillEllipse(x2 + factor1, y - 40, 30, 35, CoreS3.Display.color332(0, 0, 0));

}
