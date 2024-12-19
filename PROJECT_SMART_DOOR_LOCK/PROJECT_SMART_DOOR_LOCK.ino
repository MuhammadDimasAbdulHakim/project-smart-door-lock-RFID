/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  NOTE: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6FE6Wmr7N"
#define BLYNK_TEMPLATE_NAME "pintu pintar RF ID"
#define BLYNK_AUTH_TOKEN "LE4yvHFSp065WPy7JFsPUI7tULIpXZYS"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "msdimskuyy";
char pass[] = "masdimas";


#define SS_PIN 4  // sda
#define RST_PIN 2
 
int lock = D1;    
 
MFRC522 mfrc522(RST_PIN, SS_PIN);   


SimpleTimer timer;
int fflag = 0; 
int eflag = 0; 
int jflag = 0; 
WidgetTerminal terminal(V2);

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(lock,OUTPUT);
      digitalWrite(lock, LOW);
        SPI.begin();                // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        //Serial.println("Scan a MIFARE Classic PICC to demonstrate Value Blocks.");
          timer.setInterval(1000L, iot_rfid);

}

void loop()
{
  timer.run();
  Blynk.run();
}
void iot_rfid()
{
 
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                return;
        }
 
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print("Card UID:");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
               Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(mfrc522.uid.uidByte[i], DEC);
        } 
        Serial.println();
 
        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    //    Serial.print("PICC type: ");
//Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                //Serial.println("This sample only works with MIFARE Classic cards.");
                return;
        }
        
        // Enter RFID Tag ID here 
        if( ((mfrc522.uid.uidByte[0] == 80) && (mfrc522.uid.uidByte[1] == 175) && (mfrc522.uid.uidByte[2] == 218) && (mfrc522.uid.uidByte[3] == 26)) && (fflag == 1) )
        {
         Serial.println("User01");   //Enter User1 Name
         Blynk.virtualWrite(V2, "KARTU PUTIH 1 " );   //Enter User1 Name
         digitalWrite(lock, HIGH); 
         delay(3000); 
         digitalWrite(lock, LOW); 
        }
  
        else
        if(( (mfrc522.uid.uidByte[0] == 163) && (mfrc522.uid.uidByte[1] == 244) && (mfrc522.uid.uidByte[2] == 116) && (mfrc522.uid.uidByte[3] == 14))&& (eflag == 1) )
        {
         Serial.println("User02");   //Enter User2 Name 
         Blynk.virtualWrite(V2, "TAG 1" );   //Enter User2 Name
         digitalWrite(lock, HIGH); 
         delay(3000); 
         digitalWrite(lock, LOW); 
        }
        else
        if( ((mfrc522.uid.uidByte[0] == 21) && (mfrc522.uid.uidByte[1] == 22) && (mfrc522.uid.uidByte[2] == 23) && (mfrc522.uid.uidByte[3] == 24))&& (jflag == 1) )
        {
         Serial.println("User03");   //Enter User3 Name
         Blynk.virtualWrite(V2, "User03" );   //Enter User3 Name
         digitalWrite(lock, HIGH); 
         delay(3000); 
         digitalWrite(lock, LOW); 
        }
 
        else 
        Serial.println("Unregistered User");
  
}
 
// in Blynk app writes values to the Virtual Pin 3
BLYNK_WRITE(V3)
{
   fflag = param.asInt(); // assigning incoming value from pin V3 to a variable
  // Blynk.virtualWrite(V2, fflag );
 
}
 
 
// in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V4)
{
   eflag = param.asInt(); // assigning incoming value from pin V4 to a variable
 
}
 
BLYNK_WRITE(V5)
{
   jflag = param.asInt(); // assigning incoming value from pin V5 to a variable
 
}


