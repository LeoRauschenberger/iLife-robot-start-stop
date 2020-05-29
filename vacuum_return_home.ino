//Vacuum home by  Leo Rauschenberger 
//sends vacuum robot home at specific time

#include <IRremote.h>
#include <virtuabotixRTC.h>

IRsend irsend;

int A_hour=7;
int A_minute=25;

int var;

virtuabotixRTC myRTC(6, 7, 8);

void setup() {
  Serial.begin(9600);
  // Set the current date, and time in the following format:
  // 1. seconds 
  // 2. minutes 
  // 3. hours
  //
  // 4. day of the week
  // 5. day of the month
  //
  // 6. month
  // 7. year
  // myRTC.setDS1302Time(00, 11, 16, 6, 17, 8, 2019);
  pinMode(13, OUTPUT);                                                  
}

void loop() {
  myRTC.updateTime();
  // RTC sends time to serial every 30 seconds
  //Serial.print(myRTC.hours);                                                                              
  //Serial.print(":");                         acce                                                            
  //Serial.println(myRTC.minutes);
  // delay(60000);

  // Tell the vacuum to go back to where it came from at preset time:
  if(myRTC.hours==A_hour && myRTC.minutes==A_minute){
    digitalWrite(13, LOW);   // LED is off
    var = 0;
    while(var < 30){
        digitalWrite(13, HIGH);   // turn the LED on
        irsend.sendNEC(0x2AA8877,32);
        myRTC.updateTime();  // get current time
        Serial.print(myRTC.hours);                                                                              
        Serial.print(":");                                                                                     
        Serial.print(myRTC.minutes);  
        Serial.print(":");                                                                                     
        Serial.print(myRTC.seconds); 
        Serial.println(" -> Call robot Home");
        delay(4000); //wait 4 seconds
         var++;
    }
  }
  else{digitalWrite(13, LOW);   // LED is off
  }
}
