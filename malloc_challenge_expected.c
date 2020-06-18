#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct metadata_t {
  int size;
  struct metadata_t *metadata;
} metadata_t;

double urand() {
  double m, a;
  m = (double)RAND_MAX + 1;
  a = (rand() + 0.5) / m;
  a = (rand() + a) / m;
  return (rand() + a) / m;
}

// Return an object size. The returned size is a random number in
// [min_size, max_size) that follows an exponential distribution.
// |min_size| needs to be a multiple of 8 bytes.
size_t get_object_size(size_t min_size, size_t max_size) {
  const int alignment = 8;
  assert(min_size <= max_size);
  assert(min_size % alignment == 0);
  const double lambda = 1;
  const double threshold = 6;
  double tau = -lambda * log(urand());
  if (tau >= threshold) {
    tau = threshold;
  }
  size_t result = (size_t)((max_size - min_size) * tau / (threshold + 1e-4)) + min_size;
  result = result / alignment * alignment;
  assert(min_size <= result);
  assert(result < max_size);
  return result;
}

// Return an object lifetime. The returned lifetime is a random number in
// [min_epoch, max_epoch] that follows an exponential distribution.
unsigned get_object_lifetime(unsigned min_epoch, unsigned max_epoch) {
  const double lambda = 1;
  const double threshold = 6;
  double tau = -lambda * log(urand());
  if (tau >= threshold) {
    tau = threshold;
  }
  unsigned result = (unsigned)((max_epoch - min_epoch) * tau / threshold + min_epoch);
  assert(min_epoch <= result);
  assert(result <= max_epoch);
  return result;
}

int main(void) {
  srand(100);
  for (int i = 0; i < 1000; i++) {
    printf("%ld\n", get_object_size(8, 4000));
  }
  return 0;
}
