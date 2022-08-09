#include "chunk.h"

void Chunk::Init(std::size_t blockSize, unsigned char blocks) {
  pData_ = new unsigned char[blockSize * blocks];
  firstAvailableBlock_ = 0;
  blockAvailable_ = blocks;
  unsigned char* p = pData_;
  unsigned char i = 0;
  for(; i < blocks; p+=blockSize) {
    *p = ++i;
  }
}

void Chunk::Release() {
  delete [] pData_;
}

void* Chunk::Allocate(std::size_t blockSize) {
  if (!blockAvailable_) return nullptr;
  unsigned char* pResult = pData_ + firstAvailableBlock_ * blockSize;
  --blockAvailable_;
  firstAvailableBlock_ = *pResult;
  return pResult;
}

void Chunk::Deallocate(void* p, std::size_t blockSize) {
  assert(p > pData_);
  unsigned char* toRelease = static_cast<unsigned char*>(p);
  assert((toRelease - pData_) % blockSize == 0);
  *toRelease = firstAvailableBlock_;
  firstAvailableBlock_ = (toRelease - pData_) / blockSize;
  ++blockAvailable_;
  return;
}

void Chunk::Reset(std::size_t blockSize, unsigned char blocks) {
  assert(blockSize > 0);
  assert(blocks > 0);
  // Overflow check
  assert((blockSize * blocks) / blockSize == blocks);

  firstAvailableBlock_ = 0;
  blockAvailable_ = blocks;
  unsigned char* p = pData_;
  unsigned char i = 0;
  for (; i < blocks; p+=blockSize) {
    *p = ++i;
  }
}
