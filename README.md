# 2D-terrainmaps
A C++ terraforming simulation tool that generates and manipulates 2D terrain maps by simulating the impact of dropping dirt balls and applying water levels. Outputs raw, normalized, and polished ASCII representations of the landmass.
## Introduction
Terraformer Simulation is a C++ program designed to simulate the impact of dropping dirt balls onto a terrain map and generate a polished ASCII character map representing the terrain with different elevation levels. This README provides comprehensive information about the program's functionality, usage, customization options, and more.

## Features
- **Terrain Map Simulation**: Simulates the impact of dropping dirt balls onto a 2D terrain map.
- **Normalization**: Normalizes terrain map values to a specific range.
- **Polishing**: Polishes the terrain map to create an ASCII character map representing different elevation levels.
- **User Interaction**: Allows users to input parameters such as grid dimensions, water level, dirt ball parameters, and number of dirt balls to drop.
- **File Saving**: Saves the raw, normalized, and polished terrain maps to text files for further analysis or visualization.

## Dependencies
- C++ Standard Library

## Installation and Usage
1. **Clone the Repository**: Clone or download the repository to your local machine.
2. **Compile the Source Code**: Compile the source code using a C++ compiler (e.g., g++).
3. **Run the Executable**: Execute the compiled binary to run the program.
4. **Follow On-Screen Instructions**: Input parameters as prompted to simulate the terrain and view the results.
5. **Explore Generated Files**: Explore the generated text files to analyze the terrain maps.

## Input Parameters
- **Grid Dimensions**: Specify the width and height of the terrain map grid.
- **Water Level**: Set the water level within the range of 40 to 200.
- **Dirt Ball Parameters**: Define the radius and power rating of the dirt balls to be dropped.
- **Number of Dirt Balls**: Input the number of dirt balls to simulate.

## Generated Files
- `raw_landmass.txt`: Raw terrain map with unprocessed values.
- `normalized_landmass.txt`: Terrain map with normalized values.
- `final_landmass.txt`: Polished ASCII character map representing the terrain.

## Functionality Overview
1. **Bounds Check**: Checks if coordinates are within the bounds of the terrain map.
2. **Dirt Ball Impact**: Simulates the impact of dropping dirt balls onto the terrain map.
3. **Maximum Value Finder**: Finds the maximum value in the terrain map.
4. **Terrain Map Normalization**: Normalizes terrain map values to a specified range.
5. **Terrain Map Display**: Displays the terrain map with formatted values.
6. **Polishing**: Polishes the terrain map and creates an ASCII character map representing different elevation levels.
7. **Character Map Display**: Displays the ASCII character map representing the terrain.
8. **File Saving**: Saves the terrain maps to text files for further analysis.

## Customization
- **Parameter Adjustment**: Modify simulation parameters or adjust the range of values for customization.
- **ASCII Character Customization**: Customize the ASCII characters used to represent different elevation levels in the polished map.
