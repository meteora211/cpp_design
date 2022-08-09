#include <vector>
#include "chunk.h"
class FixedAllocator {

private:
  std::size_t blockSize_;
  unsigned char numBlocks_;
  typedef std::vector<Chunk> Chunks;
  Chunks chunks_;
};
