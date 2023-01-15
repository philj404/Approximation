// Approximation resolution demo

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
}

void loop()
{
}
