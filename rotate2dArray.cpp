#include "Display.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const int N = 500; // Image Size N x N
short Pixels[N][N];

void rotateImageInPlace(float theta);
void drawLine(short Pixels[N][N], int x0, int y0, int x1, int y1);

void rotateImageInPlace(float theta) {
  short tempPixels[N][N];
  int background = 0; // Background color

  for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
          tempPixels[r][c] = Pixels[r][c];
      }
  }
  
  // Convert degrees to radians
  float rads = theta * 3.1415926 / 180.0; // fixed constant PI
  float cs = cos(-rads);                  // precalculate these values
  float ss = sin(-rads);
  float xcenter = float(N) / 2.0; // use float here!
  float ycenter = float(N) / 2.0;
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      // now find the pixel of the original image that is rotated to (r,c)
      // rotation formula assumes that origin = top-left and y points down
      int rorig =
          ycenter + ((float)(r)-ycenter) * cs - ((float)(c)-xcenter) * ss;
      int corig =
          xcenter + ((float)(r)-ycenter) * ss + ((float)(c)-xcenter) * cs;
      // now get the pixel value if you can
      int pixel = background; // in case there is no original pixel
      if (rorig >= 0 && rorig < N && corig >= 0 && corig < N) {
          Pixels[r][c] = tempPixels[rorig][corig];
      } else {
          Pixels[r][c] = background;
      }
    }
  }
}

void drawLine(short Pixels[N][N], int x0, int y0, int x1, int y1) {
  // To be able to use a for loop on x value, we need to make sure dy is
  // smaller than dx, meaning slope of line is smaller than 1 Otherwise,
  // swapping x and y values effectively rotates the line to a horizontal
  // orientation
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }
  // If 1st coordinate is further than 2nd, swap
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }
  int dx = x1 - x0;
  int dy = abs(y1 - y0);
  int error = dx / 2;
  int ystep = (y0 < y1) ? 1 : -1;
  int y = y0;
  for (int x = x0; x <= x1; x++) {
    if (steep) {
      Pixels[x][y] = 255; // Assuming 255 is the color value for the line
    } else {
      Pixels[y][x] = 255;
    }
    error -= dy;
    if (error < 0) {
      y += ystep;
      error += dx;
    }
  }
}

int main() {

  int center_x = 330;
  int center_y = 160;
  int radius = 50;

  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      // Draw square from if statements
      if (row >= 300 && row <= 440 && col >= 60 && col <= 200) {
        Pixels[row][col] = 125;
      }
      // Draw circle using (x-h)^2 + (y-k)^2 = r^2 where (h, k) is center

      if ((col - center_x) * (col - center_x) +
              (row - center_y) * (row - center_y) <=
          radius * radius) {
        Pixels[row][col] = 255;
      }

      drawLine(Pixels, 40, 40, 100, 270);
      drawLine(Pixels, 250, 460, 480, 380);
    }
  }

  Display image(Pixels, "output1");

  rotateImageInPlace(45);

  Display image2(Pixels, "output2");

  return 0;
}
