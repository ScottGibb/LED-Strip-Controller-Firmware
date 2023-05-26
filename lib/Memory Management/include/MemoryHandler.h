#ifndef MEMORYHANDLER_H
#define MEMORYHANDLER_H

#include <map>
#include <stdint.h>

/**
 * @brief SEGMENT enum, outlining the different memory segments
 *
 */
enum class SEGMENT
{
  SYSTEM_INFO = 0,
  CHANNEL_CMDS = 1,
  USER_MODES = 2,
  NUM_MEMORY_SEGMENTS = 3
};

/**
 * @brief MEMORY_ERR enum representing the different errors the Memory Handler can return
 *
 */
enum class MEMORY_ERR
{
  OK = 0,
  SEGMENT_OUT_OF_BOUNDS = 1,
  OUT_OF_SLOTS = 2,
  SLOT_OUT_OF_BOUNDS = 3
};

/**
 * @brief MemoryMap_t outlining the start, end and size of the different segments.
 *
 */
typedef struct
{
  uint16_t MEMORY_START;
  uint16_t MEMORY_END;
  uint16_t MEMORY_SIZE;
  uint16_t SLOT_SIZE; // The memory segment is divided into slots of SLOT_SIZE
  uint16_t NUM_SLOTS;
} MemoryMap_t;

/**
 * @brief A low level class used to abstract the EEPROM/Flash storage from the rest of the system and maintain the memory management and ensure safe saving and loading
 *
 */
class MemoryHandler
{
public:
  static MemoryHandler *instance;
  /**
   * @brief Gets the singleton object of MemoryHandler
   *
   * @param memory
   * @return MemoryHandler*
   */
  static MemoryHandler *getInstance(std::map<SEGMENT, MemoryMap_t> memory);
  /**
   * @brief Get the singleton Object of MemoryHandler, if called first, will return a NULLPTR
   *
   * @return MemoryHandler*
   */
  static MemoryHandler *getInstance();
  /**
   * @brief Saves the bytes in data to the Segment in slot position pos
   *
   * @param seg the segment of memory to be saved in
   * @param pos the slot in that segment
   * @param data the data to be saved
   * @param dataLen the length of data to be saved (Must be <= slotSize)
   * @return MEMORY_ERR
   */
  MEMORY_ERR saveData(SEGMENT seg, uint16_t pos, uint8_t *data, uint16_t dataLen);
  /**
   * @brief Loads the bytes in the segment slot into a buffer provided
   *
   * @param seg the segment of memory to be loaded in
   * @param pos the slot in that segment
   * @param data the buffer that the data will be loaded in to
   * @param dataLen the length of data to be loaded (Must be <= slotSize)
   * @return MEMORY_ERR
   */
  MEMORY_ERR loadData(SEGMENT seg, uint16_t pos, uint8_t *data, uint16_t dataLen);

private:
  std::map<SEGMENT, MemoryMap_t> MEMORY_MAP;
  /**
   * @brief Construct a new Memory Handler object, Private Constructor, so object can only be instantiated through the getInstance methods
   *
   * @param MemoryMap
   */
  MemoryHandler(std::map<SEGMENT, MemoryMap_t> MemoryMap);
  /**
   * @brief Construct a new Memory Handler object
   *
   */
  MemoryHandler(const MemoryHandler &) = delete;
  /**
   * @brief
   *
   * @return MemoryHandler&
   */
  MemoryHandler &operator=(const MemoryHandler &) = delete;
  /**
   * @brief Destroy the Memory Handler object
   *
   */
  ~MemoryHandler();
  /**
   * @brief Checks the Memory position to see if the operation is valid
   *
   * @param seg the chosen segment
   * @param pos the chosen slot
   * @param dataLen the length of the data
   * @return MEMORY_ERR
   */
  MEMORY_ERR checkValidity(SEGMENT seg, uint16_t pos, uint16_t dataLen);
};

#endif // MEMORYHANDLER_H