#include <ESP32Servo.h>

// Pin konfigurasi
#define pirPin 5       // Pin PIR
#define ledPin 2       // Pin LED
#define servoPin 4     // Pin Servo
#define trigPin 12     // Pin Trig Ultrasonik
#define echoPin 14     // Pin Echo Ultrasonik

Servo myServo;

void setup() {
  // Inisialisasi pin
  pinMode(pirPin, INPUT);  
  pinMode(ledPin, OUTPUT); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  // Inisialisasi servo
  myServo.attach(servoPin);
  myServo.write(0);

  Serial.begin(115200);    
}

void loop() {
  // Membaca status PIR
  int pirState = digitalRead(pirPin);  

  // Membaca jarak dari sensor ultrasonik
  float distance = getUltrasonicDistance();

  // Log hasil
  Serial.print("PIR State: ");
  Serial.print(pirState);
  Serial.print(", Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (pirState == HIGH && distance < 30) {  
    // Jika ada gerakan dan jarak < 50 cm
    digitalWrite(ledPin, HIGH);  
    Serial.println("Hama Burung Terdeteksi");

    unsigned long startTime = millis();  
    while (millis() - startTime < 15000) {  
      myServo.write(90);  // Servo bergerak
      delay(200);       
      myServo.write(0);   // Servo kembali
      delay(200);       
    }

    myServo.write(0);

  } else {
    // Tidak ada gerakan atau objek terlalu jauh
    digitalWrite(ledPin, LOW);  
    Serial.println("Tidak Ada Hama atau Objek Terlalu Jauh");
  }

  delay(1000); // Tunggu 1 detik sebelum loop berikutnya
}

// Fungsi untuk membaca jarak dari sensor ultrasonik
float getUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);  // Waktu pulsa dalam mikrodetik
  float distance = duration * 0.034 / 2;  // Konversi ke cm
  return distance;
}
