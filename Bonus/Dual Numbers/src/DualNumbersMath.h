#pragma once
#include <cmath>

namespace dual {

DualNumbers exp(const DualNumbers& x) {
    return DualNumbers(std::exp(x.real()), std::exp(x.real()) * x.dual());
}

DualNumbers log(const DualNumbers& x) {
    return DualNumbers(std::log(x.real()), x.dual() / x.real());
}

DualNumbers sin(const DualNumbers& x) {
    return DualNumbers(std::sin(x.real()), std::cos(x.real()) * x.dual());
}

DualNumbers cos(const DualNumbers& x) {
    return DualNumbers(std::cos(x.real()), -std::sin(x.real()) * x.dual());
}

DualNumbers sqrt(const DualNumbers& x) {
    float r = std::sqrt(x.real());
    return DualNumbers(r, x.dual() / (2 * r));
}

DualNumbers pow(const DualNumbers& x, float y) {
    if (y == 0) {
        return DualNumbers(1, 0);
    }
    return DualNumbers(std::pow(x.real(), y), y * std::pow(x.real(), y - 1) * x.dual());
}

} // namespace dual
