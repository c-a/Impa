#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

int
main(void)
{
    int round;

    while (cin >> round)
    {
        string answer;
        string guesses;
        bool done_guesses['z' - 'a' + 1] = {false,};

        if (round < 0)
            break;

        cin >> answer;
        cin >> guesses;

        int wrong_guesses = 0;
        for (int i = 0; i < (int)guesses.length(); ++i)
        {
            char c = guesses[i];
            
            if (done_guesses[c-'a'])
                continue;

            if (answer.find(c) != string::npos)
            {
                answer.erase(std::remove(answer.begin(), answer.end(), c), answer.end());
                if (answer.size() == 0)
                    break;
            }
            else
            {
                if (++wrong_guesses == 7)
                    break;
            }
        }
        
        cout << "Round " << round << endl;

        if (wrong_guesses == 7)
            cout << "You lose." << endl;
        
        else if (answer.size() == 0)
            cout << "You win." << endl;

        else
            cout << "You chickened out." << endl;
    }

    return 0;
}