// Approximation.h -- An *approximation* of a number value
//
// it has some idea of how many of its digits are significant
#include <Arduino.h>

class Approximation
{
  public:
    Approximation(void);
    Approximation(double aValue, double aResolution);
    Approximation(double aValue, const String& units, double aResolution);
    void value(double aValue);
    void value(double aValue, double resolution);
    double value(void) const;
    void resolution(double aResolution);
    double resolution(void) const;
    void units(const String& units);
    String units(void) const;

    static double rounded(double aVal, double aResolution);
    static void engUnitScaleFor(double aVal, char& siName, double& siScale);
    String asString(void) const;

    // example: auto inMeters = inInches.convert(1, "inches", 0.0254, "meters");
    Approximation convertFromTo(double fromVal, const String& fromUnits, double toVal, const String& toUnits) const;

    operator String() const
    {
        return asString();
    };

    // TODO add operators:
    // (assign) =, +=, -=, *=, /=
    // +, -, *, / (doubles and Approximation)
    // convert to double?


  private:
    // note floats have at most 6 significant digits!
    float _requested;
    float _actual;
    float _resolution;
    String _units;
};