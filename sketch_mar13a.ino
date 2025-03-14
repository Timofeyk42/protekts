#include "WiFi.h"
#include "esp_camera.h"
#include <HTTPClient.h>

// Конфигурация GPIO-пинов для AI-Thinker ESP32-CAM
#define PWDN_GPIO_NUM    32
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      21
#define Y4_GPIO_NUM      19
#define Y3_GPIO_NUM      18
#define Y2_GPIO_NUM       5

#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

// Настройки Wi-Fi точки доступа устройства
const char* ssid = "dkiss"; // SSID точки доступа устройства
const char* password = "deniska33"; // Пароль точки доступа
const char* URL = "http://....."

void setup() {
  Serial.begin(115200);

  // Инициализация камеры
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_SVGA; // Разрешение 800 × 600
    config.jpeg_quality = 10;          // Высокое качество JPEG
    config.fb_count = 2;               // Два буфера кадров
  } else {
    config.frame_size = FRAMESIZE_VGA; // Разрешение 640 × 480
    config.jpeg_quality = 12;          // Хорошее качество JPEG
    config.fb_count = 1;               // Один буфер кадров
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  Serial.println("Camera initialized successfully");

  // Подключение к точке доступа устройства
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  sensor_t * img = esp_camera_sensor_get();

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(URL);
    http.addHeader("Content-Type", "image/jpeg");

    int httpResponseCode = http.POST(img);  
  
    if(httpResponseCode>0){
      String response = http.getString();                      
      Serial.println(httpResponseCode);  
      Serial.println(response);           
    }else{
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
   }
  }

void loop() {
  // Пустой цикл, так как отправка происходит только один раз при запуске
}