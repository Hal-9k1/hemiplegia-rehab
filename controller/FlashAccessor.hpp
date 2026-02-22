#pragma once

class FlashAccessor
{
public:
  FlashAccessor(uint32_t startOffset, int dataSize, int numBlocks);
  const uint8_t *getReadAddress(int tag);
  void write(int tag, const uint8_t *pData);
};
