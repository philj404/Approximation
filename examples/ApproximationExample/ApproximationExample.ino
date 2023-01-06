// Approximation library tests
//#line 2 "basic.ino"

// Adapted from:
// https://github.com/mmurdoch/arduinounit/blob/master/examples/basic/basic.ino

//#include <AUnit.h>
#include <Arduino.h>
#include "Approximation.h"

void printValueAndApproximation(double value, const Approximation& estimate) {
  Serial.print(value, 7);
  Serial.print(F(" rounded to the nearest "));
  Serial.print(estimate.resolution(), 6);
  Serial.print(F(" is approximately: "));
  Serial.println(estimate);
}

void demoCoarseResolutions(void) {
  Serial.println(F("Show values track their resolution"));

  static const double pi = 3.14159265358979;

  // constructor
  Approximation estimateOfPi(pi, 1.e-6);

  // typical syntax
  estimateOfPi.value(pi);          // sets value
  estimateOfPi.resolution(1.e-6);  // sets resolution

  for (double currentResolution = 1.e-6; currentResolution <= 1.0; currentResolution *= 10) {

    estimateOfPi.resolution(currentResolution);

    printValueAndApproximation(pi, estimateOfPi);
  }
  Serial.println();

  static const double oneThird = 1.0 / 3.0;
  Approximation aboutOneThird(oneThird, 0.01);
  printValueAndApproximation(oneThird, aboutOneThird);
  Serial.println();

  static const double twoThirds = 2.0 / 3.0;
  Approximation aboutTwoThirds(twoThirds, 0.01);
  printValueAndApproximation(twoThirds, aboutTwoThirds);
  Serial.println();
}

void demoUnits(void) {
  Serial.println(F("Show units with value"));

  Approximation adcOutput(50, 1.0);
  adcOutput.units("dac-counts");

  Serial.print(F("ADC output is: "));
  Serial.println(adcOutput);

  Approximation aVoltage(1.5, 0.1);
  aVoltage.units("Volts");

  Serial.print(F("This voltage is: "));
  Serial.println(aVoltage);
}
//----------------------------------------------------------------------------
// setup() and loop()
//----------------------------------------------------------------------------

void setup() {
  delay(1000);           // wait for stability on some boards to prevent garbage Serial
  Serial.begin(115200);  // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ;  // for the Arduino Leonardo/Micro only

  Serial.println(F("Running " __FILE__ ",\nBuilt " __DATE__));

  demoCoarseResolutions();
  // demoFixedPointResolutions();
  // demoScientificNotation();
  // demoEngineeringNotation();
  // demoUnitConversions();
  // demoApproximationMath();
  demoUnits();
}

void loop() {
  //aunit::TestRunner::run();
}
