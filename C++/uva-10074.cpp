#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

static bool trees[100][100];

static bool
valid_land(int t, int b, int l, int r)
{
    for (int i = t; i <= b; i++)
    {
        for (int j = l; j <= r; j++)
        {
            if (trees[i][j])
                return false;
        }
    }

    return true;
}

int
main(void)
{
    while (true)
    {
        int M, N;

        cin >> M >> N;
        if (M == 0)
            break;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
                cin >> trees[i][j];
        }

        int max_size = 0;

        for (int t = 0; t < M; t++)
        {
            for (int l = 0; l < N; l++)
            {
                for (int b = t; b < M; b++)
                {
                    for (int r = l; r < N; r++)
                    {
                        if (!valid_land(t, b, l, r))
                            break;

                        int size = (b-t+1)*(r-l+1);
                        if (size > max_size)
                            max_size = size;
                    }
                }
            }
        }

        cout << max_size << endl;
    }

    return 0;
}