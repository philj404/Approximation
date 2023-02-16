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
    Approximation(const Approximation& a);

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

    // auto convert to double?
    // operator double() const;

    // assignment
    Approximation& operator=(double d);
    Approximation& operator=(const Approximation& a);

    // relational
    bool operator==(double d) const;
    bool operator==(const Approximation& a) const;
    bool operator!=(double d) const;
    bool operator!=(const Approximation& a) const;
    bool operator>(double d) const;
    bool operator>(const Approximation& a) const;
    bool operator<(double d) const;
    bool operator<(const Approximation& a) const;
    bool operator>=(double d) const;
    bool operator>=(const Approximation& a) const;
    bool operator<=(double d) const;
    bool operator<=(const Approximation& a) const;

    // binary arithmetic - for example a+b
    //Approximation& operator+(double d) const;
    //Approximation& operator+(const Approximation& a) const;
    Approximation& operator-(double d) const;
    Approximation& operator-(const Approximation& a) const;
    Approximation& operator*(double d) const;
    Approximation& operator*(const Approximation& a) const;
    Approximation& operator/(double d) const;
    Approximation& operator/(const Approximation& a) const;

    // assignment
    Approximation& operator+=(double d);
    Approximation& operator-=(double d);
    Approximation& operator*=(double d);
    Approximation& operator/=(double d);
    Approximation& operator+=(const Approximation& a);
    Approximation& operator-=(const Approximation& a);
    Approximation& operator*=(const Approximation& a);
    Approximation& operator/=(const Approximation& a);

    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend Approximation operator+(Approximation lhs,         // passing lhs by value helps optimize chained a+b+c
                                   const Approximation& rhs)  // otherwise, both parameters may be const references
    {
        lhs += rhs;
        return lhs;
    }

    friend Approximation operator+(double lhs,         // passing lhs by value helps optimize chained a+b+c
                                   Approximation rhs)  // otherwise, both parameters may be const references
    {
        rhs += lhs;
        return rhs;
    }

    friend Approximation operator+(Approximation lhs,
                                   double rhs)
    {
        return operator+(rhs, lhs);  // commutative property
    }
    
    // unary arithmetic (-a)
    Approximation operator-() const;


  private:
    bool unitsMatch(const Approximation& rhs) const;

    enum CompareResult { Less,
                         AboutEqual,
                         Greater,
                         Error };
    CompareResult compare(double lhs, double rhs, double tolerance) const;
    CompareResult compare(const Approximation& rhs) const;
    CompareResult compare(double rhs) const;

    // note floats have at most 6 significant digits!
    float _requested;
    float _actual;
    float _resolution;
    String _units;
};