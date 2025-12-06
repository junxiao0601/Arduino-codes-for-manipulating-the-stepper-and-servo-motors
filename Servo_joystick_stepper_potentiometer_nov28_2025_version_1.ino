#include <Servo.h>
#include <Stepper.h>
// Potentiometer for the stepper motor
//Pin connection
int potPin = A2;

int previousVal = 0;
int currentVal;

// Stepper Motor
//Steps for full 360-degree rotation, change to fit your motor
int stepsPerRevolution = 2048;

//Set a speed for the stepper motor
int rpm = 10;

//Initializing the stepper library on pins 7, 6, 5, 4
//pin-order IN1 IN2 IN3 IN4
Stepper myStepper (stepsPerRevolution, 7, 6, 5, 4);

// Micro Servo
int xPin = A0;
int yPin = A1;

int xVal;
int yVal;

int xServoPin = 9;
int yServoPin = 10;

int xServoPos;
int yServoPos;

Servo xServo;
Servo yServo;


void setup() {
  //Stepper
  myStepper.setSpeed(rpm);

  // put your setup code here, to run once:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  
  xServo.attach(xServoPin);
  yServo.attach(yServoPin);
}

void loop() {
  // Stepper with Potentiometer
  currentVal = analogRead(potPin);
  //int previousSteps = map(previousVal, 0, 1023, 0, 2048);
  //int currentSteps = map(currentVal, 0, 1023, 0, 2048);

  int stepSpeed = map(currentVal, 0, 1023, 0, 17);

  //change the # of step as change in potentiometer reading
  //myStepper.step((currentSteps - previousSteps));
  //previousVal = currentVal;
  if (stepSpeed > 0){
    myStepper.setSpeed(stepSpeed);
    //step 1/100 of a revolution
    myStepper.step(stepsPerRevolution/100);
  }

  // put your main code here, to run repeatedly:
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);

  // target = map(source, lowSource, highSource, lowTarget, highTarget)

  xServoPos = map(xVal, 0, 1023, 0, 180);
  yServoPos = map(yVal, 0, 1023, 0, 180);

  xServo.write(xServoPos);
  yServo.write(yServoPos);
}
