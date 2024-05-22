#include <iostream>   // Input and output stream, used for standard I/O operations
#include <fstream>    // File stream, used for reading and writing to files
#include <iomanip>    // Input/output manipulators, used for formatting output
#include <cmath>      // Math functions, used for mathematical operations
#include <ctime>      // Time functions, used for working with time-related operations
#include <cstdlib>    // Standard library functions, used for general utility functions

using namespace std;

// Function to check if the given coordinates (x, y) are within the specified bounds.
bool boundsCheck(int x, int y, int minX, int minY, int maxX, int maxY);

// Function to simulate dropping a dirt ball onto a terrain map at a specific location and with a specified radius and power.
void dropDirtBall(int** terrainMap, int mapWidth, int mapHeight, int centerX, int centerY, int radius, int power);

// Function to find the maximum value in a 2D map of given dimensions.
int findMaxValue(int** map, int width, int height);

// Function to normalize a terrain map by scaling its values based on the maximum value found.
void normalizeTerrainMap(int** map, int width, int height, int maxVal);

// Function to print the values of a terrain map.
void printTerrainMap(int** map, int width, int height);

// Function to check the color associated with a numeric value in the terrain map.
int colorCheck(char value);

// Function to polish the terrain map by applying a water level and creating a corresponding character map.
void polishTerrainMap(int** map, int width, int height, int waterLevel, char** polishedMap);

// Function to print the values of a character map.
void printCharMap(char** map, int width, int height);

// Function to save a terrain map to a file with the specified filename.
void saveTerrainMapToFile(int** map, int width, int height, const char* filename);

// Function to save a character map to a file with the specified filename.
void saveCharMapToFile(char** map, int width, int height, const char* filename);

// Function to generate a random double value between 0 and 1
double generateRandomDouble();

int main(int argc, char** argv) {
  // Seed for random number generation
  int seed;
  if (argc > 2 && argv[1][1] == 's') {
    // Extract seed from command line arguments if provided
    seed = atoi(argv[2]);
  } else {
    // If no seed provided, use the current time as the seed
    seed = -1;
  }
  if (seed == -1) {
    srand(time(0));
  } else {
    srand(seed);
  }

  // User input for grid dimensions
  int width, height;
  cout << "Welcome to terraformer assignment!" << endl;
  cout << "Enter grid width: ";
  cin >> width;
  cout << "Enter grid height: ";
  cin >> height;

  // 2D array for terrainMap and polishedMap initialization
  int** terrainMap = new int*[height];
  for (int i = 0; i < height; i++) {
    terrainMap[i] = new int[width];
    // Initialize terrainMap with zeros
    fill_n(terrainMap[i], width, 0);
  }

  char** polishedMap = new char*[height];
  for (int i = 0; i < height; i++) {
    polishedMap[i] = new char[width];
  }

  // User input for simulation parameters
  int waterLevel;
  cout << "Enter value for water level (40-200): ";
  cin >> waterLevel;

  int dirtBallRadius;
  cout << "Enter dirt ball radius (minimum 2): ";
  cin >> dirtBallRadius;

  int dirtBallPower;
  cout << "Enter dirt ball power rating (minimum = radius): ";
  cin >> dirtBallPower;

  int numDirtBalls;
  cout << "Enter number of dirt balls to drop: ";
  cin >> numDirtBalls;

  // Simulation of dirt ball impact on terrainMap
  for (int k = 0; k < numDirtBalls; k++) {
    // Generate random coordinates for dirt ball impact
    int centerX = static_cast<int>(generateRandomDouble() * width);
    int centerY = static_cast<int>(generateRandomDouble() * height);
    // Drop dirt ball at random coordinates
    dropDirtBall(terrainMap, width, height, centerX, centerY, dirtBallRadius, dirtBallPower);
  }

  // Display and save the raw terrainMap
  cout << "Raw 2D array:" << endl;
  printTerrainMap(terrainMap, width, height);
  cout << endl;
  saveTerrainMapToFile(terrainMap, width, height, "raw_landmass.txt");

  // Normalize terrainMap values and polish the map
  int maxTerrainValue = findMaxValue(terrainMap, width, height);
  normalizeTerrainMap(terrainMap, width, height, maxTerrainValue);
  polishTerrainMap(terrainMap, width, height, waterLevel, polishedMap);

  // Display and save the normalized terrainMap
  cout << "Normalized 2D array:" << endl;
  printTerrainMap(terrainMap, width, height);
  cout << endl;
  saveTerrainMapToFile(terrainMap, width, height, "normalized_landmass.txt");

  // Display and save the final polished ASCII character array
  cout << "Polished ASCII character array:" << endl;
  printCharMap(polishedMap, width, height);
  cout << endl;
  saveCharMapToFile(polishedMap, width, height, "final_landmass.txt");

  // Deallocate memory for arrays
  for (int i = 0; i < height; i++) {
    delete[] terrainMap[i];
    delete[] polishedMap[i];
  }
  delete[] terrainMap;
  delete[] polishedMap;

  return 0;
}


// Function to check if coordinates are within bounds
bool boundsCheck(int x, int y, int minX, int minY, int maxX, int maxY) {
  return (minX <= x && x < maxX && minY <= y && y < maxY);
}

// Function to simulate the impact of dropping a dirt ball on terrainMap
void dropDirtBall(int** terrainMap, int mapWidth, int mapHeight, int centerX, int centerY, int radius, int power) {
  // Iterate over each cell in the terrainMap
  for (int i = 0; i < mapHeight; i++) {
    for (int j = 0; j < mapWidth; j++) {
      // Check if the current cell is within the bounds of the terrainMap
      if (boundsCheck(j, i, 0, 0, mapWidth, mapHeight)) {
        // Calculate the distance between the current cell and the center of the dirt ball
        int dx = j - centerX;
        int dy = i - centerY;
        double distance = sqrt(dx * dx + dy * dy);

        // Check if the distance is within the radius of the dirt ball
        if (distance <= radius) {
          // Calculate the impact based on the power and distance from the center
          int impact = max(0, power - static_cast<int>(distance));

          // Update the terrainMap at the current cell with the impact value
          terrainMap[i][j] += impact;
        }
      }
    }
  }
}

// Function to find the maximum value in terrainMap
int findMaxValue(int** map, int width, int height) {
  // Initialize maxVal with the value at the top-left corner of terrainMap
  int maxVal = map[0][0];

  // Iterate over each cell in the terrainMap
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Update maxVal if the value at the current cell is greater
      maxVal = max(maxVal, map[i][j]);
    }
  }

  // Return the maximum value found in terrainMap
  return maxVal;
}

// Function to normalize terrainMap values
void normalizeTerrainMap(int** map, int width, int height, int maxVal) {
  // Iterate over each cell in the terrainMap
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Normalize the value at the current cell using the formula: (value / maxVal) * 255
      // The result is cast to an integer to ensure it falls within the valid range [0, 255]
      map[i][j] = static_cast<int>((static_cast<double>(map[i][j]) / maxVal) * 255);
    }
  }
}

// Function to display terrainMap
void printTerrainMap(int** map, int width, int height) {
  // Iterate over each row in the terrainMap
  for (int i = 0; i < height; i++) {
    // Iterate over each column in the terrainMap
    for (int j = 0; j < width; j++) {
      // Display the value at the current cell, formatted to a width of 4 characters
      cout << setw(4) << map[i][j];
    }
    // Move to the next line after printing a row
    cout << endl;
  }
}

// Function to polish the terrainMap and create an ASCII character map
void polishTerrainMap(int** map, int width, int height, int waterLevel, char** polishedMap) {
  // Define thresholds and characters for different elevation levels
  int landZone = 255 - waterLevel;
  int halfWater = waterLevel / 2;
  int fifteenPercent = static_cast<int>(landZone * 0.15);
  int fortyPercent = static_cast<int>(landZone * 0.4);
  int eightyPercent = static_cast<int>(landZone * 0.8);

  // Iterate over each cell in the terrainMap
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Check if the elevation at the current cell is below or equal to waterLevel
      if (map[i][j] <= waterLevel) {
        // Set characters '#' for elevations below half of waterLevel, and '~' for the rest
        polishedMap[i][j] = (map[i][j] < halfWater) ? '#' : '~';
      } else {
        // Check different elevation ranges and assign corresponding characters
        if (map[i][j] < (waterLevel + fifteenPercent)) {
          polishedMap[i][j] = '.';
        } else if (map[i][j] >= (waterLevel + fifteenPercent) && map[i][j] < (waterLevel + fortyPercent)) {
          polishedMap[i][j] = '-';
        } else if (map[i][j] >= (waterLevel + fortyPercent) && map[i][j] < (waterLevel + eightyPercent)) {
          polishedMap[i][j] = '*';
        } else {
          polishedMap[i][j] = '^';
        }
      }
    }
  }
}

// Function to display a character map
void printCharMap(char** map, int width, int height) {
  // Iterate over each row in the character map
  for (int i = 0; i < height; i++) {
    // Iterate over each column in the character map
    for (int j = 0; j < width; j++) {
      // Display the character at the current cell
      cout << map[i][j];
    }
    // Move to the next line after printing a row
    cout << endl;
  }
}

// Function to save terrainMap to a file
void saveTerrainMapToFile(int** map, int width, int height, const char* filename) {
  // Open a file with the specified filename for writing
  ofstream file(filename);

  // Check if the file is successfully opened
  if (file.is_open()) {
    // Iterate over each row in the terrainMap
    for (int i = 0; i < height; i++) {
      // Iterate over each column in the terrainMap
      for (int j = 0; j < width; j++) {
        // Write the value at the current cell to the file, formatted to a width of 4 characters
        file << setw(4) << map[i][j];
      }
      // Move to the next line after writing a row
      file << endl;
    }

    // Close the file after writing
    file.close();
    // Display a success message if the map is saved
    cout << "Map saved to " << filename << endl;
  } else {
    // Display an error message if the file cannot be opened
    cout << "Failed to save the map to " << filename << endl;
  }
}

// Function to save a character map to a file
void saveCharMapToFile(char** map, int width, int height, const char* filename) {
  // Open a file with the specified filename for writing
  ofstream file(filename);

  // Check if the file is successfully opened
  if (file.is_open()) {
    // Iterate over each row in the character map
    for (int i = 0; i < height; i++) {
      // Iterate over each column in the character map
      for (int j = 0; j < width; j++) {
        // Write the character at the current cell to the file
        file << map[i][j];
      }
      // Move to the next line after writing a row
      file << endl;
    }

    // Close the file after writing
    file.close();
    // Display a success message if the map is saved
    cout << "Map saved to " << filename << endl;
  } else {
    // Display an error message if the file cannot be opened
    cout << "Failed to save the map to " << filename << endl;
  }
}

// Function to generate a random double between 0 and 1
double generateRandomDouble() {
  return static_cast<double>(rand()) / (static_cast<long>(RAND_MAX) + 1);
}