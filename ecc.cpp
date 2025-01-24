#include <string>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#define NUM_DATA_BITS 128

using namespace std;



int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: ./hammersim_ecc <data> <path to parity matrix>" << endl;
    exit(1);
  }

  uint8_t data[16];
  convertHexToUint8Array(hexValue, data);
  
  string dataHex = loadData(argv[1]);
  string dataHex = argv[1];

  uint8_t data[16];
  
  for (size_t i = 0; i < 16; ++i) {
    data[i] = static_cast<uint8_t>(stoi(dataHex.substr(i * 2, 2), nullptr, 16));
  }

  for (int i = 0; i < 16; ++i) {
    cout << static_cast<int>(data[i]) << " ";
  }

  cout << endl;
  return 0;
}
