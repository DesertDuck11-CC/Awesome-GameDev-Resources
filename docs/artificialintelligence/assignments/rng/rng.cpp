#include <fstream>
#include <iostream>
#include <istream>
#include <cstdint>

const std::string TEST_FOLDER = "\\tests\\";

struct PRNG {
private:
  unsigned int seed;

public:
  PRNG(unsigned int seed) : seed(seed) {}

  unsigned int lfsr(unsigned int min, unsigned int max) {
    // XOR shifts a bit after extracting the 1st, 3rd, 5th and 6th bit which then gets masked 
    // using the "1u" value to ensure it stays as a single bit
    unsigned int bit = ((seed >> 0) ^ (seed >> 2) ^ (seed >> 4) ^ (seed >> 5)) & 1u;
    // The seed is then right-shifted by 1  dropping the least significant bit and then right-shifting 
    // all other bits by 1 position. Then the previous bit is left-shifted by 15 bits
    // and inserted into the seed giving you a random number
    seed = (seed >> 1) | (bit << 15);

    // Clamps between the random number between the min and max value given
    return min + (seed % (max - min + 1));
  }
};

int main(){
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;

  PRNG lfsr(seed);

  for (size_t i = 0; i < N; i++) 
  {
    std::cout << lfsr.lfsr(min, max) << std::endl;
  }
}
