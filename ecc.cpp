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

vector<vector<uint8_t> > loadPMatrix(const string& pMatrixPath) {
  ifstream file(pMatrixPath);
  string line;
  
  vector<vector<uint8_t> > pMatrix;
  
  while (getline(file, line)) {
    stringstream ss(line);
    
    vector<uint8_t> pMatrixRow;
    
    uint8_t value;
    while (ss >> value) {
      pMatrixRow.push_back(static_cast<uint8_t>(value));
    }
    pMatrix.push_back(pMatrixRow);
  }
  file.close();
  
  return pMatrix;
}

vector<vector<uint8_t> > attachToIdentityMatrix(const vector<vector<uint8_t> >& pMatrix) {
  vector<vector<uint8_t> > gMatrix(NUM_DATA_BITS, vector<uint8_t>(NUM_DATA_BITS + NUM_ECC_BITS, 0));

  for (size_t i = 0; i < NUM_DATA_BITS; ++i) {
    gMatrix[i][i] = 1;
  }

  for (size_t i = 0; i < NUM_DATA_BITS; ++i) {
    for (size_t j = 0; j < NUM_ECC_BITS; ++j) {
      gMatrix[i][NUM_DATA_BITS + j] = pMatrix[i][j];
    }
  }

  return gMatrix;
}

vector<uint8_t> binaryVectorMatrixMultiplication(const vector<uint8_t>& data, const vector<vector<uint8_t> >& gMatrix) {
  vector<uint8_t> result(NUM_DATA_BITS + NUM_ECC_BITS, 0);
  
  for (size_t j = 0; j < NUM_DATA_BITS + NUM_ECC_BITS; ++j) {
    for (size_t i = 0; i < NUM_DATA_BITS; ++i) {
      result[j] ^= (data[i] & gMatrix[i][j]);
    }
  }
  
  return result;
}

vector<uint8_t> uint8ArrayToBinary(const uint8_t* data, size_t size) {
  vector<uint8_t> binaryArray;
  
  for (size_t i = 0; i < size; i++) {
    for (int j = 7; j >= 0; j--) {
      binaryArray.push_back(static_cast<uint8_t>((data[i] >> j) & 1));
    }
  }

  return binaryArray;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: ./hammersim_ecc <data> <path to parity matrix>" << endl;
    exit(1);
  }

  uint8_t data[NUM_DATA_BITS / BITS_PER_BYTE];
  loadUint8Array(argv[1], data);
  
  vector<uint8_t> binaryArray = uint8ArrayToBinary(data, NUM_DATA_BITS / BITS_PER_BYTE);
  vector<vector<uint8_t> > pMatrix = loadPMatrix(argv[2]);
  
  vector<vector<uint8_t> > gMatrix = attachToIdentityMatrix(pMatrix);

  vector<uint8_t> resultBinary = binaryVectorMatrixMultiplication(binaryArray, gMatrix);
  
  cout << resultBinary.size() << endl;

  for (int i = 0; i < resultBinary.size(); i++) {
    cout << static_cast<int>(resultBinary[i]);
  }
  cout << endl;
  for (int i = 0; i < binaryArray.size(); i++) {
    cout << static_cast<int>(binaryArray[i]);
  }
  cout << endl;
  return 0;
}
