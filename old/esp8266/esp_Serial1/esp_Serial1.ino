#define WIFI_SERIAL Serial1
 
#define DEBUG_SERIAL Serial
 
void setup() {
 
    DEBUG_SERIAL.begin(115200); // start the two serial ports
 
    WIFI_SERIAL.begin(115200);
 
    delay(3000); // we need a delay to make sure the ESP8266 has booted up
 
    //WIFI_SERIAL.println("AT+RST"); // send it a reset command, we should get some data back
 
    // We'll add some extra code here soon
 
}
 
void loop() {
 
    if (WIFI_SERIAL.available()) {
 
        char c = WIFI_SERIAL.read(); // read from the ESP8266
 
        DEBUG_SERIAL.write(c); // write to the USB serial port
 
    }
    if (DEBUG_SERIAL.available()) {
 
        char c = DEBUG_SERIAL.read(); // read from the ESP8266
 
        WIFI_SERIAL.write(c); // write to the USB serial port
 
    }
 
}
