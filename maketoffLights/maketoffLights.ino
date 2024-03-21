#include "ESP8266.h"
#include "Arduino.h"

/* ESP DEFENITION */
#define SSID        "ESP"
#define PASSWORD    "12345678"
#define CHANNEL     7
#define ENCRYPTION  0 //0 - OPEN, 1 - WEP, 2 - WPA_PSK, 3 - WPA2_PSK, 4 - WPA_WPA2_PSK
#define IPap        "192.168.1.1"
ESP8266 wifi(Serial, 115200);
/*END ESP DEFENITION */

/*PORTS DEFINEITION*/
int pinIN[8] = {8,12,13,A0,A1,A2,A3,A4};

int pinOUT[8] = {2,3,4,5,6,9,10,11};

int pUOTdig[2]={2,4};
int pOUTwPWM[6] = {3,5,6,9,10,11};
int RGB1[3] = { 6, 5, 3 };
int RGB2[3] = { 11, 10, 9 };
/*END PORT DEFENITION*/


/**/
char *hello_msg = "Hello, this is server!";

char *cm1 = "1tst";
char *cm2 = "2tst";
char *cm3 = "3tst";
char *cm4 = "4tst";
char *cm5 = "5tst";
char *cm6 = "6tst";
char *cm7 = "7tst";
char *cm8 = "8tst";

char *rgbCM = "A_";



String cmdS[8]={cm1,cm2,cm3,cm4,cm5,cm6,cm7,cm8};
String rgbCMD(rgbCM);

bool cmdsSTT[8] = {false,false,false,false,false,false,false,false};


bool btnS[8] = {false,false,false,false,false,false,false,false};

/**/
void setup() {
  // put your setup code here, to run once:
  int i;
  for(i=0;i<=sizeof(pinIN);i++){
    pinMode(pinIN[i], INPUT);
  }
  
  for(i=0;i<=sizeof(pinOUT);i++){
    pinMode(pinOUT[i], OUTPUT);
  }
  for(i=0;i<=sizeof(pinOUT);i++){
    //delay(100);
    digitalWrite(pinOUT[i], HIGH);
    delay(100);
    digitalWrite(pinOUT[i], LOW);
  }
  //delay(5000);
	Serial.begin(115200);
	wifi.setOprToSoftAP();
	wifi.setSoftAPParam(SSID, PASSWORD, CHANNEL, ENCRYPTION);
	wifi.setAPip(IPap);
	wifi.enableMUX();
	wifi.setTCPIPmode(0);
	wifi.startTCPServer(3000);
	wifi.setTCPServerTimeout(100);
}

void loop() {
   /* readBtns();
	Btnlight();*/


	uint8_t buffer[128] = { 0 };
	uint8_t mux_id;
	uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);

	if (len > 0) {

		String bff(reinterpret_cast<char*>(buffer));

		for (int i = 0; i <= sizeof(cmdS); i++){
			if (bff == cmdS[i])
			{
				
				if (cmdsSTT[i] == false){
					digitalWrite(pinOUT[i], HIGH);
					cmdsSTT[i] = true;
				}
				else{
					digitalWrite(pinOUT[i], LOW);
					cmdsSTT[i] = false;
				}
			}
		}
		

               

		wifi.send(mux_id, (const uint8_t*)hello_msg, strlen(hello_msg));

	}
}

/*void readBtns(){
	for (int i = 0; i <= sizeof(pinIN); i++){
		btnS[i] = digitalRead(pinIN[i]);
	}
}

void Btnlight(){
	for (int i = 0; i <= sizeof(pinIN); i++){
		if (btnS[i] != cmdsSTT[i]){
			if (cmdsSTT[i] == false){
				digitalWrite(pinOUT[i], HIGH);
				cmdsSTT[i] = true;
			}
			else{
				digitalWrite(pinOUT[i], LOW);
				cmdsSTT[i] = false;
			}
		}
		
	}
}*/