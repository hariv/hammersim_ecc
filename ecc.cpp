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

void uint8ArrayToBinaryArray(const uint8_t* data, size_t size,
			     vector<bitset<BITS_PER_BYTE> >& binaryData) {
  for (size_t i = 0; i < size; i++) {
    binaryData.push_back(bitset<BITS_PER_BYTE>(data[i]));
  }
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
  vector<bitset<BITS_PER_BYTE> > binaryData;
  
  
  uint8ArrayToBinaryArray(data, NUM_DATA_BITS / BITS_PER_BYTE, binaryData);

  for (const auto& byte: binaryData) {
    for (uint8_t bit : byte) {
      cout << static_cast<int>(bit);
    }
    cout << " " ;
  }
  
  /*for (int i = 0; i < NUM_DATA_BITS; i++) {
    for (int j = 0; j < NUM_ECC_BITS; j++) {
      cout << static_cast<int>(pMatrix[i][j]) << " " ;
    }
    cout << endl;
  }*/
  
  return 0;
}
