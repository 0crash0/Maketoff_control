
#include "ESP8266.h"

#define SSID        "ESP"
#define PASSWORD    "12345678"
#define CHANNEL     7
#define ENCRYPTION  0 //0 - OPEN, 1 - WEP, 2 - WPA_PSK, 3 - WPA2_PSK, 4 - WPA_WPA2_PSK
#define IPap        "192.168.1.1"
ESP8266 wifi(Serial1, 115200);

char *hello_msg = "Hello, this is server!";

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
			if ((String)convert(buffer) == (String)"1"){
				digitalWrite(4, HIGH);
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

char *convert(uint8_t *a)
{
	int buffer1[128];
	char buffer2[128];
	int i;
	char *buffer_pointer;

	buffer1[127] = '\0';

	for (i = 0; i <= 126; i++)
		buffer1[126 - i] = (((*a) >> i)&(0x01));

	for (i = 0; i <= 126; i++)
		buffer2[i] = buffer1[i] + '0';

	buffer2[127] = '\0';

	puts(buffer2);

	buffer_pointer = buffer2;

	return buffer_pointer;
}
