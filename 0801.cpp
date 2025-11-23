#include <iostream>
#include <cstring>
using namespace::std;

class HugeInt
{
public:
    int size;
    int* digit;

    // sum = addend + adder
    void addition(HugeInt adder, HugeInt& sum);
};

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
        addend.addition(adder, sum);

        for (int i = sum.size - 1; i >= 0; i--)
            cout << sum.digit[i];
        cout << endl;

        delete[] addend.digit;
        delete[] adder.digit;
        delete[] sum.digit;
    }
}

// sum = addend + adder
void HugeInt::addition(HugeInt adder, HugeInt& sum)
{
	sum.size = (size > adder.size ? size : adder.size) + 1;
	sum.digit = new int[sum.size];
	int carry = 0;
    for (int i = 0; i < sum.size; ++i)
    {
        int a = (i < size ? digit[i] : 0);
        int b = (i < adder.size ? adder.digit[i] : 0);
        int s = a + b + carry;
        sum.digit[i] = s % 10;
        carry = s / 10;
	}
    if (sum.digit[sum.size - 1] == 0)
		sum.size--;
}
