////////////////////////////////////////////////////
//     **** Malloc Challenge!! (◍＞◡＜◍) ****     //
////////////////////////////////////////////////////

//
// Your job is to invent a smart malloc algorithm!
// 
// Rules:
//
// 1. Your job is to implement my_malloc(), my_free() and my_initialize().
//   *  my_initialize() is called only once at the beginning of each challenge.
//      You can initialize the memory allocator.
//   *  my_malloc(size) is called every time an object is allocated. In this
//      challenge, |size| is guaranteed to be a multiple of 8 bytes and smaller
//      than 4000 bytes.
//   * my_free(ptr) is called every time an object is freed.
// 2. The only library functions you can use in my_malloc() and my_free() are
//    _mmap() and _munmap().
//   *  _mmap(size) allocates |size| bytes from the OS. |size| needs to be
//      a multiple of 4096 bytes. _mmap(size) is a system call and heavy. You
//      are expected to minimize the call of _mmap(size) by reusing the returned
//      memory region as much as possible.
//   *  _munmap(ptr, size) frees the memory region [ptr, ptr + size). |ptr| and
//      |size| need to be a multiple of 4096 bytes. You are expected to free
//      memory regions that are unused.
//   *  You are not allowed to use any other library functions at all, including
//      the default malloc() / free(), std:: libraries etc. This is because you
//      are implementing malloc itself -- if you use something that may use
//      malloc, it will result in infinite recurions.
// 3. simple_malloc(), simple_free() and simple_initialize() are an example,
//    straightforward implementation of malloc. Your job is to invent a smarter
//    malloc algorithm than the simple malloc.
// 4. There are four challenges (Challenge 1, 2, 3 and 4). Each challenge
//    allocates and frees many objects with different patterns. Your malloc
//    algorithm is evaluated by two criteria.
//   *  [Execution time] How faster your malloc algorithm finishes the challange
//      compared to the simple malloc.
//   *  [Memory utilization] How much your malloc algirhtm is memory efficient.
//      This is defined as (S1 / S2), where S1 is the total size of objects
//      allocated at the end of the challange and S2 is the total size of
//      _mmap()ed regions at the end of the challenge. You can improve the
//      memory utilization by decreasing memory fragmentation and reclaiming
//      unused memory regions to the system with _munmap().
// 5. You need to specify an '-lm' option to compile this program.
//   *  gcc malloc_challenge.c -lm
//   *  clang malloc_challenge.c -lm

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void* _mmap(size_t size);
void _munmap(void* ptr, size_t size);

////////////////////////////////////////////////////////////////////////////////

//
// [Simple malloc]
//
// This is an example, straightforward implementation of malloc. Your goal is
// to invent a smarter malloc algorithm in terms of both [Execution time] and
// [Memory utilization].

// Each object has metadata just prior to the object or a free slot.
// |m| indicates metadata.
//
// ... | m | object | m | free slot | m | free slot | m | object | ...
//
// The metadata is needed for two purposes:
//
// 1) For an allocated object:
//   *  |size| indicaes the size of the object. |size| does not include
//      the size of the metadata.
//   *  |next| is unused and set to NULL.
// 2) For a free slot:
//   *  |size| indicates the size of the free slot. |size| does not include
//      the size of the metadata.
//   *  The free slots are linked as a singly linked list (free list). |next|
//      points to the next free slot.
typedef struct simple_metadata_t {
  size_t size;
  struct simple_metadata_t* next;
} simple_metadata_t;

// Simple malloc heap.
//   *  |free_head| points to the first free slot.
//   *  |dummy| is a dummy free slot (to make the implementation simpler).
typedef struct simple_heap_t {
  simple_metadata_t* free_head;
  simple_metadata_t dummy;
} simple_heap_t;

simple_heap_t simple_heap;

// Add a free slot to the beginning of the free list.
void simple_add_to_free_list(simple_metadata_t* metadata) {
  assert(!metadata->next);
  metadata->next = simple_heap.free_head;
  simple_heap.free_head = metadata;
}

// Remove a free slot from the free list.
void simple_remove_from_free_list(simple_metadata_t* metadata, simple_metadata_t* prev) {
  if (prev) {
    prev->next = metadata->next;
  } else {
    simple_heap.free_head = metadata->next;
  }
  metadata->next = NULL;
}

// This is called only once at the beginning of each challenge.
void simple_initialize() {
  simple_heap.free_head = &simple_heap.dummy;
  simple_heap.dummy.size = 0;
  simple_heap.dummy.next = NULL;
}

// This is called every time an object is allocated. |size| is guaranteed
// to be a multiple of 8 bytes and smaller than 4000 bytes.
void* simple_malloc(size_t size) {
  simple_metadata_t* metadata = simple_heap.free_head;
  simple_metadata_t* prev = NULL;
  // First-fit: Find the first free slot the object fits.
  while (metadata && metadata->size < size) {
    prev = metadata;
    metadata = metadata->next;
  }
  
  if (!metadata) {
    // There was no free slot available. We need to request a new memory region
    // from the system calling _mmap().
    size_t buffer_size = 4096;
    simple_metadata_t* metadata = (simple_metadata_t*)_mmap(buffer_size);
    metadata->size = buffer_size - sizeof(simple_metadata_t);
    metadata->next = NULL;
    // Add the memory region to the free list.
    simple_add_to_free_list(metadata);
    // Now, try simple_malloc() again. This should succeed.
    return simple_malloc(size);
  }

  // |ptr| is the beginning of the object address.
  void* ptr = metadata + 1;
  size_t remaining_size = metadata->size - size;
  metadata->size = size;
  // Remove the free slot from the free list.
  simple_remove_from_free_list(metadata, prev);
  
  if (remaining_size > sizeof(simple_metadata_t)) {
    // Create a new metadata for the remaining free slot.
    simple_metadata_t* new_metadata = (simple_metadata_t*)((char*)ptr + size);
    new_metadata->size = remaining_size - sizeof(simple_metadata_t);
    new_metadata->next = NULL;
    // Add the remaining free slot to the free list.
    simple_add_to_free_list(new_metadata);
  }
  return ptr;
}

// This is called every time an object is freed.
void simple_free(void* ptr) {
  // Look up the metadata. The metadata is placed just prior to the object.
  simple_metadata_t* metadata = (simple_metadata_t*)ptr - 1;
  // Add the free slot to the free list.
  simple_add_to_free_list(metadata);
}

////////////////////////////////////////////////////////////////////////////////

//
// [My malloc]
//
// Your job is to invent a smarter malloc algorithm here :)

// This is called only once at the beginning of each challenge.
void my_initialize() {
  simple_initialize();  // Rewrite!
}

// This is called every time an object is allocated. |size| is guaranteed
// to be a multiple of 8 bytes and smaller than 4000 bytes.
void* my_malloc(size_t size) {
  return simple_malloc(size);  // Rewrite!
}

// This is called every time an object is freed.
void my_free(void* ptr) {
  simple_free(ptr);  // Rewrite!
}

////////////////////////////////////////////////////////////////////////////////

//
// [Test]
//
// Add test cases in test(). test() is called at the beginning of the program.

void test() {
  my_initialize();
  for (int i = 0; i < 100; i++) {
    void* ptr = my_malloc(100);
    my_free(ptr);
  }
  void* ptrs[100];
  for (int i = 0; i < 100; i++) {
    ptrs[i] = my_malloc(100);
  }
  for (int i = 0; i < 100; i++) {
    my_free(ptrs[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////
//               YOU DO NOT NEED TO READ THE CODE BELOW                       //
////////////////////////////////////////////////////////////////////////////////

// This is code to run challenges. Please do NOT modify the code.

// Vector
typedef struct object_t {
  void* ptr;
  size_t size;
} object_t;

typedef struct vector_t {
  size_t size;
  size_t capacity;
  object_t* buffer;
} vector_t;

vector_t* vector_create() {
  vector_t* vector = (vector_t*)malloc(sizeof(vector_t));
  vector->size = 0;
  vector->capacity = 0;
  vector->buffer = NULL;
  return vector;  
}

void vector_push(vector_t* vector, object_t object) {
  if (vector->size >= vector->capacity) {
    vector->capacity = vector->capacity * 2 + 4096;
    vector->buffer = (object_t*)realloc(vector->buffer, vector->capacity * sizeof(object_t));
  }
  vector->buffer[vector->size] = object;
  vector->size++;
}

size_t vector_size(vector_t* vector) {
  return vector->size;
}

object_t vector_at(vector_t* vector, size_t i) {
  return vector->buffer[i];
}

void vector_clear(vector_t* vector) {
  free(vector->buffer);
  vector->capacity = 0;
  vector->size = 0;
  vector->buffer = NULL;
}

void vector_destroy(vector_t* vector) {
  free(vector->buffer);
  free(vector);
}

// Return the current time in seconds.
double get_time(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

// Return a random number in [0, 1).
double urand() {
  return rand() / ((double)RAND_MAX + 1);
}

// Return an object size. The returned size is a random number in
// [min_size, max_size) that follows an exponential distribution.
// |min_size| needs to be a multiple of 8 bytes.
size_t get_object_size(size_t min_size, size_t max_size) {
  const int alignment = 8;
  assert(min_size <= max_size);
  assert(min_size % alignment == 0);
  const double lambda = 1;
  const double threshold = 4;
  double tau = -lambda * log(urand());
  if (tau >= threshold) {
    tau = threshold;
  }
  size_t size = (size_t)((max_size - min_size) * tau / (threshold + 1e-4)) + min_size;
  return size / alignment * alignment;
}

// Return an object lifetime. The returned lifetime is a random number in
// [min_epoch, max_epoch) that follows an exponential distribution.
int get_object_lifetime(unsigned min_epoch, unsigned max_epoch) {
  const double lambda = 1;
  const double threshold = 6;
  double tau = -lambda * log(urand());
  if (tau >= threshold) {
    tau = threshold;
  }
  return (unsigned)((max_epoch - min_epoch) * tau / (threshold + 1e-4) + min_epoch);
}

typedef void (*initialize_func_t)();
typedef void* (*malloc_func_t)(size_t size);
typedef void (*free_func_t)(void* ptr);

// Record the stats of each challenge
typedef struct stats_t {
  double begin_time;
  double end_time;
  size_t mmap_size;
  size_t allocated_size;
  size_t freed_size;
} stats_t;

stats_t stats;

// Run one challenge.
// |epoch_count|: # of epochs
// |objects_per_epoch|: # objects allocated in each epoch
// |min_size|: The min size of an allocated object
// |max_size|: The max size of an allocated object
// |*_func|: Function pointers to initialize / malloc / free.
void run_challenge(int epoch_count,
                   int objects_per_epoch,
                   size_t min_size,
                   size_t max_size,
                   initialize_func_t initialize_func,
                   malloc_func_t malloc_func,
                   free_func_t free_func) {
  // Set the maximum lifetime to 100 in epochs.
  const unsigned LIFETIME_MAX = 100;
  vector_t* objects[LIFETIME_MAX];
  for (int i = 0; i < LIFETIME_MAX; i++) {
    objects[i] = vector_create();
  }
  initialize_func();
  stats.mmap_size = stats.allocated_size = stats.freed_size = 0;
  stats.begin_time = get_time();
  for (unsigned epoch = 0; epoch < epoch_count; epoch++) {
    // Allocate |objects_per_epoch| objects.
    for (int i = 0; i < objects_per_epoch; i++) {
      size_t size = get_object_size(min_size, max_size);
      int lifetime = get_object_lifetime(1, LIFETIME_MAX);
      stats.allocated_size += size;
      void* ptr = malloc_func(size);
      object_t object = {ptr, size};
      vector_push(objects[(epoch + lifetime) % LIFETIME_MAX], object);
    }
    
    // printf("%ld %ld %ld %d%%\n", stats.allocated_size, stats.freed_size, stats.mmap_size, (int)(100.0 * (stats.allocated_size - stats.freed_size) / stats.mmap_size));

    // Free objects that are expected to be freed in this epoch.
    vector_t* vector = objects[epoch % LIFETIME_MAX];
    for (size_t i = 0; i < vector_size(vector); i++) {
      object_t object = vector_at(vector, i);
      stats.freed_size += object.size;
      free_func(object.ptr);
    }
    vector_clear(vector);
  }
  stats.end_time = get_time();
  for (int i = 0; i < LIFETIME_MAX; i++) {
    vector_destroy(objects[i]);
  }
}

// Print stats
void print_stats(char* challenge, stats_t simple_stats, stats_t my_stats) {
  printf("%s: simple malloc => my malloc\n", challenge);
  printf("Time: %.2f seconds => %.2f seconds\n",
         simple_stats.end_time - simple_stats.begin_time,
         my_stats.end_time - my_stats.begin_time);
  printf("Utilization: %d%% => %d%%\n",
         (int)(100.0 * (simple_stats.allocated_size - simple_stats.freed_size) / simple_stats.mmap_size),
         (int)(100.0 * (my_stats.allocated_size - my_stats.freed_size) / my_stats.mmap_size));
}

// Run challenges
void run_challenges() {
  stats_t simple_stats, my_stats;
  
  // Challenge 1:
  run_challenge(1000, 100, 128, 128, simple_initialize, simple_malloc, simple_free);
  simple_stats = stats;
  run_challenge(1000, 100, 128, 128, my_initialize, my_malloc, my_free);
  my_stats = stats;
  print_stats("Challenge 1", simple_stats, my_stats);

  // Challenge 2:
  run_challenge(1000, 100, 16, 16, simple_initialize, simple_malloc, simple_free);
  simple_stats = stats;
  run_challenge(1000, 100, 16, 16, my_initialize, my_malloc, my_free);
  my_stats = stats;
  print_stats("Challenge 2", simple_stats, my_stats);

  // Challenge 3:
  run_challenge(1000, 100, 16, 128, simple_initialize, simple_malloc, simple_free);
  simple_stats = stats;
  run_challenge(1000, 100, 16, 128, my_initialize, my_malloc, my_free);
  my_stats = stats;
  print_stats("Challenge 3", simple_stats, my_stats);

  // Challenge 4:
  run_challenge(1000, 100, 8, 4000, simple_initialize, simple_malloc, simple_free);
  simple_stats = stats;
  run_challenge(1000, 100, 8, 4000, my_initialize, my_malloc, my_free);
  my_stats = stats;
  print_stats("Challenge 4", simple_stats, my_stats);
}

// Allocate a memory region from the OS. |size| needs to be a multiple of
// 4096 bytes.
void* _mmap(size_t size) {
  assert(size % 4096 == 0);
  stats.mmap_size += size;
  // Ideally we should call a system call here (mmap on Unix and VirtualAlloc
  // on Windows). However, we call calloc() to avoid introducing compatibility
  // problems to this challenge. Needless to say, you should not leverage the
  // fact that _mmap() is using calloc() instead of making a system call.
  return calloc(1, size);
}

// Free a memory region [ptr, ptr + size) to the OS. |ptr| and |size| needs to
// be a multiple of 4096 bytes.
void _munmap(void* ptr, size_t size) {
  stats.mmap_size -= size;
  // Ideally we should call a system call here (munmap on Unix and VirtualFree
  // on Windows). However, we call free to avoid introducing compatibility
  // problems to this challenge. Needless to say, you should not leverage the
  // fact that _munmap() is using free() instead of making a system call.
  free(ptr);
}

int main(int argc, char** argv) {
  srand(123456);  // Set the rand seed.
  test();
  run_challenges();
  return 0;
}
