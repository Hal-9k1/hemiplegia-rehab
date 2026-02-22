#include "FlashAccessor.hpp"

#define FLASH_SECTOR_SIZE 4096 // for erasing
#define FLASH_PAGE_SIZE 256 // for writing

FlashAccessor::FlashAccessor(uint32_t startOffset, int dataSize, int numBlocks)
{

}

const uint8_t *FlashAccessor::getReadAddress(int tag)
{

}
