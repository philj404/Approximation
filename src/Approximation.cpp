// Approximation.cpp
#include <Arduino.h>
#include "Approximation.h"

Approximation::Approximation(double val, double res)
    : Approximation(val, "", res){};

Approximation::Approximation(void)
    : Approximation(0.0, 1.e-6){};

Approximation::Approximation(double aValue, const String& units, double aResolution)
{
    _resolution = aResolution;
    value(aValue);
    _units = units;
};

void Approximation::units(const String& units)
{
    _units = units;
}

String Approximation::units(void) const
{
    return _units;
}

void Approximation::resolution(double res)
{
    _resolution = res;
    value(_requested);  // recalculate actual
}

double Approximation::resolution(void) const
{
    return _resolution;
}

void Approximation::value(double v)
{
    _requested = v;
    _actual = rounded(_requested, _resolution);  // rounded approximation
}

double Approximation::value(void) const
{
    return _actual;
}

double Approximation::rounded(double requested, double resolution)
{
    double quantized = floor(requested / resolution + 0.5);
    double value = quantized * resolution;
    return value;
}

struct ScaleAndName {
    float scale;
    char prefix;
};

const ScaleAndName scales[] = {
    { 1.0e12, 'T' },
    { 1.0e9, 'G' },
    { 1.0e6, 'M' },
    { 1.0e3, 'k' },
    { 1.0, '\0' },
    { 1.0e-3, 'm' },
    { 1.0e-6, 'u' },
    { 1.0e-9, 'n' },
    { 1.0e-12, 'p' },
    { 0.0, '\0' }
};

void Approximation::engUnitScaleFor(double aValue, char& siPrefix, double& siScale)
{
    auto positiveValue = fabs(aValue);
    siPrefix = '\0';
    siScale = 1.0;

    static const int numScales = (sizeof(scales)/sizeof(ScaleAndName));
    for (int i = 0; i < numScales; i++) {
        auto aScale = scales[i];
        if (positiveValue >= aScale.scale) {
            siPrefix = aScale.prefix;
            siScale = aScale.scale;
            return;
        }
    }
}

String Approximation::asString(void) const
{
    // note the underlying float has at most 6 significant digits!
    int numDigits = 1;
    float ratio = fabs(_actual / _resolution);
    while (ratio >= 10.) {
        numDigits++;
        ratio /= 10.;
    }

    char engUnit = '\0';
    double normalizeUnit = 1.0;
    engUnitScaleFor(_actual, engUnit, normalizeUnit);

    auto digitsAfterDecimal = numDigits;
    float displayActual = fabs(_actual / normalizeUnit);
    if (displayActual >= 100.) {
        digitsAfterDecimal -= 3;
    } else if (displayActual >= 10.) {
        digitsAfterDecimal -= 2;
    } else {
        digitsAfterDecimal -= 1;
    }
    
    displayActual = _actual / normalizeUnit; // signed
    if (digitsAfterDecimal < 0) {
        //auto coarseResolution = _resolution / normalizeUnit;
        auto coarseResolution = (digitsAfterDecimal < -1) ? 100. : 10.;
        displayActual = rounded(displayActual, coarseResolution);
        digitsAfterDecimal = 0;
    }

    String s(displayActual, digitsAfterDecimal);
    if ((engUnit != 0) || (_units[0] != 0)) {
        s += F(" ");
        if (engUnit) { s += engUnit; }
        s += _units;
    }
    return s;
}

// to convert an approximation to different units
// example: // speed of sound is about 340 m/s
//Approximation distanceInMeters = distanceInSeconds.convertFromTo(1.0, "s", 340., "m");
Approximation Approximation::convertFromTo(double fromVal, const String& fromUnits, double toVal, const String& toUnits) const
{
    auto conversionFactor = toVal / fromVal;
    Approximation converted(_requested * conversionFactor, toUnits, _resolution * conversionFactor);

    if (_units == fromUnits) {
    } else {
        converted.units("conversion error");
    }
    return converted;
}
