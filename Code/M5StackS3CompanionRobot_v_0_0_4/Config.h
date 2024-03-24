// WAV file to Hex
// http://tomeko.net/online_tools/file_to_hex.php?lang=en


#include <M5CoreS3.h>
#include <Wire.h>
#include "esp_camera.h"
#include <ArduinoBLE.h>
#include "audio_file.h"
#include "MAX30105.h"
#include "heartRate.h"

#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

// uncomment *one* of the below
#define PRINT_TEMPERATURES
//#define PRINT_ASCIIART

// Glucometro
// 200675
// AF9DF7A3-E595-11E3-96B4-0002A5D5C51B
// MAC:  c0:de:19:35:81:9e


#define PKT_ECG 0XB1
#define PKT_DIADGNOSTIC 0XB2
#define PKT_HEARTHRATE 0XB3
#define DEBUG 0

#define I2C_DEV_ADDR 0x29
#define I2C_DEV_ADDR_XIAO 0x28

#define I2C_SCL 1
#define I2C_SDA 2

#define DATA_SIZE 168

//define color
#define c1 0xFFFFFF  //white
#define c2 0x18C3    //gray
#define c3 0x9986    //red
#define c4 0x2CAB    //green
#define c5 0xBDEF    //gold
#define c6 0xFFFAFA  //snow
#define c7 0x000000  //snow

M5Canvas img(&CoreS3.Display);

int receivedData[DATA_SIZE];

int prev_x = -1;
int prev_y = -1;

static m5::touch_state_t prev_state;

int stepsX = 0;
int stepsY = 0;

float P = 0.0f;

float i = 0.0f;
int index_animation = 0;
int max_state = 5;

float interval = 3.5;

// M5CoreS3
int pupil_center_x = 111;
int pupil_center_y = 128;

// ECG
uint32_t ecg_buffer[168];

// M5Dial
//int pupil_center_x = 92;
//int pupil_center_y = 164;

// RTOS
static TaskHandle_t menuHandler = NULL;
static TaskHandle_t eyeHandler = NULL;
static TaskHandle_t hrspo2Handler = NULL;
static TaskHandle_t temperatureHandler = NULL;

//static TaskHandle_t cameraHandler = NULL;

//static TaskHandle_t ecgHandler = NULL;
//static TaskHandle_t ppgHandler = NULL;
//static TaskHandle_t spo2Handler = NULL;
//static TaskHandle_t plotHandler = NULL;


bool initECG = false;

// Menu
static int menu_x = 2;
static int menu_y = 20;
static int menu_w = 120;
static int menu_h = 30;
static int menu_padding = 36;
size_t cursor_index = 0;

uint8_t bytesReceived = 0;

String i2cData = "";
String data_rx = "";
// Plot
/*bool b_plot = false;
uint8_t data[128];

static constexpr const size_t record_length = 168;
static int16_t prev_y_plot[record_length];
static int16_t prev_h_plot[record_length];
static size_t rec_record_idx = 2;
static size_t draw_record_idx = 0;
static int16_t *rec_data;*/

// MAX3010x
MAX30105 particleSensor;

const byte RATE_SIZE = 4;  //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];     //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;  //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
int temp = 0;
int beatTotalAvg = 0;
int contaBeat = 0;

// MLX90640
paramsMLX90640 mlx90640;
const byte MLX90640_address = 0x33;  // Default 7-bit unshifted address of the
#define INTERPOLATED_COLS 32
#define INTERPOLATED_ROWS 32  // MLX90640.  MLX90640的默认7位未移位地址
#define TA_SHIFT \
  8  // Default shift for MLX90640 in open air.  MLX90640在户外的默认移位

#define COLS 32
#define ROWS 24
#define COLS_2 (COLS * 2)
#define ROWS_2 (ROWS * 2)
#define I2C_SCL 1
#define I2C_SDA 2

float pixelsArraySize = COLS * ROWS;
float pixels[COLS * ROWS];
float pixels_2[COLS_2 * ROWS_2];
float reversePixels[COLS * ROWS];

byte speed_setting = 2;  // High is 1 , Low is 2
bool reverseScreen = false;

int temperature = 0;
int n_data = 0;

// low range of the sensor (this will be blue on the screen).
int MINTEMP = 24;     // For color mapping.
int min_v = 24;       // Value of current min temp.
int min_cam_v = -40;  // Spec in datasheet.

// high range of the sensor (this will be red on the screen).
int MAXTEMP = 35;     // For color mapping.
int max_v = 35;       // Value of current max temp.
int max_cam_v = 300;  // Spec in datasheet.
int resetMaxTemp = 45;