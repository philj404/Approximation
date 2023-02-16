// Approximation library tests -- math operators

// Adapted from:
// https://github.com/mmurdoch/arduinounit/blob/master/examples/basic/basic.ino

#include <AUnit.h>
#include "Approximation.h"

test(plusEqualsApprox)
{
    Approximation sixSeconds(6.0, "s", 0.1);
    Approximation aboutSixSeconds(6.01, "s", 0.5);

    Approximation aboutTwelveSeconds(sixSeconds);
    aboutTwelveSeconds += aboutSixSeconds;
    assertTrue(aboutTwelveSeconds == 12.0);
    assertEqual(aboutTwelveSeconds.resolution(), 0.5);

    Approximation oneMinuteAndSixSeconds(1.0, "min", 0.01);
    oneMinuteAndSixSeconds += sixSeconds;
    assertEqual("units error", oneMinuteAndSixSeconds.units());
}

test(plusEqualsDouble)
{
    Approximation fivePlusOneSeconds(5.0, "s", 0.5);
    fivePlusOneSeconds += 1.0;
    assertTrue(fivePlusOneSeconds == 6.0);
}

test(plus)
{
    Approximation piAmps(3.14159265358979, "A", 0.01);
    Approximation twoAmps(2.0, "A", 0.1);

    Approximation twoPlusPiAmps = twoAmps + piAmps;
    assertNear(twoPlusPiAmps.resolution(), 0.1, 0.00001);
    assertEqual("5.1A", twoPlusPiAmps);

    Approximation twoVolts(2.0, "V", 0.1);
    Approximation voltsPlusAmps = twoVolts + twoAmps;
    assertEqual(voltsPlusAmps.units(), "units error");
}

test(plusDouble)
{
    Approximation twoAmps(2.0, "A", 0.1);

    // adding with doubles should be commutative
    auto threeAmps = twoAmps + 1.0;
    assertEqual(threeAmps, "3.0A");

    auto fourAmps = 2.0 + twoAmps;
    assertEqual(fourAmps, "4.0A");
}

test(negation)
{
    Approximation twoAmps(2.0, "A", 0.1);
    auto minusTwoAmps = -twoAmps;

    assertEqual(minusTwoAmps, "-2.0A");
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
        F("EXAMPLE - SEE THE REAL ONE BELOW: 16 passed, 0 failed, 0 skipped, 0 timed out, out of 16 test(s)."));
    Serial.println(F("----"));
}

void loop()
{
    aunit::TestRunner::run();
}
