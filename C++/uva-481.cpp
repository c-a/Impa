#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>

#include <math.h>

using namespace std;

static int
ceil_index (int* a, int l, int r, int key)
{
    while (r - l > 1)
    {
        int m = l + (r - l) / 2;
        if (a[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

int
main(void)
{
    string line;
    vector<int> numbers;

    while (getline(cin, line))
    {
        if (line.empty() || line[0] == '\n')
            break;

        istringstream tmp(line);
        int number;
        tmp >> number;

        numbers.push_back(number);
    }

    int size = numbers.size();

    int* tail_table = new int[size];
    int* pred_table = new int[size];
    int len;

    tail_table[0] = 0;
    pred_table[0] = -1;
    len = 1;
    for (int i = 1; i < size; i++)
    {
        if (numbers[i] < numbers[tail_table[0]])
        {
            tail_table[0] = i;
            pred_table[i] = -1;
        }

        else if (numbers[i] > numbers[tail_table[len-1]])
        {
            tail_table[len] = i;
            pred_table[i] = tail_table[len-1];

            len++;
        }

        else
        {
            int index = ceil_index(tail_table, 0, len-1, numbers[i]);
            tail_table[index] = i;

            pred_table[i] = tail_table[index-1];
        }
    }

    cout << len << endl;
    cout << '-' << endl;

    stack<int> s;
    for (int i = tail_table[len-1]; i != -1; i = pred_table[i])
        s.push(numbers[i]);

    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}