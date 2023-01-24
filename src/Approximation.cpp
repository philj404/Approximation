// Approximation.cpp
#include <Arduino.h>
#include "Approximation.h"

Approximation::Approximation(double val, double res)
    : Approximation(val, "", res){};

Approximation::Approximation(void)
    : Approximation(0.0, 1.e-6){};

Approximation::Approximation(double aValue, const String& units, double aResolution)
{
    _resolution = fabs(aResolution);
    value(aValue);
    _units = units;
};

Approximation::Approximation(const Approximation& a)
{
    _requested = a._requested;
    _actual = a._actual;
    _resolution = a._resolution;
    _units = a._units;
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
    _resolution = fabs(res);
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

    for (int i = 0; scales[i].scale != 0.0; i++) {
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

    displayActual = _actual / normalizeUnit;  // signed
    if (digitsAfterDecimal < 0) {
        //auto coarseResolution = _resolution / normalizeUnit;
        auto coarseResolution = (digitsAfterDecimal < -1) ? 100. : 10.;
        displayActual = rounded(displayActual, coarseResolution);
        digitsAfterDecimal = 0;
    }

    String s(displayActual, digitsAfterDecimal);
    if ((engUnit != 0) || (_units[0] != 0)) {
        //s += F(" ");
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

Approximation::CompareResult Approximation::compare(double lhs, double rhs, double tolerance) const
{
    if (lhs < (rhs - tolerance))
        return Less;
    if (lhs > (rhs + tolerance))
        return Greater;
    return Equal;  // about equal
}

bool Approximation::unitsMatch(const Approximation& rhs) const
{
    return units() == rhs.units();
}

Approximation::CompareResult Approximation::compare(const Approximation& rhs) const
{
    if (!unitsMatch(rhs))
        return Error;  // throw exception?

    double res = max(resolution(), rhs.resolution());
    return compare(value(), rhs.value(), res);
}

Approximation::CompareResult Approximation::compare(double rhs) const
{
    return compare(value(), rhs, resolution());
}

bool Approximation::operator==(double d) const
{
    return compare(d) == Equal;
};
bool Approximation::operator==(const Approximation& a) const
{
    return compare(a) == Equal;
};

bool Approximation::operator!=(double d) const
{
    return compare(d) != Equal;
};
bool Approximation::operator!=(const Approximation& a) const
{
    return compare(a) != Equal;
};

bool Approximation::operator<=(double d) const
{
    return compare(d) != Greater;
};
bool Approximation::operator<=(const Approximation& a) const
{
    return compare(a) != Greater;
};

bool Approximation::operator<(double d) const
{
    return compare(d) == Less;
};
bool Approximation::operator<(const Approximation& a) const
{
    return compare(a) == Less;
};

bool Approximation::operator>(double d) const
{
    return compare(d) == Greater;
};
bool Approximation::operator>(const Approximation& a) const
{
    return compare(a) == Greater;
};

bool Approximation::operator>=(double d) const
{
    return compare(d) != Less;
};
bool Approximation::operator>=(const Approximation& a) const
{
    return compare(a) != Less;
};