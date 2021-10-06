#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position



//temp hu
#include "Adafruit_Si7021.h"

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_Si7021 sensor = Adafruit_Si7021();
//temp hu

String data;
char clr;

void setup() {
  Serial.begin(57600);
  //Serial.println("start");
  myservo.attach(4);
  
  //temp hu
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  //Serial.println("Si7021 test!");
  
  if (!sensor.begin()) {
    //Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

//temp hu-----------------------------------








  
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(7, OUTPUT);
pinMode(9, INPUT);
pinMode(8, INPUT);

}
void loop(){
int pir = digitalRead(9);
int gas = digitalRead(8);
  //Serial.print("Humidity:    ");
Serial.println(sensor.readTemperature());  
Serial.println(sensor.readHumidity());
 // Serial.print("\tTemperature: ");

Serial.println(gas);
Serial.println(pir);




  delay(50);

  // Toggle heater enabled state every 30 seconds
  // An ~1.8 degC temperature increase can be noted when heater is enabled
  if (++loopCnt == 30) {
    enableHeater = !enableHeater;
    sensor.heater(enableHeater);
    //Serial.print("Heater Enabled State: ");
    if (sensor.isHeaterEnabled()){
      //Serial.println("ENABLED");
      }
    else{
     // Serial.println("DISABLED");
    }
    loopCnt = 0;
  }




digitalWrite(7, LOW);
if(Serial.available()>0)
   { 
      digitalWrite(7, HIGH);
      clr= Serial.read(); // reading the data received from the bluetooth module
      data +=clr;
      if(clr=='\n'){
        
       // Serial.println(data);

        
      switch(data[0])
      {
        case 'a': digitalWrite(2, HIGH);break; // when a is pressed on the app on your smart phone
        case 'x': digitalWrite(2, LOW);break; // when d is pressed on the app on your smart phone
        default : break;
      }
      switch(data[1])
      {
        case 'b': digitalWrite(3, HIGH);break; // when a is pressed on the app on your smart phone
        case 'x': digitalWrite(3, LOW);break; // when d is pressed on the app on your smart phone
        default : break;
      }
      switch(data[2])
      {
        case 'c':   myservo.write(180);break; // when a is pressed on the app on your smart phone
        case 'x': myservo.write(0);break; // when d is pressed on the app on your smart phone
        default : break;
      }
      data="";
      delay(30);
      }
   }
delay(30);

}
