#include <fstream> // Include file stream library for file operations
#include <iostream> // Include input/output stream library
#include <cmath> // Include math library for mathematical operations
using namespace std; // Use the standard namespace

// FUNCTION TO READ XY AND STORE IN DYNAMIC ARRAY
double *ReadData(const string &fileName, int &length) {
  ifstream inFile(fileName); // Open the input file
  if (!inFile.is_open()) { // Check if the file is opened successfully
    cout << "Error opening file " << fileName << endl; // Print error message
    exit(1); // Exit the program with an error code
  }
  length = 0; // Initialize length variable
  double d1, d2; // Variables to store data values
  while (inFile >> d1 >> d2) { // Read two values per line
    ++length; // Increment length count
  }
  inFile.clear(); // Clear end-of-file flag
  inFile.seekg(0, ios::beg); // Reset file position to beginning
  double *data = new double[length * 2]; // Allocate memory for data array (two columns)
  for (int i = 0; i < length * 2; i += 2) { // Loop through array indices
    inFile >> data[i] >> data[i + 1]; // Read x and y values into the array
  }
  inFile.close(); // Close the file
  return data; // Return pointer to the allocated data array
}

// FUNCTION TO CALCULATE MEAN
double CalcMean(const double *array, int length) {
  double sum = 0.0; // Initialize sum variable
  for (int i = 0; i < length; ++i) { // Loop through array elements
    sum += array[i]; // Add element to sum
  }
  return sum / length; // Return mean value
}

// FUNCTION TO CALCULATE FITM AND FITB
void ComputeFit(const double *data, int length, double &fitm, double &fitb) {
  double sumx = 0.0, sumy = 0.0, sumxy = 0.0, sumxx = 0.0; // Initialize summation variables
  for (int i = 0; i < length * 2; i += 2) { // Loop through data array (two columns)
    sumx += data[i]; // Sum of x values
    sumy += data[i + 1]; // Sum of y values
    sumxy += data[i] * data[i + 1]; // Sum of x * y
    sumxx += data[i] * data[i]; // Sum of x squared
  }
  fitm = (length * sumxy - sumx * sumy) / (length * sumxx - sumx * sumx); // Calculate slope (m)
  fitb = (sumy - fitm * sumx) / length; // Calculate y-intercept (b)
}

// FUNCTION TO CALCULATE FITTED Y VALUES
double *CalcFitY(const double *x, const double *y, int length, double fitm, double fitb) {
  double *fity = new double[length]; // Allocate memory for fitted y values
  for (int i = 0; i < length; ++i) { // Loop through x values
    fity[i] = fitm * x[i] + fitb; // Compute fitted y value
  }
  return fity; // Return pointer to fitted y values array
}

// FUNCTION TO WRITE 3 COLUMNS OF DATA TO FILE
void WriteArraysToFile(const double *x, const double *y, const double *fity, int length, const string &fileName) {
  ofstream outFile(fileName); // Open output file
  if (!outFile.is_open()) { // Check if file is opened successfully
    cout << "Error opening file " << fileName << endl; // Print error message
    exit(1); // Exit the program with an error code
  }
  for (int i = 0; i < length; ++i) { // Loop through all data points
    outFile << x[i] << " " << y[i] << " " << fity[i] << endl; // Write x, y, and fitted y to file
  }
  outFile.close(); // Close output file
}

// MAIN FUNCTION
int main() {
  string filename = "numbers.txt"; // Define input file name
  int length; // Variable to store number of data points
  double *data = ReadData(filename, length); // Read data from file
  double fitm, fitb; // Variables to store slope and intercept
  ComputeFit(data, length, fitm, fitb); // Compute linear regression parameters
  double *x = new double[length]; // Allocate memory for x values
  double *y = new double[length]; // Allocate memory for y values
  double *fity; // Pointer for fitted y values
  for (int i = 0; i < length; ++i) { // Loop through data array
    x[i] = data[i * 2]; // Extract x values
    y[i] = data[i * 2 + 1]; // Extract y values
  }
  fity = CalcFitY(x, y, length, fitm, fitb); // Calculate fitted y values
  WriteArraysToFile(x, y, fity, length, "output.txt"); // Write results to output file
  delete[] data; // Free allocated memory for data
  delete[] x; // Free allocated memory for x values
  delete[] y; // Free allocated memory for y values
  delete[] fity; // Free allocated memory for fitted y values
  return 0; // Return successful execution code
}
