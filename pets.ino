#include <ESP32Servo.h>



#define pirPin 5  
#define ledPin 2
#define servoPin 4

Servo myServo;

void setup() {
  pinMode(pirPin, INPUT);  
  pinMode(ledPin, OUTPUT); 
  pinMode(servoPin, OUTPUT);
  myServo.attach(servoPin);
  myServo.write(0);
  Serial.begin(115200);    
}

void loop() {
  int pirState = digitalRead(pirPin);  

  if (pirState == HIGH) {
    // Jika ada gerakan
    digitalWrite(ledPin, HIGH);  
    Serial.println("Hama Terdeteksi");


    unsigned long startTime = millis();  
    while (millis() - startTime < 15000) {  
      myServo.write(90);  
      delay(1000);       
      myServo.write(0);  
      delay(1000);       
    }

    myServo.write(0);

  } else {
    // Jika tidak ada gerakan
    digitalWrite(ledPin, LOW);  
    Serial.println("Tidak Ada Hama");
  }

  delay(1000); 
}
