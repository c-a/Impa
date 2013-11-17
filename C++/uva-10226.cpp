#include <iostream>
#include <map>
#include <algorithm>

#include <stdio.h>

int
main(void)
{
    int cases;
    std::string line;
    std::map<std::string, int> trees;

    std::cin >> cases;
    getline(std::cin, line);
    getline(std::cin, line);
    for (int c = 0; c < cases; c++) {
        if (c > 0)
            printf("\n");
        trees.clear();
        int nTrees = 0;
        while (true) {
            getline(std::cin, line);
            if (!std::cin.good() || line.length() == 0)
                break;

            nTrees++;
            trees[line]++;
        }

        for (std::map<std::string, int>::const_iterator iter = trees.begin();
            iter != trees.end(); ++iter) {
            printf("%s %.4f\n", iter->first.c_str(), ((float)iter->second/nTrees)*100);
        }
    }

    return 0;
}
