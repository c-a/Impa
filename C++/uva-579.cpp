#include <stdio.h>

using namespace std;

int
main(void)
{
  while (true) {

    int H, M;
    scanf("%d:%d", &H, &M);
    if (H == 0 && M == 0)
      break;

    float angle1 = 30*(H + (float)M/60);
    float angle2 = 6*M;

    float diff;
    if (angle1 > angle2)
      diff = angle1 - angle2;
    else
      diff = angle2 - angle1;

    if (diff > 180.0)
      diff = 360.0 - diff;

    printf("%.3f\n", diff);
  }

  return 0;
}
