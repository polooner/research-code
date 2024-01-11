#include "Display.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int N = 180;
int Pixels[N][N];   // Original Phantom matrix
int Sinogram[N][N]; // Sinogram matrix
int Reconstruction[N][N];

void rotateImageInPlace(int image[N][N], float theta);
void createSinogram(int Pixels[N][N], int Sinogram[N][N]);
void loadImage(int Pixels[N][N], string fileName);
void backProject(int Reconstruction[N][N], int Sinogram[N][N]);
void scale2DArray(int arr[N][N]);

void scale2DArray(int arr[N][N]) {
  int max_value = 0;
  for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
          if (arr[i][j] > max_value) {
              max_value = arr[i][j];
          }
      }
  }

  if (max_value > 0) {
      for (int i = 0; i < N; ++i) {
          for (int j = 0; j < N; ++j) {
              arr[i][j] = (arr[i][j] * 255) / max_value;
          }
      }
  }
}

void loadImage(int Pixels[N][N], string fileName) {
  cout << "loading image\n";
  ifstream file(fileName);
  if (!file) {
    cout << "File does not exist!\n";
    return;
  }
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      file >> Pixels[row][col];
  file.close();
}

void createSinogram(int Pixels[N][N], int Sinogram[N][N]) {
  // Initialize Sinogram with zeroes

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      Sinogram[i][j] = 0;
    }
  }

  for (int angle = 0; angle < 180; ++angle) {
    int tempPixels[N][N];
    memcpy(tempPixels, Pixels,
           sizeof(int) * N * N);         // Copy the original matrix
    rotateImageInPlace(tempPixels, (angle * - 1)); // Rotate the copied matrix

    for (int col = 0; col < N; ++col) {
      int sum = 0;
      for (int row = 0; row < N; ++row) {
        sum += tempPixels[row][col];
      }
      Sinogram[angle][col] = sum;
    }
  }
}

void rotateImageInPlace(int image[N][N], float theta) {
  int tempPixels[N][N];
  int background = 0; // Background color

  // Convert degrees to radians
  float rads = theta * M_PI / 180.0; // Use M_PI for Pi
  float cs = cos(-rads);             // Pre-calculate these values
  float ss = sin(-rads);
  float xcenter = float(N) / 2.0;
  float ycenter = float(N) / 2.0;
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < N; ++c) {
      int rorig =
          ycenter + ((float)(r)-ycenter) * cs - ((float)(c)-xcenter) * ss;
      int corig =
          xcenter + ((float)(r)-ycenter) * ss + ((float)(c)-xcenter) * cs;

      int pixel = background; // Default to background color
      if (rorig >= 0 && rorig < N && corig >= 0 && corig < N) {
        tempPixels[r][c] = image[rorig][corig];
      } else {
        tempPixels[r][c] = background;
      }
    }
  }

  memcpy(image, tempPixels,
         sizeof(int) * N * N); // Copy the rotated image back
}

void backProject(int Reconstruction[N][N], int Sinogram[N][N]) {
    memset(Reconstruction, 0, sizeof(int) * N * N);

    for (int angle = 0; angle < 180; ++angle) {
        int Temp[N][N];
        memset(Temp, 0, sizeof(int) * N * N); // Initialize Temp to all zeros

        // Spread a sinogram row into Temp array
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                Temp[i][j] = Sinogram[angle][i];
            }
        }

        // Rotate the Temp image
        rotateImageInPlace(Temp, angle);

        // Backproject the sinogram onto the reconstruction array
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                Reconstruction[i][j] += Temp[i][j];
            }
        }
    }
}

int main() {
    // Load image into Pixels
    loadImage(Pixels, "shapesPhantom.txt"); // Replace filename.txt with your actual file name

    // Fill the Sinogram
    createSinogram(Pixels, Sinogram);

    // Scale the Sinogram for display purposes
    scale2DArray(Sinogram);

    // Display or further process the Sinogram as needed
    Display sinogramImage(Sinogram, "Sinogram Output");

    // Reconstruct the image from the Sinogram
    backProject(Reconstruction, Sinogram);

  // Scale reconstruction
    
    scale2DArray(Reconstruction);
    

    rotateImageInPlace(Reconstruction, 90);

    Display reconstructedImage(Reconstruction, "Reconstructed Output");

    return 0;
}
