#include <iostream>
#include <cstring>
using namespace::std;

struct HugeInt
{
    int size;
    int* digit;
};

// sum = addend + adder
void addition(HugeInt addend, HugeInt adder, HugeInt& sum);

int main()
{
    char strA[251], strB[251];
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        cin >> strA >> strB;

        HugeInt addend;
        addend.size = strlen(strA);
        addend.digit = new int[addend.size];
        for (int i = 0; i < addend.size; ++i)
            addend.digit[i] = strA[addend.size - 1 - i] - '0';

        HugeInt adder;
        adder.size = strlen(strB);
        adder.digit = new int[adder.size];
        for (int i = 0; i < adder.size; ++i)
            adder.digit[i] = strB[adder.size - 1 - i] - '0';

        HugeInt sum;
        addition(addend, adder, sum);

        for (int i = sum.size - 1; i >= 0; i--)
            cout << sum.digit[i];
        cout << endl;

        delete[] addend.digit;
        delete[] adder.digit;
        delete[] sum.digit;
    }
}

// sum = addend + adder
void addition(HugeInt addend, HugeInt adder, HugeInt& sum)
{
	sum.size = (addend.size > adder.size ? addend.size : adder.size) ;
	sum.digit = new int[sum.size]();
    int i = 0, j = 0;
    while(i<addend.size&&j<adder.size)
    {
        sum.digit[i] = addend.digit[i] + adder.digit[j];
        i++;
        j++;
	}
    while (i < addend.size)
    {
        sum.digit[i] = addend.digit[i];
        i++;
    }
    while (j < adder.size)
    {
        sum.digit[j] = adder.digit[j];
        j++;
    }
    for (int k = 0; k < sum.size - 1; k++)
    {
        if (sum.digit[k] >= 10)
        {
            sum.digit[k + 1] += sum.digit[k] / 10;
            sum.digit[k] = sum.digit[k] % 10;
        }
	}
}
