#include <iostream>
using namespace::std;

// find the sum of factors of n in the range [ start .. n - 1 ]
int sumFactors(int n, int start);

int main()
{
	int numCases;
	cin >> numCases;
	for (int i = 1; i <= numCases; i++)
	{
		int n;
		cin >> n;

		// n is equal to the sum of factors of n in the range [ 1 .. n - 1 ]
		if (n == sumFactors(n, 1))
			cout << "perfect number" << endl;
		else
			cout << "non-perfect number" << endl;
	}
}

int sumFactors(int n, int start)
{
	if (n == start)return 0;
	if (!(n % start)) {
		start += sumFactors(n, start + 1);
		return start;
	}
	else sumFactors(n, start + 1);
}
