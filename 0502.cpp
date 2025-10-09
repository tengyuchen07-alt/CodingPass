#include <iostream>
using namespace std;

// find the sum of all the even integers in the range [ a, b ]
// provided that both a and b are positive even integers, and a <= b
int evenSum(int a, int b);

int main()
{
    int numCases;
    cin >> numCases;
    for (int i = 1; i <= numCases; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a == b && a % 2 == 1)
            cout << 0 << endl;
        else
        {
            if (a % 2)a++;
            if (b % 2)b--;
            cout << evenSum(a, b) << endl;
        }
    }
}

// find the sum of all the even integers in the range [ a, b ]
// provided that both a and b are positive even integers, and a <= b
int evenSum(int a, int b)
{
    int sum = 0;
    for (int i = a; i <= b; i += 2)
        sum += i;
    return sum;
}
