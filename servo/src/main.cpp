#include <Arduino.h>
#include <ESP32Servo.h>
Servo servo;

const int initialAngle = 0;
const int maxAngle = 180;
int currentAngle = initialAngle;
int direction = 1;

void setup() {
    Serial.begin(9600);
    delay(100);
    Serial.println("Seting up...");
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    servo.setPeriodHertz(50);
    servo.attach(25);
    servo.write(initialAngle);
    delay(100);
    Serial.println("Setup done.");
}

void loop()
{
    int increment = 10;
    int nSteps = maxAngle/increment;

    currentAngle += direction * increment;

    if ((currentAngle > maxAngle) || (currentAngle < initialAngle))
    {
        direction *= -1;
        currentAngle += direction * increment;
    }

    servo.write(currentAngle);

    Serial.print("Angle = ");
    Serial.println(currentAngle);

    delay(200);
}
