#include <ESP32Servo.h>

#define pirPin 5  
#define ledPin 2
#define servoPin1 4  // Servo pertama
#define servoPin2 15 // Servo kedua

Servo myServo1;
Servo myServo2;

void setup() {
  pinMode(pirPin, INPUT);  
  pinMode(ledPin, OUTPUT); 
  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);
  
  myServo1.write(0);
  myServo2.write(0);
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
      myServo1.write(90);  
      myServo2.write(90);  
      delay(200);        

      myServo1.write(0);  
      myServo2.write(0);  
      delay(200);        
    }

    myServo1.write(0);
    myServo2.write(0);

  } else {
    // Jika tidak ada gerakan
    digitalWrite(ledPin, LOW);  
    Serial.println("Tidak Ada Hama");
  }

  delay(1000); 
}
