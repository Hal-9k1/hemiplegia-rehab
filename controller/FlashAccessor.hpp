#pragma once

/**
 * Reads and writes persistent data to flash.
 *
 * Uses wear leveling to increase flash lifespan. All memory access occurs relative to a hardcoded
 * region far past the binary end so data persists through firmware updates with limited size.
 */
class FlashAccessor
{
public:
  /**
   * Constructs a FlashAccessor.
   *
   * @param startOffset the offset within the managed flash data region to start this wear-leveled
   * data region.
   * @param dataSize the size in bytes of a single version of the data to be stored by this
   * FlashAccessor.
   * @param numBlocks the number of versions of the data to store for wear leveling.
   */
  FlashAccessor(uint32_t startOffset, int dataSize, int numBlocks);

  /**
   * Returns a read-only pointer to the current version of the data stored by this FlashAccessor.
   */
  const uint8_t *getReadAddress();
};
