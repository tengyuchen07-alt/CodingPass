#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;

class HugeInt
{
public:
    int size;
    int* digit;

    // quotient = dividend / divisor; remainder = dividend % divisor
    // provided that dividend != 0, divisor != 0 and dividend >= divisor
    void division(HugeInt divisor, HugeInt& quotient, HugeInt& remainder);

    // hugeInt /= 10, or equivalently, shifts right by one position
    void divideBy10();

    // minuend -= subtrahend
    // provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
    void subtraction(HugeInt subtrahend);

    // returns true if and only if hugeInt1 < hugeInt2
    // provided that hugeInt1 != 0 and hugeInt2 != 0
    bool less(HugeInt hugeInt2);

    // return true if and only if hugeInt1 == hugeInt2
    // provided that hugeInt1 != 0 and hugeInt2 != 0
    bool equal(HugeInt hugeInt2);

    // returns true if and only if the specified huge integer is zero
    bool isZero();
};

const int arraySize = 250;

int main()
{
    char strA[251], strB[251];

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        cin >> strA >> strB;

        HugeInt dividend;
        dividend.size = strlen(strA);
        dividend.digit = new int[dividend.size]();
        for (int i = 0; i < dividend.size; ++i)
            dividend.digit[i] = strA[dividend.size - 1 - i] - '0';

        HugeInt divisor;
        divisor.size = strlen(strB);
        divisor.digit = new int[divisor.size]();
        for (int i = 0; i < divisor.size; ++i)
            divisor.digit[i] = strB[divisor.size - 1 - i] - '0';

        HugeInt quotient;
        HugeInt remainder;
        dividend.division(divisor, quotient, remainder);

        for (int i = quotient.size - 1; i >= 0; i--)
            cout << quotient.digit[i];
        cout << endl;

        for (int i = remainder.size - 1; i >= 0; i--)
            cout << remainder.digit[i];
        cout << endl;

        delete[] dividend.digit;
        delete[] divisor.digit;
        delete[] quotient.digit;
        delete[] remainder.digit;
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend != 0, divisor != 0 and dividend >= divisor
void HugeInt::division(HugeInt divisor, HugeInt& quotient, HugeInt& remainder)
{
    quotient.size = size - divisor.size + 1;
    quotient.digit = new int[quotient.size]();

    for (int i = quotient.size - 1; i >= 0; i--) {   //每一位的商

        HugeInt newdivisor;
        newdivisor.size = i + divisor.size;
        newdivisor.digit = new int[newdivisor.size]();
        for (int m = divisor.size - 1; m >= 0; m--)newdivisor.digit[m + i] = divisor.digit[m];

        while (less(newdivisor)||equal(newdivisor)) {       //除數小於被除數就做
            subtraction(newdivisor);
            quotient.digit[i] += 1;
        }

        delete[] newdivisor.digit;
    }

    remainder.size = size;
    remainder.digit = new int[remainder.size];
    for (int i = 0; i < remainder.size; i++)
        remainder.digit[i] = digit[i];

    if (quotient.size > 1 && quotient.digit[quotient.size - 1] == 0)    //處理12/6=02等情況
        quotient.size--;
}

// hugeInt /= 10, or equivalently, shifts right by one position
void HugeInt::divideBy10()
{
    if (size == 1)
        digit[0] = 0;
    else
    {
        for (int i = 1; i < size; i++)
            digit[i - 1] = digit[i];

        size--;
        digit[size] = 0;
    }
}

// minuend -= subtrahend
// provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
void HugeInt::subtraction(HugeInt subtrahend)
{
    if (equal(subtrahend))
    {
        size = 1;
        digit[0] = 0;
        return;
    }

    int i = 0, j = 0;
    while (j < subtrahend.size)
    {
        digit[j] = digit[j] - subtrahend.digit[j];
        j++;
    }
    while (j < size)
    {
        digit[j] = digit[j];
        j++;
    }
    for (i = 0; i < size - 1; i++)
    {
        if (digit[i] < 0)
        {
            digit[i] += 10;
            digit[i + 1]--;
        }
    }
    while (size > 1 && digit[size - 1] == 0)
        size--;
}

// returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool HugeInt::less(HugeInt hugeInt2)
{
    if (size > hugeInt2.size)return true;
    if (size < hugeInt2.size)return false;
    for (int i = size - 1; i >= 0; i--) {
        if (digit[i] > hugeInt2.digit[i])return true;
        if (digit[i] < hugeInt2.digit[i])return false;
    }
    return false;
}

// return true if and only if hugeInt1 == hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool HugeInt::equal(HugeInt hugeInt2)
{
    if (size != hugeInt2.size)
        return false;

    for (int i = size - 1; i >= 0; i--)
        if (digit[i] != hugeInt2.digit[i])
            return false;

    return true;
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero()
{
    return size == 1 && digit[0] == 0;
}
