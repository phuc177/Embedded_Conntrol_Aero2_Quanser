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


/*-----------------------------------------*/

//This function will be called once during initialization
void setup() {
  // Set the slaveSelectPin as an output
  pinMode(slaveSelectPin, OUTPUT);

  // Initialize SPI
  SPI.begin();

  // Initialize serial communication at 250000 baud
  Serial.begin(250000);

}

// This function will be called repeatedly until Arduino is reset
void loop() {
  // After 3000 loops, change the theta_desired = -theta_desired (for students)
  

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

  // PID Controller (for students)
  

  // The variable "motor0Voltage" and "motor1Voltage" is saturated within the range of -24V to 24V. (for students)


  // drive motor
  driveMotor();
  

  delay(Ts*1000);
  // take the slave select pin high to de-select the device
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
}
