#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

int
main(void)
{
    string line;

    while (cin >> line)
    {
        if (line.empty())
            break;

        istringstream tmp(line);
        int n;
        tmp >> n;

        vector<string> strings;

        unsigned int max = 0;
        for (int i = 0; i < n; ++i)
        {
            cin >> line;
            strings.push_back(line);

            if (line.length() > max)
                max = line.length();
        }

        sort(strings.begin(), strings.end());

        for (int i = 0; i < 60; i++)
            cout << '-';
        cout << endl;

        cout << left;

        unsigned int columns = 1;
        columns += ((60 - max) / (max + 2));
        
        unsigned int rows = ceil((float)strings.size() / columns);

        for (unsigned int row = 0; row < rows; ++row)
        {
            for (unsigned int col = 0; col < columns; ++col)
            {
                unsigned int index = col * rows + row;
                if (index >= strings.size())
                    break;

                if (col == (columns - 1))
                    cout.width(max);
                else
                    cout.width(max + 2);

                cout << strings[index];
            }
            cout << endl;
        }
    }

    return 0;
}