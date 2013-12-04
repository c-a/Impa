#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>


struct Event {
  enum Type {
    FUEL_CONSUMPTION,
    LEAK,
    GAS_STATION,
    MECHANIC,
    GOAL
  };

  Event(const std::string string) {
    struct {
      char* str;
      Type type;
    } types[5] = {
      { "Fuel consumption", FUEL_CONSUMPTION },
      { "Leak", LEAK },
      { "Mechanic", MECHANIC },
      { "Gas station", GAS_STATION },
      { "Goal", GOAL }
    };
    
    char* s;

    pos = strtol(string.c_str(), &s, 10);

    // Skip spaces
    while (*s == ' ') s++;

    for (int i = 0; i < 5; i++) {
      if (strncmp(s, types[i].str, strlen(types[i].str)) == 0) {
        type = types[i].type;
        s += strlen(types[i].str);
      }
    }

    // Skip spaces
    while (*s == ' ') s++;

    if (type == FUEL_CONSUMPTION)
      fuel_consumption = strtol(s, &s, 10);
  }

  int pos;
  Type type;
  int fuel_consumption;
};

int main() {
  std::string line;

  int tank_size = 0;

  int gas = 0;
  int prev_pos = 0;
  int fuel_consumption = 0;
  int leak = 0;
  while (std::getline(std::cin, line)) {
    Event event(line);

    gas += (event.pos - prev_pos) * (fuel_consumption + 100*leak);
    prev_pos = event.pos;

    if (event.type == Event::FUEL_CONSUMPTION) {
      if (event.pos == 0 && event.fuel_consumption == 0)
        break;

      fuel_consumption = event.fuel_consumption;
    }
    else if (event.type == Event::LEAK) {
      leak++;
    }
    else if (event.type == Event::MECHANIC) {
      leak = 0;
    }
    else if (event.type == Event::GAS_STATION) {
      tank_size = std::max(tank_size, gas);
      gas = 0;
    }
    else if (event.type == Event::GOAL) {
      tank_size = std::max(tank_size, gas);
      printf("%.3f\n", (float)tank_size / 100);

      tank_size = 0;
      gas = 0;
      prev_pos = 0;
      fuel_consumption = 0;
      leak = 0;
    }
  }

  return 0;
}

