By flashing wifi_mac_get.ino and open Serial terminal with BAUD rate 115200 we can get the print out of MAC Address for further use with ESP-NOW protocol (direct communication between ESP32s)

Lilygo ESP32-S3 T-Display MAC: C0:4E:30:02:6C:70

Adafruit ESP32-S3 Feather MAC: DC:54:75:DA:70:F0

esp32_screen_receive for Lilygo ESP32-S3 T-Display
esp32_sensor_send for Adafruit ESP32-S3 Feather

ESP32-S3 feather wiring:
- Both GND from sensor connected to GND on microcontroller board.
- Both VDD from sensor connected to 3.3V on microcontroller board.
- Data line of sensors connected to A0 and A1 respectively.

Battery is 1100mAh x4 connected in parralel to maintain the Voltage output of 3.7V.

Both microcontroller have battery controller chip so they can be charged directly through the USB-C port on the microcontroller.