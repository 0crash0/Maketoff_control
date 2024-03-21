#include "ESP8266.h"
#include "Arduino.h"

#define SSID        "ESP"
#define PASSWORD    "12345678"
#define CHANNEL     7
#define ENCRYPTION  0 //0 - OPEN, 1 - WEP, 2 - WPA_PSK, 3 - WPA2_PSK, 4 - WPA_WPA2_PSK
#define IPap        "192.168.1.1"
ESP8266 wifi(Serial1, 115200);

char *hello_msg = "Hello, this is server!";

char *cm1 = "1tst";
char *cm2 = "2tst";
char *cm3 = "3tst";
char *cm4 = "4tst";
char *cm5 = "5tst";

String cmd1(cm1);
String cmd2(cm2);
String cmd3(cm3);
String cmd4(cm4);
String cmd5(cm5);

bool cm1st = false;
bool cm2st = false;
bool cm3st = false;
bool cm4st = false;
bool cm5st = false;

bool btn1 = false;
bool btn2 = false;
bool btn3 = false;

void setup(void)
{
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);

	pinMode(10, INPUT);
	pinMode(11, INPUT);
	pinMode(12, INPUT);

	for (int i = 4; i <= 9; i++){
		delay(100);
		digitalWrite(i, HIGH);
		delay(900);
		digitalWrite(i, LOW);
	}
	delay(5000);
	Serial.begin(115200);
	Serial.print("setup begin\r\n");

	Serial.print("FW Version:");
	Serial.println(wifi.getVersion().c_str());

	if (wifi.setOprToSoftAP()) {
		Serial.print("to station + softap ok\r\n");
	}
	else {
		Serial.print("to station + softap err\r\n");
	}

	if (wifi.setSoftAPParam(SSID, PASSWORD, CHANNEL, ENCRYPTION)) {
		Serial.print("Start AP success\r\n");
		Serial.print("IP: ");
		Serial.println(wifi.getLocalIP().c_str());
	}
	else {
		Serial.print("Start AP failure\r\n");
	}

	if (wifi.setAPip(IPap)) {
		Serial.print("set IP ok\r\n");
	}
	else {
		Serial.print("set IP err\r\n");
	}

	if (wifi.enableMUX()) {
		Serial.print("multiple ok\r\n");
	}
	else {
		Serial.print("multiple err\r\n");
	}

	if (wifi.setTCPIPmode(0)) {
		Serial.print("set tcp/ip mode ok\r\n");
	}
	else {
		Serial.print("set tcp/ip mode err\r\n");
	}

	if (wifi.startTCPServer(3000)) {
		Serial.print("start tcp server ok\r\n");
	}
	else {
		Serial.print("start tcp server err\r\n");
	}

	if (wifi.setTCPServerTimeout(100)) {
		Serial.print("set tcp server timout 10 seconds\r\n");
	}
	else {
		Serial.print("set tcp server timout err\r\n");
	}

	Serial.print("setup end\r\n");
}

void loop(void)
{
	readBtns();
	Btnlight();
	digitalWrite(9, HIGH);

	uint8_t buffer[128] = { 0 };
	uint8_t mux_id;
	uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
	if (len > 0) {
		Serial.print("Status:[");
		Serial.print(wifi.getIPStatus().c_str());
		Serial.println("]");

		Serial.print("Received: ");

		for (uint32_t i = 0; i < len; i++){
			Serial.print((char)buffer[i]);
		}
		String bff(reinterpret_cast<char*>(buffer));

		if (bff == cmd1){
			digitalWrite(4, HIGH);
		}

		if (bff == cmd1){
			if (cm1st == false){
				digitalWrite(4, HIGH);
				cm1st = true;
			}
			else{
				digitalWrite(4, LOW);
				cm1st = false;
			}
		}
		else if (bff == cmd2){
			if (cm2st == false){
				digitalWrite(5, HIGH);
				cm2st = true;
			}
			else{
				digitalWrite(5, LOW);
				cm2st = false;
			}
		}
		else if (bff == cmd3){
			if (cm3st == false){
				digitalWrite(6, HIGH);
				cm3st = true;
			}
			else{
				digitalWrite(6, LOW);
				cm3st = false;
			}
		}
		else if (bff == cmd4){
			if (cm4st == false){
				digitalWrite(7, HIGH);
				cm4st = true;
			}
			else{
				digitalWrite(7, LOW);
				cm4st = false;
			}
		}
		else if (bff == cmd5){
			if (cm5st == false){
				for (int i = 4; i < 8; i++){
					digitalWrite(i, LOW);
				}
				cm5st = true;
			}
			else{
				for (int i = 4; i < 8; i++){
					digitalWrite(i, HIGH);
				}
				cm5st = false;
			}
		}


		if (wifi.send(mux_id, (const uint8_t*)hello_msg, strlen(hello_msg))) {
			Serial.print("send back ok\r\n");
		}
		else {
			Serial.print("send back err\r\n");
		}

		/*       if (wifi.releaseTCP(mux_id)) {
		Serial.print("release tcp ");
		Serial.print(mux_id);
		Serial.println(" ok");
		} else {
		Serial.print("release tcp");
		Serial.print(mux_id);
		Serial.println(" err");
		}
		*/
		Serial.print("Status:[");
		Serial.print(wifi.getIPStatus().c_str());
		Serial.println("]");
	}
}

void readBtns(){
	btn1 = digitalRead(10);
	btn2 = digitalRead(11);
	btn1 = digitalRead(12);
}

void Btnlight(){
	if (btn1){
		digitalWrite(4, HIGH);
	}
	if (btn2){
		digitalWrite(5, HIGH);
	}
	if (btn3){
		digitalWrite(6, HIGH);
	}
}


