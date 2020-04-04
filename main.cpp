#include <iostream>
#include <stdexcept>
#include <set>
#include <map>

int NOD(int a, int b) {
    if (b==0) throw std::invalid_argument("Denominator cannot be zero");
    if (a==b or a==0){ return 1;}
    if (a<b) {
        int x=b;
        b=a;
        a=x;
    }
    for (;;){
        a -= b * (a / b);
        if (a == 0){ return b;}
        b -= a * (b / a);
        if (b == 0){ return a;}
    }
}

class Rational {
private:
    int ch_;
    int zn_;
public:
    Rational(int ch = 0, int zn = 1) {
        if (zn == 0) throw std::invalid_argument("Denominator cannot be zero");
        ch_ = ch / NOD(ch, zn);
        zn_ = zn / NOD(ch, zn);
        if (zn_ < 0) {
            ch_ *= -1;
            zn_ *= -1;
        }
        if (ch_ == 0) zn_ = 1;
    }

    ~Rational(){}
    int GetCh() const { return ch_; }
    int GetZn() const { return zn_; }

    Rational operator+(const Rational& b) {
        ch_ = (ch_ * b.zn_) + (b.ch_ * zn_);
        zn_ = zn_ * b.zn_;
        return Rational(ch_, zn_);
    }
    Rational operator-(const Rational& b) {
        ch_ = (ch_ * b.zn_) - (b.ch_ * zn_);
        zn_ = zn_ * b.zn_;
        return Rational(ch_, zn_);
    }
    Rational operator*(const Rational& b) {
        ch_ *= b.ch_;
        zn_ *= b.zn_;
        return Rational(ch_, zn_);
    }
    Rational operator/(const Rational& b) {
        ch_ *= b.zn_;
        zn_ *= b.ch_;
        return Rational(ch_, zn_);
    }

    bool operator<(const Rational& b) const { return (ch_ * (b.zn_) < (b.ch_) * zn_); }
    bool operator>(const Rational& b) const { return (ch_ * (b.zn_) > (b.ch_) * zn_); }
    bool operator==(const Rational& b) const { return (ch_ * (b.zn_) == (b.ch_) * zn_); }

    double cast_double() { return static_cast<double>(GetCh()) / GetZn(); }
    float cast_float() { return static_cast<float>(GetCh()) / static_cast<float >(GetZn()); }
};

std::ostream& operator<<(std::ostream& os, const Rational &b){
    return os << b.GetCh() << " " << b.GetZn();
}
std::istream& operator>>(std::istream& in, Rational& b) {
    int ch = 0;
    int zn = 0;
    in >> ch;
    in.ignore(1);
    in >> zn;
    b = Rational{ch, zn};
    return in;
}

int main(){
    const Rational a = Rational(1, 2) + Rational(1, 3) - Rational(1, 4);
    if (a == Rational(7, 12)) {
        std::cout << "equal" << std::endl;
    }

    const Rational b = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
    if (b == Rational(2, 3)) {
        std::cout << "equal" << std::endl;
    }

    Rational c;
    std::cout << "Input please" << std::endl;
    std::cin >> c; // тут с консоли пользователь ввел `1 2`
    std::cout << c << std::endl; // тут в консоль вывело 1/2.

    Rational d(1, 2);
    std::cout << d.cast_double() << std::endl;

    std::set<Rational> rationals;
    rationals.insert(Rational(1, 2));
    rationals.insert(Rational(1, 3));
    std::map<Rational, std::string> name;
    name[Rational(1, 2)] = "одна вторая";
    return 0;
}
