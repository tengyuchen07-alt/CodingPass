// Polynomial division provided that the quotient and remainder have integer coefficients
#include <iostream>
using namespace std;

// quotient = dividend / divisor; remainder = dividend % divisor provided that
// dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ], and
// neither dividend nor divisor is the zero polynomial
void division(int dividendCoef[], long long int dividendExpon[], int dividendSize,
    int divisorCoef[], long long int divisorExpon[], int divisorSize,
    int quotientCoef[], long long int quotientExpon[], int& quotientSize,
    int remainderCoef[], long long int remainderExpon[], int& remainderSize);

// returns true if and only if polynomial1 == polynomial2
bool equal(int coefficient1[], long long int exponent1[], int size1,
    int coefficient2[], long long int exponent2[], int size2);

// minuend -= subtrahend
void subtraction(int minuendCoef[], long long int minuendExpon[], int& minuendSize,
    int subtrahendCoef[], long long int subtrahendExpon[], int subtrahendSize);

// outputs the specified polynomial
void output(int coefficient[], long long int exponent[], int size);

const int arraySize1 = 20;
const int arraySize2 = 400;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int dividendCoef[arraySize2] = {};
        long long int dividendExpon[arraySize2] = {};
        int dividendSize;
        cin >> dividendSize; // input dividend
        for (int i = dividendSize - 1; i >= 0; i--)
            cin >> dividendCoef[i];
        for (int i = dividendSize - 1; i >= 0; i--)
            cin >> dividendExpon[i];

        int divisorCoef[arraySize1] = {};
        long long int divisorExpon[arraySize1] = {};
        int divisorSize;
        cin >> divisorSize; // input divisor
        for (int i = divisorSize - 1; i >= 0; i--)
            cin >> divisorCoef[i];
        for (int i = divisorSize - 1; i >= 0; i--)
            cin >> divisorExpon[i];

        int quotientCoef[arraySize1] = {};
        long long int quotientExpon[arraySize1] = {};
        int quotientSize = arraySize1;

        int remainderCoef[arraySize2] = {};
        long long int remainderExpon[arraySize2] = {};
        int remainderSize = dividendSize;

        // quotient = dividend / divisor; remainder = dividend % divisor
        division(dividendCoef, dividendExpon, dividendSize,
            divisorCoef, divisorExpon, divisorSize,
            quotientCoef, quotientExpon, quotientSize,
            remainderCoef, remainderExpon, remainderSize);

        output(quotientCoef, quotientExpon, quotientSize);
        output(remainderCoef, remainderExpon, remainderSize);
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor provided that
// dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ], and
// neither dividend nor divisor is the zero polynomial
void division(int dividendCoef[], long long int dividendExpon[], int dividendSize,
    int divisorCoef[], long long int divisorExpon[], int divisorSize,
    int quotientCoef[], long long int quotientExpon[], int& quotientSize,
    int remainderCoef[], long long int remainderExpon[], int& remainderSize)
{
    quotientSize = 0;
    while (dividendSize>0&&dividendExpon[dividendSize - 1] >= divisorExpon[divisorSize - 1]) {
        int qCoef = dividendCoef[dividendSize - 1] / divisorCoef[divisorSize - 1];
        long long qExpon = dividendExpon[dividendSize - 1] - divisorExpon[divisorSize - 1];

        quotientCoef[quotientSize]  = qCoef;
        quotientExpon[quotientSize] = qExpon;
        quotientSize++;

        for (int i = 0; i < divisorSize; i++) {
            remainderCoef[i] = qCoef * divisorCoef[i];
            remainderExpon[i] = qExpon + divisorExpon[i];
        }
        remainderSize = divisorSize;
        if (equal(dividendCoef, dividendExpon, dividendSize,
            remainderCoef, remainderExpon, remainderSize)) {
			remainderCoef[0] = 0;
			remainderExpon[0] = 0;
			remainderSize = 1;
            break;
        }
        subtraction(dividendCoef, dividendExpon, dividendSize,
            remainderCoef, remainderExpon, remainderSize);
        remainderSize = dividendSize;
        for (int i = 0; i < remainderSize; i++) {
            remainderCoef[i] = dividendCoef[i];
            remainderExpon[i] = dividendExpon[i];
        }
    }
    for (int i = 0; i < quotientSize / 2; i++) {
        swap(quotientCoef[i], quotientCoef[quotientSize - 1 - i]);
        swap(quotientExpon[i], quotientExpon[quotientSize - 1 - i]);
    }
}
// returns true if and only if polynomial1 == polynomial2
bool equal(int coefficient1[], long long int exponent1[], int size1,
    int coefficient2[], long long int exponent2[], int size2)
{
    if (size1 != size2)
        return false;

    for (int i = 0; i < size1; i++)
        if (coefficient1[i] != coefficient2[i] || exponent1[i] != exponent2[i])
            return false;

    return true;
}

// minuend -= subtrahend
void subtraction(int minuendCoef[], long long int minuendExpon[], int& minuendSize,
    int subtrahendCoef[], long long int subtrahendExpon[], int subtrahendSize)
{
    int resultCoef[arraySize2] = {};
    long long int resultExpon[arraySize2] = {};
    int i = 0, j = 0, k = 0;
    while (i < minuendSize && j < subtrahendSize) {
        if (minuendExpon[i] == subtrahendExpon[j]) {
            int coef = minuendCoef[i] - subtrahendCoef[j];
            if (coef != 0) {
                resultCoef[k] = coef;
                resultExpon[k] = minuendExpon[i];
                k++;
            }
            i++; j++;
        }
        else if (minuendExpon[i] < subtrahendExpon[j]) {
            resultCoef[k] = minuendCoef[i];
            resultExpon[k] = minuendExpon[i];
            k++; i++;
        }
        else { 
            resultCoef[k] = -subtrahendCoef[j];
            resultExpon[k] = subtrahendExpon[j];
            k++; j++;
        }
    }
    while (i < minuendSize) {
        resultCoef[k] = minuendCoef[i];
        resultExpon[k] = minuendExpon[i];
        k++; i++;
    }
    while (j < subtrahendSize) {
        resultCoef[k] = -subtrahendCoef[j];
        resultExpon[k] = subtrahendExpon[j];
        k++; j++;
    }
    minuendSize = k;
    for (int t = 0; t < k; t++) {
        minuendCoef[t] = resultCoef[t];
        minuendExpon[t] = resultExpon[t];
    }
}
// outputs the specified polynomial
void output(int coefficient[], long long int exponent[], int size)
{
    cout << size << endl;
    cout << coefficient[size - 1];
    for (int i = size - 2; i >= 0; i--)
        cout << " " << coefficient[i];
    cout << endl;

    cout << exponent[size - 1];
    for (int i = size - 2; i >= 0; i--)
        cout << " " << exponent[i];
    cout << endl;
}
