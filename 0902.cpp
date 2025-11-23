#include <iostream>
#include <cstring>
#include <vector>
using namespace::std;

// returns true if and only if hugeInt1 == hugeInt2
bool equal(vector< int > hugeInt1, vector< int > hugeInt2);

// difference = minuend - subtrahend provided that minuend >= subtrahend
vector< int > subtraction(vector< int > minuend, vector< int > subtrahend);

int main()
{
    char strA[251], strB[251];

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        cin >> strA >> strB;

        int minuendSize = strlen(strA);
        vector< int > minuend(minuendSize);
        for (int i = 0; i < minuendSize; ++i)
            minuend[i] = strA[minuendSize - 1 - i] - '0';

        int subtrahendSize = strlen(strB);
        vector< int > subtrahend(subtrahendSize);
        for (int i = 0; i < subtrahendSize; ++i)
            subtrahend[i] = strB[subtrahendSize - 1 - i] - '0';

        vector< int > difference = subtraction(minuend, subtrahend);

        for (int i = difference.size() - 1; i >= 0; i--)
            cout << difference[i];
        cout << endl;
    }
}

// returns true if and only if hugeInt1 == hugeInt2
bool equal(vector< int > hugeInt1, vector< int > hugeInt2)
{
    int size1 = hugeInt1.size();
    int size2 = hugeInt2.size();
    if (size1 != size2)
        return false;

    for (int i = 0; i < size1; i++)
        if (hugeInt1[i] != hugeInt2[i])
            return false;

    return true;
}

// difference = minuend - subtrahend provided that minuend >= subtrahend
vector< int > subtraction(vector< int > minuend, vector< int > subtrahend)
{
	if (equal(minuend, subtrahend))
        return vector< int >(1, 0);
	vector< int > difference;
    int borrow = 0;
    for (int i = 0; i < minuend.size(); i++) {
        int a = (i < minuend.size() ? minuend[i] : 0);
        int b = (i < subtrahend.size() ? subtrahend[i] : 0);
        if (a - b+borrow < 0) {
            difference.push_back(a - b +borrow+ 10);
            borrow = -1;
        }
        else
        {
            difference.push_back(a - b+borrow);
            borrow = 0;
        }
    }
    while (difference[difference.size() - 1] == 0 && difference.size() > 0)
        difference.resize(difference.size() - 1);
    return difference;
}
