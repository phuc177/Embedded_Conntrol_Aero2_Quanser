#include <SPI.h>
#include <math.h>
// Quanser Aero library
#include "Aero.h"  
#include "ACSI_aero_lib.h"

/*                     IMPORTANT INFORMATION

Accessible global variables (just use them):
These are the variables that already be defined in QUBE Servo library, 
you don't need to define them again in this file

    - Input variables (you can get them after readSensors() function):
        float yaw;          // yaw angle position in radians

    - Output variables (you can send them by driveMotor() function):
        float motor0Voltage;   // Signal sent to the motor 0 in Volts
        float motor1Voltage;   // Signal sent to the motor 1 in Volts
*/

/* DECLARE GLOBAL VARIABLES HERE IF NEEDED */
float Ts = 0.002; // second
float yaw_desired = PI/6;
float yaw_read;
float MotorVoltage_calc;
float motorVoltagePrev2 = 0;
float motorVoltagePrev  = 0;
    
float yaw_desiredPrev2 = 0;
float yaw_desiredPrev  = 0;
    
float yaw_readPrev2 = 0;
float yaw_readPrev  = 0;
float yaw_error = 0;
float yaw_errorPrev = 0;
float yawErrorRateFilter = 0;
float yawErrorRateFilterPrev = 0;
float Kp = 200;
float Kd = 100;
float alpha = Ts*20 / (1 + 20*Ts);

int NumLoopCnt = 0; // Loop counter for changing reference
int NumLoop = 3000; // Number of loop to change the reference

volatile bool controlCalc = false;

// Interrupt service routine
ISR(TIMER1_COMPA_vect)
{
  OCR1A += 32000; // Advance The COMPA Register
  // 2 ms sampling time
  controlCalc = true;
}

/*-----------------------------------------*/

//This function will be called once during initialization
void setup() {
  // Timer setup
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000001;  // Prescalar = 64
  OCR1A = 32000;        // Timer CompareA Register
  TIMSK1 |= B00000010;  // Enable Timer Overflow Interrupt
  
  // Set the slaveSelectPin as an output
  pinMode(slaveSelectPin, OUTPUT);

  // Initialize SPI
  SPI.begin();

  // Initialize serial communication at 250000 baud
  Serial.begin(250000);
}

// This function will be called repeatedly until Arduino is reset
void loop() {
  // Serial plotter
  Serial.print(millis());
  Serial.print(",");
  Serial.print(yaw);
  Serial.print(",");
  Serial.print(motor1Voltage);
  Serial.print(",");
  Serial.println(yaw_desired);
  
  // After 3000 loops, change the yaw_desired = -yaw_desired (for students)
  if (NumLoopCnt == NumLoop) {
    yaw_desired = -yaw_desired;
    NumLoopCnt = 0;
  }
  NumLoopCnt ++;

  // Reset after the Arduino power is cycled or the reset pushbutton is pressed
  if (startup) {
    resetQuanserAero();
    startup = false;
  }

  // initialize the SPI bus using the defined speed, data order and data mode
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE2));
  // take the slave select pin low to select the device
  digitalWrite(slaveSelectPin, LOW);

  // read the sensors
  readSensors();
  yaw_read = yaw;
  yaw_error = yaw_desired - yaw_read;

  if (controlCalc == true) {
    // PID Controller (for students)
    yawErrorRateFilter = alpha*(yaw_error - yaw_errorPrev)/Ts + (1 - alpha)*yawErrorRateFilterPrev;  
    motor1Voltage = Kp*yaw_error + Kd*yawErrorRateFilter; 

    // RST Controller
    // motor1Voltage =
    //   1.967 * motorVoltagePrev
    // - 0.967 * motorVoltagePrev2

    // + 0.01481 * yaw_desired
    // + 0.02962 * yaw_desiredPrev
    // + 0.01481 * yaw_desiredPrev2

    // - 4151.0 * yaw_read
    // + 8278.0 * yaw_readPrev
    // - 4127.0 * yaw_readPrev2;

    // The variable "motor0Voltage" and "motor1Voltage" is saturated within the range of -24V to 24V. (for students)
    if (motor1Voltage > 24) {
      motor1Voltage = 24;
    }
    else if (motor1Voltage < -24) {
      motor1Voltage = -24;
    }

    // Update histories
    motorVoltagePrev2 = motorVoltagePrev;
    motorVoltagePrev  = motor1Voltage;
    
    yaw_desiredPrev2 = yaw_desiredPrev;
    yaw_desiredPrev  = yaw_desired;
    
    yaw_readPrev2 = yaw_readPrev;
    yaw_readPrev  = yaw_read;
  
    yawErrorRateFilterPrev = yawErrorRateFilter;
    yaw_errorPrev = yaw_error;

    motor0Voltage = - motor1Voltage;
    
    // drive motor
    driveMotor();
    controlCalc = false;
  }
  // take the slave select pin high to de-select the device
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
}
