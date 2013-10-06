#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>

#include <stdio.h>

template<int MAX_EDGES>
class Graph
{
public:
    void reset(unsigned int V) {
        V_ = V;
        for (int i = 0; i < MAX_EDGES; i++)
            adj_[i].clear();
    }

    void addEdge(unsigned int u, unsigned int v) {
        for(std::vector<unsigned int>::iterator it = adj_[u].begin();
            it != adj_[u].end(); ++it) {
            if (*it == v)
                return;
        }

        adj_[u].push_back(v);
        adj_[v].push_back(u);
    }

    unsigned int V() const {
        return V_;
    }

    const std::vector<unsigned int>& adj(unsigned int u) {
        return adj_[u];
    }

private:
    std::vector<unsigned int> adj_[MAX_EDGES];
    unsigned int V_;
};

template<int MAX_EDGES>
class ShortestPath
{
public:
    void reset(Graph<MAX_EDGES>& G, unsigned int s) {
        for (int i = 0; i < G.V(); i++) {
            pred_[i] = -1;
            distance_[i] = 0;
        }

        std::list<unsigned int> q;
        pred_[s] = s;
        q.push_back(s);
        while(!q.empty()) {
            unsigned int u = q.front();
            q.pop_front();

            const std::vector<unsigned int>& adj = G.adj(u);
            for(std::vector<unsigned int>::const_iterator it = adj.begin();
                it != adj.end(); ++it) {
                unsigned int v = *it;
                if (pred_[v] != -1)
                    continue;

                pred_[v] = u;
                distance_[v] = distance_[u] + 1;
                q.push_back(v);
            }
        }
    }

    unsigned int distance(unsigned int u) {
        return distance_[u];
    }

private:
    unsigned int pred_[MAX_EDGES];
    unsigned int distance_[MAX_EDGES];
};

int
main(void)
{
    Graph<10000> G;
    ShortestPath<10000> SP;
    int lines[10000];
    int cases;

    std::cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        std::string line, s;
        std::stringstream ss;
        int S, N;

        std::cin >> N;
        std::cin >> S;
        getline(std::cin, line);

        G.reset(N);
        for (int n = 0; n < N; n++)
            lines[n] = 0;

        for (int j = 0; j < S; j++) {
            int prevStation = -1;

            getline(std::cin, line);
            ss.str(line);
            ss.clear();
            while (std::getline(ss, s, ' ')) {
                int station;
                sscanf(s.c_str(), "%d", &station);
                if (station == 0)
                    break;
                station--;
                if (prevStation != -1)
                    G.addEdge(prevStation, station);
                lines[station]++;
                prevStation = station;
            }
        }

        unsigned long long int minDist = std::numeric_limits<unsigned long long int>::max();
        int station = -1;
        for (int n = 0; n < N; n++) {
            if (lines[n] <= 1)
                continue;

            SP.reset(G, n);
            unsigned long long int dist = 0;
            for (int u = 0; u < N; u++) {
                if (lines[u] <= 1)
                    continue;
                dist += SP.distance(u);
            }

            if (dist < minDist || (dist == minDist && n < station)) {
                minDist = dist;
                station = n;
            }
        }

        printf("Krochanska is in: %d\n", station+1);
    }

    return 0;
}