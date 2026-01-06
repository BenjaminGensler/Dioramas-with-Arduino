#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini dfPlayer;
Servo servo_9;

const int fireplaceLED = 5;

int pos = 0;

void setup() {
  Serial.begin(9600); 
  mySoftwareSerial.begin(9600);

  Serial.println("Initializing DFPlayer Mini...");

  if (!dfPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1. Please recheck the connection!"));
    Serial.println(F("2. Please insert the SD card!"));
    while(true);
  }

  dfPlayer.volume(20);
  dfPlayer.EQ(DFPLAYER_EQ_NORMAL);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  delay(500);

  dfPlayer.play(11);

  Serial.println("Playing file...");

  servo_9.attach(9, 500, 2500); // Attach servo to pin 9

  pinMode(fireplaceLED, OUTPUT);
}

void loop() {

  // Flicker fireplace LED
  int flicker = random(50, 255); // random brightness
  delay(200);
  analogWrite(fireplaceLED, flicker);

  // Sweep servo from 45° to 135°
  for (pos = 80; pos <= 170; pos += 1) {
    servo_9.write(pos);
    delay(15);
    analogWrite(fireplaceLED, random(50, 255)); // flicker during sweep
  }
  for (pos = 170; pos >= 80; pos -= 1) {
    servo_9.write(pos);
    delay(15);
    analogWrite(fireplaceLED, random(50, 255)); // flicker during sweep
  }
}
