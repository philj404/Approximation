# Approximation
An Approximation library for Arduino.

This library provides support for "coarse" numeric values.  These values track how many digits are significant.  Conversion to strings avoids showing distracting unimportant digits.

Approximations track their units.  For example values may be in "Volts" or "miles/gallon"

Output values also support engineering notation. They round the exponent to the nearest group of three.

### Why would I want this? 
Here is an example which illustrates why approximations can round off digits which are not really significant:

The aircraft carrier _USS Enterprise_ gets ready to leave port.  It is fully loaded, and weighs 32,600 Tons. Lieutenant Jimmy boards the ship.  He weighs 72.5kg, and is carrying a sandwich (455g), coffee (455g), and a poundcake (455g).

- How much does the Enterprise weigh after Jimmy goes on board? 32,600 Tons -- _Jimmy's extra weight is not significant for the aircraft carrier._
- How much does Jimmy weigh after eating lunch? About 74kg.  _Jimmy's weight has increased. We do not know his weight to the nearest gram, and we should not imply that we do._

### How to use:
Include the library:
```cpp
#include <Approximation.h>
```

Create an approximation:
```cpp
...
Approximation about3volts;
about3volts.value(3.0);
about3volts.resolution(0.1);
about3volts.units("V");
...
```
Convert the Approximation to a string (for printing):
```cpp
...
String output = about3volts.asString();
Serial.println(output); // print the string

Serial.println(about3volts); // OR automatic conversion to String
...
```

### Example Sketches

- ApproximationCoarseResolutions
 - Demonstrates printing coarse resolutions
- ApproximationUnitConversions
 - Demonstrates converting units, for example adc-counts to Volts
- ApproximationUnits
 - Demonstrates units with the approximation, for example "Watts"

### Tips

### Notes

