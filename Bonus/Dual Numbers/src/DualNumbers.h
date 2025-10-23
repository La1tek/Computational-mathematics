#pragma once
#include <iostream>

class DualNumbers {
  private:
    float _real;
    float _dual;
  public:
    float real() const { return _real; }
    float dual() const { return _dual; }

    DualNumbers() {
      _real = 0;
      _dual = 0;
    }

    void real(float real) { _real = real; }
    void dual(float dual) { _dual = dual; }

    DualNumbers(float real, float dual) {
      _real = real;
      _dual = dual;
    }

    DualNumbers(float real) {
      _real = real;
      _dual = 0;
    }

    DualNumbers operator+(const DualNumbers& other) {
      return DualNumbers(_real + other._real, _dual + other._dual);
    }

    DualNumbers operator-(const DualNumbers& other) {
      return DualNumbers(_real - other._real, _dual - other._dual);
    }

    DualNumbers operator*(const DualNumbers& other) {
      return DualNumbers(_real * other._real, _real * other._dual + _dual * other._real);
    }

    DualNumbers operator/(const DualNumbers& other) {
      return DualNumbers(_real / other._real, (_dual * other._real - _real * other._dual) / (other._real * other._real));
    }

    bool operator==(const DualNumbers& other) {
      return _real == other._real && _dual == other._dual;
    }

    bool operator!=(const DualNumbers& other) {
      return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os) {
      os << _real << " + " << _dual << "e";
      return os;
    }

    std::istream& operator>>(std::istream& is) {
      is >> _real >> _dual;
      return is;
    }
};