#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>

#include <stdio.h>

int str[10000];
static int K;

int createPalindrome(int left, int length, int additions) {
    if (additions > K)
        return std::numeric_limits<int>::max();

    if (length <= 1)
        return additions;

    if (str[left] == str[left + length - 1])
        return createPalindrome(left+1, length-2, additions);

    return std::min(createPalindrome(left, length-1, additions+1),
        createPalindrome(left+1, length-1, additions+1));
}

int
main(void)
{
    int cases;

    std::cin >> cases;
    for (int c = 0; c < cases; c++) {
        int N;

        std::cin >> N >> K;
        for (int i = 0; i < N; i++)
            std::cin >> str[i];

#if 0
        //int *dp = new int[10001*10001];
        for (int l = 0; l < N; l++) {
            dp[0*10001+l] = dp[1*10001+l] = 0;
        }
        
        for (int length = 2; length <= N; length++) {
            for (int left = 0; left < (N-length+1); left++) {
                int right = left + (length - 1);
                if (str[left] == str[right]) {
                    dp[length*10001+left] = dp[(length-2)*10001 + left+1];
                }
                else {
                    dp[length*10001+left] = std::min(dp[(length-1)*10001+left]+1, dp[(length-1)*10001+ left+1]+1);
                }
            }
        }

        int difficulty = dp[N*10001+0];
#endif

        int difficulty = createPalindrome(0, N, 0);

        printf("Case %d: ", c+1);
        if (difficulty == 0)
            std::cout << "Too easy" << std::endl;
        else if (difficulty <= K)
            std::cout << difficulty << std::endl;
        else
            std::cout << "Too difficult" << std::endl;
    }

    return 0;
}
