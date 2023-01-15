// Approximation Units demo
//
#include <Arduino.h>
#include <Approximation.h>

void demoUnits(void)
{
    Serial.println(F("Show units with value"));
    Serial.println();

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

    demoUnits();
}

void loop()
{
}
