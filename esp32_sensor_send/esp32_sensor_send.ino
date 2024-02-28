/// Import needed library
#include <esp_now.h>
#include <WiFi.h>

/// Define threshold for warning
const int threshold = 1700;

/// Setting up receiver address (MAC Address)
uint8_t receiverAdd[] = {0xC0, 0x4E, 0x30, 0x02, 0x6C, 0x70};
esp_now_peer_info_t peerInfo;

String sta;

/// Structure of data sending (must match receiver)
typedef struct sensor_data{
  int sensor0; // sensor 1 reading
  int sensor1; // sensor 2 reading
  bool oil; // boolean true false
} sensor_data;

/// Create myData with struct sensor_data
sensor_data myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if(status == ESP_NOW_SEND_SUCCESS) 
  sta="Delivery Success"; else sta="Delivery Fail";
}

void setup() {
  /// Init ESP-NOW
  WiFi.mode(WIFI_STA);
  esp_now_init();
  /// Get status of the transmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  /// Register peer
  memcpy(peerInfo.peer_addr, receiverAdd, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  /// Add peer
  esp_now_add_peer(&peerInfo);
 
}


void loop() {
  ///Read data and put in myData
  myData.sensor0 = analogRead(A0);
  myData.sensor1 = analogRead(A1);

  ///If the data is above threshold send boolean TRUE
  if (myData.sensor0 > threshold | myData.sensor1 > threshold)
  {
   myData.oil = true; 
  } else myData.oil = false;

  ///Send data
  esp_err_t result = esp_now_send(receiverAdd, (uint8_t *) &myData, sizeof(myData));

  ///Serial output for debugging
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  ///Serial print for debugging
  Serial.println(myData.sensor0);

  ///Delay between data transfer
  delay(1000);
}
