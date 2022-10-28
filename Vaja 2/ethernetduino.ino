/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3 and 4  in a single ThingSpeak update every 20 seconds.
  
  Hardware: Arduino Ethernet
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
 - Requires the Ethernet library
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/

#include <Ethernet.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros


#define vhodAD A1 //senzor temp
#define vhodSv A0 //svetlost temp


byte mac[] = SECRET_MAC;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values SEM GRE KODA ZA TEMP IN SVETL
int number1 = 0;
int number2 = 0;

float getTemp(){
  // read the input on analog pin 0:
  float sensorValue = (analogRead(A1) + 20.0); //A0 - svetloba, A1 - temperatura, +20 je za kalibracijo temperature
  // print out the value you read:
  float napetost = sensorValue * (5000/1023);
  float temp = napetost - 400;
  temp = temp / 19.5;
  //Serial.println(temp);
  delay(250);        // delay in between reads for stability
  return temp;
  }



void setup() {
  Ethernet.init(10);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
      
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  
  // set the fields with the values
  ThingSpeak.setField(1, getTemp());
  ThingSpeak.setField(2, analogRead(vhodSv));
  //ThingSpeak.setField(3, number3);
  //ThingSpeak.setField(4, number4);

    
  // write to the ThingSpeak channel 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  Serial.println(getTemp());

  
  delay(20000); // Wait 20 seconds to update the channel again
}
