// Polynomial multiplication
#include <iostream>
using namespace std;

// product = multiplicand * multiplier
void multiplication(long long int multiplicandCoef[], long long int multiplicandExpon[], int multiplicandSize,
    long long int multiplierCoef[], long long int multiplierExpon[], int multiplierSize,
    long long int productCoef[], long long int productExpon[], int& productSize);

// addend += adder
void addition(long long int addendCoef[], long long int addendExpon[], int& addendSize,
    long long int adderCoef[], long long int adderExpon[], int adderSize);

// returns true if and only if the specified polynomial is the zero polynomial
bool isZero(long long int coefficient[], int size);

// outputs the specified polynomial
void output(long long int coefficient[], long long int exponent[], int size);

const int arraySize = 10;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        long long int multiplicandCoef[arraySize] = {};
        long long int multiplicandExpon[arraySize] = {};
        int multiplicandSize;
        cin >> multiplicandSize; // input multiplicand
        for (int i = multiplicandSize - 1; i >= 0; i--)
            cin >> multiplicandCoef[i];
        for (int i = multiplicandSize - 1; i >= 0; i--)
            cin >> multiplicandExpon[i];

        long long int multiplierCoef[arraySize] = {};
        long long int multiplierExpon[arraySize] = {};
        int multiplierSize;
        cin >> multiplierSize; // input multiplier
        for (int i = multiplierSize - 1; i >= 0; i--)
            cin >> multiplierCoef[i];
        for (int i = multiplierSize - 1; i >= 0; i--)
            cin >> multiplierExpon[i];

        long long int productCoef[arraySize * arraySize] = {};
        long long int productExpon[arraySize * arraySize] = {};
        int productSize = 1;

        // product = multiplicand * multiplier
        multiplication(multiplicandCoef, multiplicandExpon, multiplicandSize,
            multiplierCoef, multiplierExpon, multiplierSize,
            productCoef, productExpon, productSize);

        output(productCoef, productExpon, productSize);
    }
}

// product = multiplicand * multiplier
void multiplication(long long int multiplicandCoef[], long long int multiplicandExpon[], int multiplicandSize,
    long long int multiplierCoef[], long long int multiplierExpon[], int multiplierSize,
    long long int productCoef[], long long int productExpon[], int& productSize)
{
    long long int resultCoef[arraySize] = {};
    long long int resultExpon[arraySize] = {};
    
    for (int i = 0; i <= multiplicandSize - 1; i++) {
        int resultSize = 0;
        for (int j =0 ; j <= multiplierSize - 1; j++) {
            resultCoef[resultSize] = multiplicandCoef[i] * multiplierCoef[j];
            resultExpon[resultSize] = multiplicandExpon[i] + multiplierExpon[j];
            resultSize++;
        }//被乘數的第i項和乘數相乘的結果進addition
        addition(productCoef, productExpon, productSize,resultCoef, resultExpon, resultSize );
    }
}

// addend += adder
void addition(long long int addendCoef[], long long int addendExpon[], int& addendSize,
    long long int adderCoef[], long long int adderExpon[], int adderSize)
{
    for (int i = 0; i < adderSize; ++i) {
        bool merged = false;
        for (int j = 0; j < addendSize; ++j) {
            if (adderExpon[i] == addendExpon[j]) {
                addendCoef[j] += adderCoef[i];
                merged = true;
                break;
            }
        }
        if (!merged) {
            addendCoef[addendSize] = adderCoef[i];
            addendExpon[addendSize] = adderExpon[i];
            addendSize++;
        }
    }
    int newSize = 0;
    for (int i = 0; i < addendSize; ++i) {
        if (addendCoef[i] != 0) {
            addendCoef[newSize] = addendCoef[i];
            addendExpon[newSize] = addendExpon[i];
            newSize++;
        }
    }
    addendSize = newSize;
    for (int i = 0; i < addendSize - 1; ++i) {
        for (int j = i + 1; j < addendSize; ++j) {
            if (addendExpon[i] > addendExpon[j]) {
                std::swap(addendExpon[i], addendExpon[j]);
                std::swap(addendCoef[i], addendCoef[j]);
            }
        }
    }
}

// returns true if and only if the specified polynomial is the zero polynomial
bool isZero(long long int coefficient[], int size)
{
    return (size == 1 && coefficient[0] == 0);
}

// outputs the specified polynomial
void output(long long int coefficient[], long long int exponent[], int size)
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
