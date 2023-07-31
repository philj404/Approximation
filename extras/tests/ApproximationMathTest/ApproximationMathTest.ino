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

test(minus)
{
    Approximation piAmps(3.14159265358979, "A", 0.01);
    Approximation twoAmps(2.0, "A", 0.1);

    Approximation twoMinusPiAmps = twoAmps - piAmps;
    assertNear(twoMinusPiAmps.resolution(), 0.1, 0.00001);
    assertEqual("-1.1A", twoMinusPiAmps);

    Approximation twoVolts(2.0, "V", 0.1);
    Approximation voltsMinusAmps = twoVolts - twoAmps;
    assertEqual(voltsMinusAmps.units(), "units error");

    Approximation grossWeight(2000.0, "g", 10.);
    Approximation tareWeight(100.0, "g", 10.);
    Approximation netWeight = grossWeight - tareWeight;
    assertEqual(netWeight, "1.90kg");
}

test(minusDouble)
{
    Approximation twoAmps(2.0, "A", 0.1);

    // adding with doubles should be commutative
    auto oneAmps = twoAmps - 1.0;
    assertEqual(oneAmps, "1.0A");

    auto minusOneAmps = 1.0 - twoAmps;
    assertEqual(minusOneAmps, "-1.0A");

    auto zeroAmps = 2.0 - twoAmps;
    assertEqual(zeroAmps, "0mA");
}

test(digitsForZero)
{
    Approximation zeroAmps(0.0, "A", 0.1);
    assertEqual(zeroAmps, "0mA");

    zeroAmps.resolution(0.01);
    assertEqual(zeroAmps, "0mA");

    zeroAmps.resolution(0.001);
    assertEqual(zeroAmps, "0mA");

    zeroAmps.resolution(1.0);
    assertEqual(zeroAmps, "0A");

    zeroAmps.resolution(1000.);
    assertEqual(zeroAmps, "0kA");

    zeroAmps.resolution(1.e6);
    assertEqual(zeroAmps, "0MA");
}

test(assignFromDouble)
{
    Approximation someAmps(0.0, "A", 0.1);
    someAmps = 3.3333;
    assertEqual(someAmps, "3.3A");
}

test(multiply)
{
    const Approximation twoAmps(2.0, "A", 0.01);
    const Approximation fiveVolts(5.0, "V", 0.001);

    Approximation tenWatts = fiveVolts * twoAmps;
    assertEqual(tenWatts, "10.00VA");  //DC volt-amps is Watts

    Approximation twoMilliAmps = twoAmps * 0.001;
    assertEqual(twoMilliAmps, "2.00mA");

    Approximation twoMilliAmps2 = 0.001 * twoAmps;
    assertEqual(twoMilliAmps, "2.00mA");
}

test(timesEqualsCoarseFine)
{
    Approximation ten_Watts(2.0, "V", 0.1);              // ~2 digits
    const Approximation five_000_Amps(5.0, "A", 0.001);  // ~4 digits
    ten_Watts *= five_000_Amps;                          // *= Approximation

    assertEqual(ten_Watts, "10VA");  //DC volt-amps is Watts
}

test(timesEqualsFineCoarse)
{
    Approximation ten_Watts2(1.0, "V", 0.001);    // ~4 digits
    const Approximation tenAmps(10.0, "A", 1.0);  // ~2 digits
    ten_Watts2 *= tenAmps;                        // *= Approximation
 
    assertEqual(ten_Watts2, "10VA");  //DC volt-amps is Watts
}

test(timesEqualsDouble)
{
    Approximation tenAmps(5.0, "A", 0.001);
    assertEqual(tenAmps, "5.000A");
    tenAmps *= 2.0;  // *= double
    assertEqual(tenAmps, "10.00A");
}

test(divideEqualsDouble)
{
    Approximation tenAmps(10.0, "A", 0.001);
    assertEqual(tenAmps, "10.000A");
    tenAmps /= 10.0;  // double
    assertEqual(tenAmps, "1.0000A");

    Approximation infAmps(10.0, "A", 0.001);
    infAmps /= 0.0;
    assertEqual(infAmps, "-nanA");  // [not guaranteed?]
}

test(divideEqualsApprox)
{
    Approximation tenWatts(10.0, "W", 0.001);
    const Approximation oneAmp(1.0, "A", 0.1);
    assertEqual(tenWatts, "10.000W");
    assertEqual(oneAmp, "1.0A");

    tenWatts /= oneAmp;
    assertEqual(tenWatts, "10W/A");
}

test(divideApprox)
{
    const Approximation tenWatts(10.0, "W", 0.001);
    const Approximation oneAmp(1.0, "A", 0.1);
    assertEqual(tenWatts, "10.000W");
    assertEqual(oneAmp, "1.0A");

    Approximation oneVolt = tenWatts / oneAmp;
    assertEqual(oneVolt, "10W/A");
}

test(divideDouble)
{
    Approximation tenAmps(10.0, "A", 0.001);
    assertEqual(tenAmps, "10.000A");

    Approximation oneAmp = tenAmps / 10.0;
    assertEqual(oneAmp, "1.0000A");

    Approximation oneAmp2 = 10.0 / tenAmps;
    assertEqual(oneAmp2, "1.0000/A");
}

//----------------------------------------------------------------------------
// setup() and loop()
//----------------------------------------------------------------------------

void setup()
{
    delay(1000);           // wait for stability on some boards to prevent garbage Serial
    Serial.begin(115200);  // ESP8266 default of 74880 not supported on Linux
    while (!Serial)
        ;                  // for the Arduino Leonardo/Micro only

    Serial.println(F("Running " __FILE__ ",\nBuilt " __DATE__));
    Serial.println(F("This test should produce the following:"));
    Serial.println(
        F("EXAMPLE - SEE THE REAL ONE BELOW: <N> passed, 0 failed, 0 skipped, 0 timed out, out of <N> test(s)."));
    Serial.println(F("----"));
}

void loop()
{
    aunit::TestRunner::run();
}
