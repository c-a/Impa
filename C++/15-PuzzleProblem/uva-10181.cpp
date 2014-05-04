
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <unordered_map>

typedef uint64_t Board;

Board swap(Board b, int i, int j) {
  Board iset = (b >> 4*(15 - i)) & 0xf;
  Board jset = (b >> 4*(15 - j)) & 0xf;
  Board sor = iset ^ jset;
  sor = (sor << 4*(15 - i)) | (sor << 4*(15 - j));
  return b ^ sor;
}

Board set(Board b, uint8_t i, uint8_t val) {
  Board mask = ~(0xfLL << 4*(15 - i));
  Board vset = static_cast<uint64_t>(val) << 4*(15 - i);
  return (b & mask) | vset;
}

uint8_t get(Board b, uint8_t i) {
  return (b >> 4*(15 - i)) & 0xf;
}

uint8_t FindPos(Board b, uint8_t val) {
  for (int j = 0; j < 16; ++j) {
    if (get(b, j) == val) {
      return j;
    }
  }
  return -1;
}

uint16_t HamiltonDistance(Board b) {
  uint16_t sum = 0;
  for (uint8_t i = 0; i < 16; ++i) {
    int val = get(b, i);
    if (val == 0) continue;
    val--;
    sum += std::abs((i % 4) - (val % 4)) + std::abs((i / 4) - (val / 4));
  }
  return sum;
}

static const int kMaxSteps = 50;

struct Pos {
  Board b;
  char seq[kMaxSteps + 1];
  uint16_t ham_dist;
  uint8_t steps;
  Pos() :
    b(0), ham_dist(0), steps(0) { seq[steps] = '\0'; }
  explicit Pos(Board b_) :
    b(b_), ham_dist(HamiltonDistance(b_)), steps(0) { seq[steps] = '\0'; }
  Pos(const Pos& old_pos, char dir, Board nb) :
    b(nb), ham_dist(HamiltonDistance(nb)), steps(old_pos.steps + 1) {
      memcpy(seq, old_pos.seq, old_pos.steps * sizeof(char));
      seq[steps - 1] = dir;
      seq[steps] = '\0';
    }
  bool operator<(const Pos& other) const {
    return steps + 4*ham_dist > other.steps + 4*ham_dist;
  }
};

std::priority_queue<Pos> q;
std::unordered_map<Board, bool> visited;

void MaybePush(const Pos& p, char dir, uint8_t pos, uint8_t npos) {
  Board nb = swap(p.b, pos, npos);
  if (!visited[nb]) {
    Pos np = Pos(p, dir, nb);
    if (np.steps + np.ham_dist > kMaxSteps)
      return;
    q.push(np);
    visited[nb] = true;
  }
}

bool MinDistance(Board b, Pos* op) {
  q = std::priority_queue<Pos>();
  visited.clear();
  q.push(Pos(b));
  visited[b] = true;
  while (!q.empty()) {
    Pos p = q.top(); q.pop();
    if (p.b == 0x123456789ABCDEF0LL) {
      *op = p;
      return true;
    }
    uint8_t zpos = FindPos(p.b, 0);
    if (zpos % 4 > 0) {
      MaybePush(p, 'L', zpos, zpos - 1);
    }
    if (zpos % 4 < 3) {
      MaybePush(p, 'R', zpos, zpos + 1); 
    }
    if (zpos / 4 > 0) {
      MaybePush(p, 'U', zpos, zpos - 4);
    }
    if (zpos / 4 < 3) {
      MaybePush(p, 'D', zpos, zpos + 4);
    }
  }
  return false;
}

bool IsSolvable(Board b) {
  uint8_t inversions = 0;
  uint8_t blank_row;
  for (uint8_t i = 0; i < 16; ++i) {
    if (get(b, i) == 0) {
      blank_row = i / 4;
    }
    for (uint8_t j = i + 1; j < 16; ++j) {
      if (get(b, j) && get(b, i) > get(b, j))
        inversions++;
    }
  }
  return (blank_row + 1) % 2 == inversions % 2;
}

int main() {
  int N;
  scanf("%d", &N);
  while (N-- > 0) {
    Board b = 0;
    for (uint8_t i = 0; i < 16; ++i) {
      int val; scanf("%d", &val);
      b = set(b, i, val);
    }
    Pos p;
    if (IsSolvable(b) && MinDistance(b, &p)) {
      p.seq[p.steps] = '\0';
      printf("%s\n", p.seq);
    } else {
      printf("This puzzle is not solvable.\n");
    }
  }
}
