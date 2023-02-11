// Approximation library tests

#include <Arduino.h>
#include <Approximation.h>

void printValueAndApproximation(double value, const Approximation& estimate)
{
    Serial.print(value, 7);
    Serial.print(F(" rounded to the nearest "));
    Serial.print(estimate.resolution(), 6);
    Serial.print(F(" is approximately: "));

    Serial.println(estimate);
}

void demoCoarseResolutions(void)
{
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
    auto hundredPi = pi * 100.;
    Approximation about100pi(pi * 100., 10.);
    printValueAndApproximation(hundredPi, about100pi);
    Serial.println();

    static const double oneThird = 1.0 / 3.0;
    Approximation aboutOneThird(oneThird, 0.01);
    printValueAndApproximation(oneThird, aboutOneThird);
    //Serial.println();

    static const double twoThirds = 2.0 / 3.0;
    Approximation aboutTwoThirds(twoThirds, 0.01);
    printValueAndApproximation(twoThirds, aboutTwoThirds);
    Serial.println();
}

void demoUnits(void)
{
    Serial.println(F("Show units with value"));

    Approximation power(50, 0.01);
    power.units("W");

    Serial.print(F("Power is: "));
    Serial.println(power);

    Approximation speedOfSound(331.29, 0.1);
    speedOfSound.units("m/s");

    Serial.print(F("The speed of sound in dry air at 0 degrees C is about: "));
    Serial.println(speedOfSound);
    Serial.println();

    Approximation orbitalSpeedAtEquator(7.1e3, 100.);
    orbitalSpeedAtEquator.units("m/s");

    Serial.print(F("Low orbit speed at equator is about: "));
    Serial.println(orbitalSpeedAtEquator);
    Serial.println();
}

void demoUnitConversions(void)
{
    Serial.println(F("Unit conversion -- ADC-counts to Volts"));

    Approximation adcInput(125, 1.0);
    adcInput.units("adc-counts");

    Approximation voltage = adcInput.convertFromTo(250., "adc-counts", 5.0, "V");

    Serial.print(F("ADC input is: "));
    Serial.print(adcInput);
    Serial.print(F("; this is equivalent to: "));
    Serial.println(voltage);
    Serial.println();
}
//----------------------------------------------------------------------------
// setup() and loop()
//----------------------------------------------------------------------------

void setup()
{
    delay(1000);           // wait for stability on some boards to prevent garbage Serial
    Serial.begin(115200);  // ESP8266 default of 74880 not supported on Linux
    while (!Serial)
        ;  // for the Arduino Leonardo/Micro only

    Serial.println(F("Running " __FILE__ ",\nBuilt " __DATE__));

    demoCoarseResolutions();
    // demoFixedPointResolutions();
    // demoScientificNotation();
    // demoEngineeringNotation();
    demoUnitConversions();
    // demoApproximationMath();
    demoUnits();
}

void loop()
{
}
