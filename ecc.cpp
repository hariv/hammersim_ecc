#include <vector>
#include <string>
#include <bitset>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#define NUM_DATA_BITS 128
#define NUM_ECC_BITS 16
#define BITS_PER_BYTE 8

using namespace std;

void loadUint8Array(string hexValue, uint8_t data[16]) {
  for (size_t i = 0; i < NUM_DATA_BITS / BITS_PER_BYTE;  i++) {
    data[i] = static_cast<uint8_t>(stoi(hexValue.substr(i*2, 2), nullptr, 16));
  }
}

void loadPMatrix(const string& pMatrixPath, uint8_t pMatrix[NUM_DATA_BITS][NUM_ECC_BITS]) {
  ifstream file(pMatrixPath);

  string line;
  int row = 0;

  while (getline(file, line)) {
    stringstream ss(line);
    int col = 0;
    int value;
    while (ss >> value) {
      pMatrix[row][col] = static_cast<uint8_t>(value);
      col++;
    }
    row++;
  }
  file.close();
}

//vector<vector<int> > uint8ArrayToBinary(const uint8_t* data, size_t size) {
vector<int> uint8ArrayToBinary(const uint8_t* data, size_t size) {
  
  //vector<vector<int> >binaryArray;
  vector<int> binaryArray;

  for (size_t i = 0; i < size; i++) {
    //vector<int> binary;
    //binary.reserve(8);

    for (int j = 7; j >= 0; j--) {
      binaryArray.push_back((data[i] >> j) & 1);
      //binary.push_back((data[i] >> j) & 1);
    }
    //binaryArray.push_back(binary);
  }

  return binaryArray;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: ./hammersim_ecc <data> <path to parity matrix>" << endl;
    exit(1);
  }

  uint8_t data[NUM_DATA_BITS / BITS_PER_BYTE];
  uint8_t pMatrix[NUM_DATA_BITS][NUM_ECC_BITS];
  
  loadUint8Array(argv[1], data);
  loadPMatrix(argv[2], pMatrix);

  //vector<vector<uint8_t> > binaryData;
  //vector<bitset<BITS_PER_BYTE> > binaryData;
  
  //vector<vector<int >> binaryArray = uint8ArrayToBinary(data, NUM_DATA_BITS / BITS_PER_BYTE);
  vector<int> binaryArray = uint8ArrayToBinary(data, NUM_DATA_BITS / BITS_PER_BYTE);
  
  for (int bit : binaryArray) {
    cout << bit;
  }
  cout << endl;
  /*for (int i = 0; i < NUM_DATA_BITS; i++) {
    for (int j = 0; j < NUM_ECC_BITS; j++) {
      cout << static_cast<int>(pMatrix[i][j]) << " " ;
    }
    cout << endl;
  }*/
  
  return 0;
}
