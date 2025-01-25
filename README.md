# Hammersim ECC

## ECC implementation for [Hammersim](https://arch.cs.ucdavis.edu/assets/papers/yarch-hammersim.pdf) based on  [ECCploit](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8835222)

### Usage:
```
make clean
make
./hammersim_ecc <data 128-bit hex string> <path to parity matrix text file>
```

### Note:
- `pMatrix.txt` is a sample parity matrix text file
- `0123456789abcdef0123456789abcdef` is an example for a 128-bit hex string
- Prints the data as a `uint8_t` array of size 16 and the data with ecc bits added as a `uint8_t` array of size 18.
- Assumes 16 ECC bits