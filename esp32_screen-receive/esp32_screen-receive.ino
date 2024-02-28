/// Import required library
#include <esp_now.h>
#include <WiFi.h>

/// Setting up screen
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);


/// Structure of data receiving (must match transmitter)
typedef struct sensor_data{
  int sensor0; // sensor 1 reading
  int sensor1; // sensor 2 reading
  bool oil; // boolean true false
} sensor_data;

/// Create myData with struct sensor_data
sensor_data myData;

/// Setting up variables
int vol = 0;

/// Receive data
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  draw();
  ///Serial print for debug
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("S2: ");
  Serial.println(myData.sensor0);
  Serial.print("S1: ");
  Serial.println(myData.sensor1);
  Serial.print("Bool: ");
  Serial.println(myData.oil);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  /// ESP32-S3 T-Display need GPIO15 to be set to high for backlight
  pinMode(15,OUTPUT);
  digitalWrite(15,1);

  /// Set up before receiving data and show status (waiting for data)
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.drawString("WAITING...",10,10,4);
  sprite.createSprite(320,170);

     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 110);

  /// ESP-NOW protocol  
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void draw()
  {
    /// Getting battery information at pin 4
    vol = (analogRead(4) * 2 * 3.3 * 1000) / 4096;


    /// Print out value and data
    tft.fillScreen(TFT_BLACK); 
    tft.setTextColor(TFT_WHITE,TFT_BLACK);

    tft.drawString("SENSOR DATA",10,10,4);
    tft.drawString("Sensor 1:", 10, 40,4);
    tft.drawString(String(myData.sensor0),130,40,4);
    tft.drawString("Sensor 2:", 10, 80,4);
    tft.drawString(String(myData.sensor1),130,80,4);

    /// Boolean data give 1 if true for value over threshold, and 0 for false meaning value below threshold
    if (myData.oil == 0){
      tft.drawString("Normal Level",115,115,4);
    } else {
      tft.setTextColor(TFT_RED,TFT_BLACK);
      tft.drawString("OIL DETECTED",85,110,4);

    ///Print out battery percentage
    tft.drawString(String(vol)+" mV",10,140,4);

  }
}

void loop() {

}


