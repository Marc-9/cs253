#include "Ratio.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::cerr;
using std::cout;
using std::ifstream;
using std::runtime_error;

int main() {
    Ratio f12(-2,-4), f34(3L,4L), seven_eights = Ratio(7).divide(Ratio(8));
    const Ratio f78(seven_eights), one(f34.divide(f34));
    assert(f12.numerator() == 1);
    assert(f12.denominator() == 2);
    assert(f12.ratio() == 0.5);
    assert(f34.ratio() == 0.75);
    assert(f78.ratio() == 0.875);
    assert(f12.add(f34).multiply(f78).ratio() == 1.09375);
    assert(f12.ratio() == 0.5);
    assert(f34.ratio() == 0.75);
    assert(f78.ratio() == 0.875);
    assert(Ratio(1,5).add(Ratio(1,7)).compare(Ratio(12,35)) == 0);

    assert(f12.compare(f34) < 0);
    assert(f34.compare(f12) > 0);
    assert(f34.compare(Ratio(-66,-88)) == 0);
    assert(f12.add(f34).compare(Ratio(5,4)) == 0);
    assert(f12.add(f34).ratio() == 1.25);
    assert(f12.add(f34).compare(1.25L) == 0);
    assert(f12.add(f34, f78, f12, f34, f78).ratio() == 4.250);
    assert(f34.add(one,one,one,one,one,one,one,one).ratio() == 8.75);

    Ratio r(42, 666);
    r.numerator(0);
    r.numerator(700);
    r.denominator(-3000);
    assert(r.numerator() == -7);
    assert(r.denominator() == 30);

    cout << "Should be |-7/30|: |" << r << "|\n";
    ifstream in("data");
    if (!in) {
        cerr << "Can’t open data\n";
        return 1;
    }
    while (in >> r)
        cout << "»»» " << r << '\n';

    try {
        r.denominator(0);
        cout << "Should not get here.\n";
    }
    catch (const runtime_error &err) {
        cout << "Error detected: "  << err.what() << '\n';
    }

 
    return 0;
}
