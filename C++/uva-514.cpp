#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

#include <math.h>

using namespace std;

static bool
check_train(vector<int>& train)
{
    int next_couch;
    int current_couch;
    stack<int> station;

    next_couch = 0;
    current_couch = 1;
    while (true)
    {
        /* Check if we can take couch from station */
        if (!station.empty() && station.top() == train[next_couch])
        {
            station.pop();
            if (++next_couch == (int)train.size())
                return true;
        }

        /* If we can take couch from train */
        else if (current_couch <= (int)train.size())
        {
            if (current_couch == train[next_couch])
            {
                if (++next_couch == (int)train.size())
                    return true;
            }
            else
            {
                station.push(current_couch);
            }

            current_couch++;
        }

        else
            return false;
    }
}

int
main(void)
{
    int train_length;
    map<int, int> number_map;
    vector<int> numbers;

    while (cin >> train_length)
    {
        if (train_length == 0)
            break;

        while (true)
        {
            int couch_n;
            vector<int> train;

            cin >> couch_n;
            if (couch_n == 0)
                break;

            train.push_back(couch_n);
            for (int i = 1; i < train_length; i++)
            {
                cin >> couch_n;
                train.push_back(couch_n);
            }

            if (check_train(train))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }

        cout << endl;
    }
}