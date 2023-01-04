// Approximation library tests
//#line 2 "basic.ino"

// Adapted from:
// https://github.com/mmurdoch/arduinounit/blob/master/examples/basic/basic.ino

#include <AUnit.h>
#include "Approximation.h"

test(resolutions)
{
    Approximation a;
    a.value(3.14159265358979);

    a.resolution(0.01);
    assertEqual("3.14", a);

    a.resolution(0.0001);
    assertEqual("3.1416", a);

    a.resolution(0.1);
    assertEqual("3.1", a);
}

test(units)
{
    Approximation a(3.1416, 0.01);
    a.units("Volts");
    assertEqual("Volts", a.units());
    assertEqual("3.14 Volts", a);
}

test(engineeringNotation)
{
    Approximation a(3141.6, 10.0);
    a.units("V");
    assertEqual("V", a.units());
    assertEqual("3.14 kV", a);
}

char engUnitsFor(double aNumber)
{
    double scale;
    char unitName = '\0';
    Approximation::engUnitScaleFor(aNumber, unitName, scale);
    return unitName;
}

double engScaleFor(double aNumber)
{
    double scale;
    char unitName = '\0';
    Approximation::engUnitScaleFor(aNumber, unitName, scale);
    return scale;
}

test(engineeringUnits)
{
    assertEqual('\0', engUnitsFor(1.0));
    assertEqual('\0', engUnitsFor(10.0));
    assertEqual('\0', engUnitsFor(100.0));
    assertEqual('\0', engUnitsFor(999.999));
    assertEqual('k', engUnitsFor(1.0e3));
    assertEqual('k', engUnitsFor(1000.));
    assertEqual('k', engUnitsFor(1005.));
    assertEqual('M', engUnitsFor(1.05e6));
    assertEqual('G', engUnitsFor(1.05e9));
    assertEqual('T', engUnitsFor(1.05e12));
    assertEqual('m', engUnitsFor(1.05e-3));
    assertEqual('u', engUnitsFor(1.05e-6));
    assertEqual('n', engUnitsFor(1.05e-9));
    assertEqual('p', engUnitsFor(1.05e-12));
    assertEqual('m', engUnitsFor(-1.05e-3));
}

test(kiloPrefix)
{
    assertEqual(1000., engScaleFor(1000.));
    assertEqual(1000., engScaleFor(999999.0));

    assertEqual("k", engUnitsFor(1.0e3));
    assertEqual("k", engUnitsFor(1000.));
    assertEqual("k", engUnitsFor(1005.));
    assertEqual("k", engUnitsFor(999999.0));
}

test(engineeringScales)
{
    assertEqual(1.0, engScaleFor(1.0));
    assertEqual(1.0, engScaleFor(10.0));
    assertEqual(1.0, engScaleFor(100.0));
    assertEqual(1.0, engScaleFor(999.9));
    assertEqual(1000., engScaleFor(1000.));
    assertEqual(1.0e6, engScaleFor(1.05e6));
    assertEqual(1.0e9, engScaleFor(1.05e9));
    assertEqual(1.0e12, engScaleFor(1.05e12));
    assertEqual(1.0e-3, engScaleFor(1.05e-3));
    assertEqual(1.0e-6, engScaleFor(1.05e-6));
    assertEqual(1.0e-9, engScaleFor(1.05e-9));
    assertEqual(1.0e-12, engScaleFor(1.05e-12));
    assertEqual(1.0e-3, engScaleFor(-1.05e-3));
}

// Arduino float to String conversion examples
test(numberToString)
{
    double pi = 3.1415923535;
    assertEqual("3.14", String(pi, 2));
    assertEqual("3.1416", String(pi, 4));
    assertEqual("3.1", String(pi, 1));
    assertEqual(" 3", String(pi, 0));
    // CRASH! assertEqual("3.", String(pi, -1));
    assertEqual("3141.6", String(pi * 1000., 1));
}

test(truncateToZeros)
{
    // only show SIGNIFICANT digits
    Approximation a(314.16, 1.0);
    assertEqual("314", a);
    a.resolution(10.0);
    assertEqual("310", a);
    a.resolution(100.0);
    assertEqual("300", a);
    a.resolution(0.1);
    assertEqual("314.2", a);
}

test(showTrailingZeros)
{
    Approximation b(10.0, 0.1);
    assertEqual("10.0", b);
    b.resolution(0.01);
    assertEqual("10.00", b);
}

test(roundBy5s)
{
    // only show SIGNIFICANT digits
    Approximation a(1. / 3., 0.5);
    assertEqual("500 m", a);  // round up
    a.value(0.249);
    assertEqual(" 0", a);
    a.value(0.251);
    assertEqual("500 m", a);
}

test(roundBy2s)
{
    // only show SIGNIFICANT digits
    Approximation a(1. / 3., 0.2);
    assertEqual("400 m", a);  // round up
    a.value(0.099);
    assertEqual(" 0", a);
    a.value(0.101);
    assertEqual("200 m", a);
}

test(negativeValues)
{
    Approximation a(-10. / 3., 0.2);
    assertEqual("-3.4", a);  // round to nearest

    a.value(-10.e3 / 3.0);
    a.resolution(100.);
    assertEqual("-3.3 k", a);
}

test(inchesToMeters)
{
    Approximation inInches(100.0, "inches", 100.);
    //inInches.units("inches");

    auto inMeters = inInches.convertFromTo(1.0, "inches", 0.0254, "meters");

    assertEqual(" 3 meters", inMeters);  // round to nearest
}

test(metersToInches)
{
    Approximation inMeters(10.0, "meters", 10.);
    //inMeters.units("meters");

    auto inInches = inMeters.convertFromTo(1.0, "meters", 39.37, "inches");

    assertEqual("400 inches", inInches);  // round to nearest
}

test(milesToKilometers)
{
    Approximation inMiles(100.0, "miles", 100.);
    //inMiles.units("miles");

    auto inMeters = inMiles.convertFromTo(1.0, "miles", 1609., "m");

    assertEqual("200 km", inMeters);  // round to nearest
}

test(lightningStrikeDistance)
{
    // convert distance to lightning strike from FLASH to BOOM sound
    // speed of sound is about 1 mile in 5 seconds
    // timing lightning flash to Approximation inSeconds(3.0, 100.);
    Approximation inSeconds(6.0, 0.5);
    inSeconds.units("s");

    auto inMiles = inSeconds.convertFromTo(5.0, "s", 1.0, "miles");

    assertEqual("1.2 miles", inMiles);  // round to nearest
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
    Serial.println(F("This test should produce the following:"));
    Serial.println(
        F("EXAMPLE - SEE THE REAL ONE BELOW: 15 passed, 0 failed, 0 skipped, 0 timed out, out of 15 test(s)."));
    Serial.println(F("----"));
}

void loop()
{
    aunit::TestRunner::run();
}
