#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <list>

using namespace std;

struct Beverage {
  int index;
  string name;
  set<string> larger;
  int inDegree;
};

int main() {
  for (int caseN = 1, N; cin >> N; ++caseN) {
    string line;
    getline(cin, line);
    deque<Beverage> beverages;
    map<string, Beverage*> bev_map;
    for (int i = 0; i < N; ++i) {
      Beverage bev;
      bev.index = i;
      getline(cin, bev.name);
      bev.inDegree = 0;
      beverages.push_back(std::move(bev));
      bev_map[beverages.back().name] = &beverages.back();
    }

    int M;
    cin >> M;
    getline(cin, line);
    for (int i = 0; i < M; ++i) {
      string b1, b2;
      getline(cin, b1, ' ');
      getline(cin, b2);
      if (bev_map[b1]->larger.insert(b2).second) {
        bev_map[b2]->inDegree++;
      }
    }

    struct BevComp {
      bool operator()(const Beverage* a, const Beverage* b) const {
        return a->index > b->index;
      }
    };
    priority_queue<const Beverage*, vector<const Beverage*>, BevComp>
      pq((BevComp()));
    for (const Beverage& bev : beverages) {
      if (bev.inDegree == 0) { pq.push(&bev); }
    }
    vector<const Beverage*> topSort;
    while (!pq.empty()) {
      const Beverage* bev = pq.top(); pq.pop();
      for (const string& larger : bev->larger) {
        Beverage* l = bev_map[larger];
        if (--l->inDegree == 0) {
          pq.push(l);
        }
      }
      topSort.push_back(bev);
    }

    cout << "Case #" << caseN <<
      ": Dilbert should drink beverages in this order:";
    for (const Beverage* bev : topSort) {
      std::cout << " " << bev->name;
    }
    std::cout << ".\n\n";
  }
}

