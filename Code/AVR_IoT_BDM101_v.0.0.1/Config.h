// https://programmersought.com/article/84888077916/

#include <Arduino.h>
#include <http_client.h>
#include <led_ctrl.h>
#include <log.h>
#include <lte.h>
#include <Adafruit_Sensor_Calibration.h>
#include <Adafruit_AHRS.h>
#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <mcp9808.h>
#include <Adafruit_LSM6DSOX.h>
#include <eloquent_tinyml.h>

//#include "MAX30105.h"
//#include "heartRate.h"

#include <Adafruit_MLX90640.h>

// uncomment *one* of the below
//#define PRINT_TEMPERATURES
#define PRINT_ASCIIART

//#include "StringSplitter.h"
//#include <EloquentTinyML.h>
//#include <eloquent_tinyml/tensorflow.h>

#define EXCODE 0x55
#define I2C_DEV_ADDR 0x29
#define SYNC_BDM101 0xAA
#define BDM101_RESET PIN_PD5
#define BDM101_CS PIN_PD6

#define  I2C_SDA PIN_PF2
#define  I2C_SCL PIN_PF3

// Http Server
#define DOMAIN "Your-Server-Host"

uint8_t Uart2_Buffer[256];  // Buffer de recepción
uint8_t Uart2_Rx = 0;       // Índice del buffer UART2
uint8_t Uart2_Len;          // Longitud de los datos (incluido el CRC después del tercer byte)
int checksum = 0;           // Valor de verificación calculado por PayLoad
uint8_t Uart2_Sta = 0;      // Indicador de marco de datos correcto
uint8_t Uart2_check;        // Valor de verificación del marco
uint8_t sig_quality = 200;  // Calidad de la señal
uint32_t ecg_value = 0;

int stop_flag = 0;


int x_time = 0;

int nData = 187;
char ecgBuffer[127];


String esg_str = " ";
String esg_str2send = " ";
String sig_data = " ";
String ECG_Payload = " ";
String ECG_Data = " ";

String hearth_rate = " ";

//String ECG_Diagnostic = "\"O\"";;
String ECG_Diagnostic = "";
String ECG_Diagnostic_POST = " ";
int conta_ecg_signal = 0;

//int hearth_rate = 0;
int quality_signal = 0;

// Http Server
HttpResponse response_post;
HttpResponse response_get;
bool serverIsConnected = true;

int n_get_ecg = 0;

bool get_ecg = false;
bool get_hr = false;
bool send_data = false;
bool get_diagnostic = false;


String serverService = "/avr_iot/";
String api_key = "Serve-Host_Api-Key";
String sensor_id = "AVR-IoT";

int httpCode = 0;

// IMU
Adafruit_LIS3MDL lis3mdl;
Adafruit_LSM6DSOX sox;

String acc = "";
String gyros = "";
String magn = "";
String temp = "";

String i2cData = "";

// MAX3015
const byte RATE_SIZE = 4;  //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];     //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;  //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

// MLX90640
Adafruit_MLX90640 mlx;
float frame[32 * 24]; // buffer for full frame of temperatures
