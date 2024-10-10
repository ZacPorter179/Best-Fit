#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;
//1 FUNCTION TO READ XY AND STORE IN DYNAMIC ARRAY
double *ReadData(const string &fileName, int &length){
  ifstream inFile(fileName);
  if(!inFile.is_open()) {
    cout << "Error opening file " << fileName << endl;
    exit(1);
  }
  length = 0;
  double d1, d2;
  while (inFile >> d1 >> d2) {
    ++length;
  }
  inFile.clear();
  inFile.seekg(0, ios::beg);
  double *data = new double[length * 2]; //TWO COLUMNS
  for (int i = 0; i < length * 2; i += 2){
    inFile >> data[i] >> data[i + 1];
  }
  inFile.close();
  return data; //COME BACK TO THIS LATER
}
//2 FUNCTION TO CALCULATE MEAN
double CalcMean(const double *array, int length){
  double sum = 0.0;
  for (int i = 0; i < length; ++i){
    sum += array[i];
  }
  return sum / length;
}
//3 FUNCTION TO CALCULATE FITM AND FITB
void ComputeFit(const double *data, int length, double &fitm, double &fitb){
  double sumx = 0.0, sumy = 0.0, sumxy = 0.0, sumxx = 0.0;
  for (int i = 0; i < length *2; i += 2){
    sumx += data[i];
    sumy += data[i + 1];
    sumxy += data[i] * data[i + 1];
    sumxx += data[i] * data[i];
  }
  fitm = (length * sumxy - sumx * sumy) / (length * sumxx - sumx * sumx);
  fitb = (sumy - fitm * sumx) / length;
}
//4 FUNCTION TO CALCULATE FITY
double *CalcFitY(const double *x, const double *y, int length, double fitm, double fitb) {
  double *fity = new double[length];
  for (int i = 0; i < length; ++i) {
    fity[i] = fitm * x[i] + fitb;
  }
  return fity;
}
//5 FUNCTION TO WRITE 3 COLUMNS OF DATA TO FILE
void WriteArraysToFile(const double *x, const double *y, const double *fity, int length, const string &fileName){
  ofstream outFile(fileName);
  if (!outFile.is_open()) {
    cout << "Error opening file " << fileName << endl;
    exit(1);
  }
  for (int i = 0; i < length; ++i) {
    outFile << x[i] << " " << y[i] << " " << fity[i] << endl;
  }
  outFile.close();
}
//MAIN
int main() {
  string filename = "numbers.txt";
  int length;
  double *data = ReadData(filename, length);
  double fitm, fitb;
  ComputeFit(data, length, fitm, fitb);
  double *x = new double[length];
  double *y = new double[length];
  double *fity;
  for (int i = 0; i < length; ++i) {
    x[i] = data[i * 2];
    y[i] = data[i * 2 + 1];
  }
  fity = CalcFitY(x, y, length, fitm, fitb);
  WriteArraysToFile(x, y, fity, length, "output.txt");
  delete[] data;
  delete[] x;
  delete[] y;
  delete[] fity;
  return 0;
}