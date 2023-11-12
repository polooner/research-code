#include <iostream>
#include <cmath>
using namespace std;

const int N = 21;
int rayValue = 50;

void resetRays (short[][N], short);
void displayRays (short[][N]);
void computeRays (short[][N], double);
void computeRays_0_45 (short[][N], double);
void computeRays_45_90 (short[][N], double);
void computeRays_90_135 (short[][N], double);
void computeRays_135_180 (short[][N], double);
void drawline (short[][N], int, int, int, int, short);

int
main ()
{
  short rays[N][N];


  for (double angle = 0; angle < 180; angle += 15)
    {
      resetRays (rays, 0);
      cout << "\nangle = " << angle << endl;
      computeRays (rays, angle);
      displayRays (rays);
    }

  return 0;
}


void
resetRays (short R[][N], short n)
{
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      R[row][col] = n;
}

void
displayRays (short R[][N])
{
  for (int row = 0; row < N; row++)
    {
      for (int col = 0; col < N; col++)
  cout << R[row][col] << " ";
      cout << endl;
    }
}

void
computeRays (short R[][N], double angle)
{
  if (angle >= 0 && angle < 45)
    computeRays_0_45 (R, angle);
  if (angle >= 45 && angle < 90)
    computeRays_45_90 (R, angle);
  if (angle >= 90 && angle < 135)
    computeRays_90_135 (R, angle);
  if (angle >= 135 && angle <= 180)
    computeRays_135_180 (R, angle);
}

void loopBackwards(short R[][N], int i, int counter) {
    for (int k = 0; k < counter; k++) {
        R[i][N - 1 -k] = 50 + counter - k;
    }
}

void loopBackwardsFromPoint(short R[][N], int i, int counter) {
    for (int k = 1; k <= counter; k++) {
        R[i][counter - k] = 50 - k;
    }
}

void loopBackwardsDecrementing(short R[][N], int i, int counter) {
    int j = 0;
    for (int k = counter; k > 0; k--) {
        R[N - 1 - k][i] = 50 - k;
        j++;
    }
}

void loopBackwardsFromPointIncrementing(short R[][N], int i, int counter) {
    for (int k = 1; k <= counter; k++) {
        R[i][counter - k] = 50 + k;
    }
}

void computeRays_0_45 (short R[][N], double angle)
{
  int intercept = round (angle * (N - 1) / 45.0);
  drawline (R, 0, 0, N - 1, intercept, rayValue);
  for (int i = 0; i < N; i++) {
        int leftCounter = 0;
        int rightCounter = 0;
        bool past50 = false;
    for (int j = 0; j < N - 1; j++) {
        if (R[i][j] == 50) {
            past50 = true;
        } 
        if (past50 == false) {
            leftCounter+=1;
        } 
        if (past50 == true) {
            rightCounter += 1;
        }
        
  }    
    loopBackwards(R, i, rightCounter);
    loopBackwardsFromPoint(R, i, leftCounter);
  }
    
}


void
computeRays_45_90 (short R[][N], double angle)
{
  int intercept = round ((90 - angle) * (N - 1) / 45.0);
  drawline (R, 0, 0, intercept, N - 1, rayValue);
for (int i = 0; i < N; i++) {
        int downCounter = 0;
        int upCounter = 0;
        bool past50 = false;
    for (int j = 0; j < N - 1; j++) {
        if (R[j][i] == 50) {
            past50 = true;
        } 
        if (past50 == false) {
            downCounter+=1;
        } 
        if (past50 == true) {
            upCounter += 1;
        }
        
  }    
    loopBackwardsDecrementing(R, i, upCounter);
    loopBackwardsFromPointIncrementing(R, i, downCounter);
  }
  
}


void
computeRays_90_135 (short R[][N], double angle)
{
  int intercept = round ((angle - 90) * (N - 1) / 45.0);
  drawline (R, 0, N - 1, intercept, 0, rayValue);
}

void
computeRays_135_180 (short R[][N], double angle)
{
  int intercept = round ((angle - 135) * (N - 1) / 45.0);
  drawline (R, 0, N - 1, N - 1, intercept, rayValue);
}

void
drawline (short A[][N], int x1, int y1, int x2, int y2, short c)
{
  int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
  dx = x2 - x1;
  dy = y2 - y1;
  dx1 = abs (dx);
  dy1 = abs (dy);
  px = 2 * dy1 - dx1;
  py = 2 * dx1 - dy1;
  if (dy1 <= dx1)
    {
      if (dx >= 0)
  {
    x = x1;
    y = y1;
    xe = x2;
  }
      else
  {
    x = x2;
    y = y2;
    xe = x1;
  }
      A[x][y] = c;
      for (i = 0; x < xe; i++)
  {
    x = x + 1;
    if (px < 0)
      {
        px = px + 2 * dy1;
      }
    else
      {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
    {
      y = y + 1;
    }
        else
    {
      y = y - 1;
    }
        px = px + 2 * (dy1 - dx1);
      }
    A[x][y] = c;
  }
    }
  else
    {
      if (dy >= 0)
  {
    x = x1;
    y = y1;
    ye = y2;
  }
      else
  {
    x = x2;
    y = y2;
    ye = y1;
  }
      A[x][y] = c;
      for (i = 0; y < ye; i++)
  {
    y = y + 1;
    if (py <= 0)
      {
        py = py + 2 * dx1;
      }
    else
      {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
    {
      x = x + 1;
    }
        else
    {
      x = x - 1;
    }
        py = py + 2 * (dx1 - dy1);
      }
    A[x][y] = c;
  }
    }
}
