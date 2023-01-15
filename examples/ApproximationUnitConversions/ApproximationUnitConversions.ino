// Approximation unit conversion demo

#include <Arduino.h>
#include <Approximation.h>

void demoUnitConversions(void)
{
    Serial.println(F("Unit conversion -- ADC-counts to Volts"));

    Approximation adcInput(125, 1.0);
    adcInput.units("adc-counts");

    // 8-bit ADC; 50 mV per ADC count (calibrated so 250 counts => 5.0V)
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

    demoUnitConversions();
}

void loop()
{
}
