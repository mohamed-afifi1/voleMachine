#include "VoleMachine.h"


string ALU::intToBinary(int integerPart) {
    string binary = "";
    if (integerPart == 0) return "0";

    while (integerPart > 0) {
        binary = (integerPart % 2 == 0 ? "0" : "1") + binary;
        integerPart /= 2;
    }
    return binary;
}

string ALU::fracToBinary(float fractionalPart, int precision) {
    string binary = "";
    while (fractionalPart > 0 || precision > 0) {
        fractionalPart *= 2;
        if (fractionalPart >= 1) {
            binary += "1";
            fractionalPart -= 1;
        }
        else {
            binary += "0";
        }
        precision--;
    }
    return binary;
}

string ALU::floatToBinary(float num) {
    int integerPart = static_cast<int>(num);
    double fractionalPart = num - integerPart;

    string binaryInteger = intToBinary(integerPart);
    string binaryFraction = fracToBinary(fractionalPart);

    return binaryFraction.empty() ? binaryInteger : binaryInteger + "." + binaryFraction;
}

float ALU::fromhextofloat(string hex) {
    int num = hextodec(hex);
    bitset<8> bs(num);
    string str = bs.to_string();
    int sign = str[0] == '1' ? -1 : 1;
    string exponent = str.substr(1, 3);
    string mantissa = str.substr(4);
    int expo = stoi(exponent, nullptr, 2);
    int mant = stoi(mantissa, nullptr, 2);
    float result = sign * pow(2, expo - 4) * (mant / 16.0);
    return result;
}

string ALU::fromfloattohex(float num) {
    int sign = (num < 0) ? 1 : 0;
    if (num > 7.5) {
        num = 7.5;
    }
    if (num < -7.5) {
        num = -7.5;
    }
    num = abs(num);
    string mantissa;
    int exp = 0;
    string binary_val = floatToBinary(num);
    auto it = find(binary_val.begin(), binary_val.end(), '.');

    if (num > 1.0) {
        exp = it - binary_val.begin();
        mantissa += binary_val.substr(0, exp);
        mantissa += binary_val.substr(exp + 1, 4 - exp);
    }
    else {
        int val = it - binary_val.begin();
        int indx = 0;
        for (int i = val + 1; i < binary_val.size(); ++i) {
            if (binary_val[i] == '1') {
                indx = i;
                break;
            }
            --exp;
            if (exp == -4) {
                indx = i + 1;
                break;
            }

        }
        mantissa = binary_val.substr(indx, 4);

    }

    int biasedexp = exp + 4;

    string binaryStr = bitset<1>(sign).to_string()
        + bitset<3>(biasedexp).to_string()
        + mantissa;
    int val = stoi(binaryStr, nullptr, 2);
    return dectohex(val);
}

int ALU::hextodec(const string& s) {
    int value = 0;
    int base = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        int val = 0;
        if (s[i] >= '0' && s[i] <= '9') {
            val = s[i] - '0';
        }
        else {
            if (s[i] >= 'a' && s[i] <= 'f') {
                val = (s[i] - 'a') + 10;
            }
            else {
                if (s[i] >= 'A' && s[i] <= 'F') {
                    val = (s[i] - 'A') + 10;
                }
            }
        }
        value += val * pow(16, base);
        base++;
    }
    return value;
}

string ALU::dectohex(int res) {
    string result;
    while (res > 0) {
        int value = res % 16;
        if (value < 10) {
            result += to_string(value);
        }
        else {
            result += char('A' + (value - 10));
        }
        res /= 16;
    }
    reverse(result.begin(), result.end());
    return result;
}

void ALU::add(int regstore, int firstReg, int secndReg, Regester& reg) {
    int val1 = hextodec(reg.getcell(firstReg));
    if (val1 > 127) {
        val1 -= 256;
    }
    int val2 = hextodec(reg.getcell(secndReg));
    if (val2 > 127) {
        val2 -= 256;
    }
    int result = val1 + val2;
    if (result < 0) {
        result += 256;
    }
    string res = dectohex(result);
    if (res.size() == 1)
        res = "0" + res;
    else if (res.size() == 0)
        res = "00" + res;
    reg.setcell(regstore, res);
}

void ALU::addFloat(int regstore, int firstReg, int secndReg, Regester& reg) {
    float val1 = fromhextofloat(reg.getcell(firstReg));
    float val2 = fromhextofloat(reg.getcell(secndReg));
    float result = (val1 + val2);
    string res = fromfloattohex(result);
    if (res.size() == 1)
        res = "0" + res;
    else if (res.size() == 0)
        res = "00" + res;
    reg.setcell(regstore, res);
}

void ALU::bitwise_Or(int regstore, int firstReg, int secndReg, Regester& reg) {
    int val1 = hextodec(reg.getcell(firstReg));
    int val2 = hextodec(reg.getcell(secndReg));
    int result = (val1 | val2);
    string res = dectohex(result);
    if (res.size() == 1)
        res = "0" + res;
    else if (res.size() == 0)
        res = "00" + res;
    reg.setcell(regstore, res);
}

void ALU::bitwise_And(int regstore, int firstReg, int secndReg, Regester& reg) {
    int val1 = hextodec(reg.getcell(firstReg));
    int val2 = hextodec(reg.getcell(secndReg));
    int result = (val1 & val2);
    string res = dectohex(result);
    if (res.size() == 1)
        res = "0" + res;
    else if (res.size() == 0)
        res = "00" + res;
    reg.setcell(regstore, res);
}

void ALU::bitwise_Xor(int regstore, int firstReg, int secndReg, Regester& reg) {
    int val1 = hextodec(reg.getcell(firstReg));
    int val2 = hextodec(reg.getcell(secndReg));
    int result = (val1 ^ val2);
    string res = dectohex(result);
    if (res.size() == 1)
        res = "0" + res;
    else if (res.size() == 0)
        res = "00" + res;
    reg.setcell(regstore, res);
}

void ALU::rotate(int regNum, int number_of_rotations, Regester& reg) {
    int num = hextodec(reg.getcell(regNum));
    bitset<8> bs(num);
    string str = bs.to_string();
    number_of_rotations %= 8;
    for (int i = 1; i <= number_of_rotations; ++i) {
        str = str.back() + str;
        str.pop_back();
    }
    int val = stoi(str, nullptr, 2);
    string res = dectohex(val);
    if (res.size() == 1)
        res = "0" + res;
    else if (res.size() == 0)
        res = "00" + res;
    reg.setcell(regNum, res);
    
}

bool ALU::jump_to_location(int regnum, Regester& reg) {
    int val1 = hextodec(reg.getcell(regnum));
    if (val1 > 127) {
        val1 -= 256;
    }
    int val2 = hextodec(reg.getcell(0));
    if (val2 > 127) {
        val2 -= 256;
    }
    return val1 > val2;
}
