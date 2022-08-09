#include <cstddef>
#include <assert.h>
class Chunk {
  void Init(std::size_t blockSize, unsigned char blocks);
  void Release();

  void* Allocate(std::size_t blockSize);
  void Deallocate(void* p, std::size_t blockSize);

  void Reset(std::size_t blockSize, unsigned char blocks);

  unsigned char* pData_;
  unsigned char firstAvailableBlock_,
                blockAvailable_;
};
