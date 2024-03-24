
void click_sound_effect() {
  CoreS3.Speaker.playRaw(wav_unsigned_8bit_click, sizeof(wav_unsigned_8bit_click) / sizeof(wav_unsigned_8bit_click[0]), 44100, false);
}

