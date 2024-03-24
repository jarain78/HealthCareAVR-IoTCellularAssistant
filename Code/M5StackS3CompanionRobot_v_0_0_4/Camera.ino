
/*void setupCamera() {

  if (!CoreS3.Camera.begin()) {
    CoreS3.Display.drawString("Camera Init Fail",
                              CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2);
  }
  CoreS3.Display.drawString("Camera Init Success", CoreS3.Display.width() / 2,
                            CoreS3.Display.height() / 2);

  //CoreS3.Camera.sensor->set_framesize(CoreS3.Camera.sensor, FRAMESIZE_QVGA);
}*/


/*void takePicture() {

  CoreS3.Camera.sensor->set_framesize(CoreS3.Camera.sensor, FRAMESIZE_SVGA);


  if (CoreS3.Camera.get()) {
#ifdef CONVERT_TO_JPEG
    uint8_t *out_jpg = NULL;
    size_t out_jpg_len = 0;
    frame2jpg(CoreS3.Camera.fb, 255, &out_jpg, &out_jpg_len);
    CoreS3.Display.drawJpg(out_jpg, out_jpg_len, 0, 0,
                           CoreS3.Display.width(), CoreS3.Display.height());
    free(out_jpg);
#else
    CoreS3.Display.pushImage(0, 0, CoreS3.Display.width(),
                             CoreS3.Display.height(),
                             (uint16_t *)CoreS3.Camera.fb->buf);
#endif

    CoreS3.Camera.free();
  }
}*/
