#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

bool divAtPos[100][10000];

static bool
divisable(int sum, int pos, vector<int>& numbers, int K)
{
    sum = ((sum % K) + K) % K;

    if (pos == (int)(numbers.size() - 1))
        return sum == 0;

    if (divAtPos[sum][pos])
        return false;

    if (divisable(sum + numbers[pos+1], pos + 1, numbers, K))
        return true;
    
    if (divisable(sum - numbers[pos+1], pos + 1, numbers, K))
        return true;

    divAtPos[sum][pos] = true;
    return false;
}

int
main(void)
{
    int cases;

    cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        int N, K;
        vector<int> numbers;

        cin >> N;
        cin >> K;
        for (int j = 0; j < N; j++)
        {
            int n;
            cin >> n;
            numbers.push_back(n);
        }

        for (int k = 0; k < 100; k++)
        {
            for (int l = 0; l < 10000; l++)
                divAtPos[k][l] = false;
        }

        if (divisable(numbers[0], 0, numbers, K))
            cout << "Divisible" << endl;
        else
            cout << "Not divisible" << endl;
    }

    return 0;
}