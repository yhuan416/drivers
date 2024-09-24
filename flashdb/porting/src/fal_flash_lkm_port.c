#include <fal.h>

#define FLASH_ERASE_MIN_SIZE (4 * 1024)

#define LOCKER_ENABLE

#ifdef LOCKER_ENABLE
#define LOCK() \
    do         \
    {          \
               \
    } while (0)

#define UNLOCK() \
    do           \
    {            \
                 \
    } while (0)
#else

#define LOCK()
#define UNLOCK()

#endif

static int init(void)
{
    return 1;
}

static int read(long offset, uint8_t *buf, size_t size)
{
    int ret;

    LOCK();

    UNLOCK();

    return ret;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    int ret;

    LOCK();

    UNLOCK();

    return ret;
}

static int erase(long offset, size_t size)
{
    int ret;
    int32_t erase_size = ((size - 1) / FLASH_ERASE_MIN_SIZE) + 1;

    LOCK();

    UNLOCK();

    return ret;
}

const struct fal_flash_dev nor_flash0 =
    {
        .name = NOR_FLASH_DEV_NAME,
        .addr = 0x0,                      // address is relative to beginning of partition; 0x0 is start of the partition
        .len = 32 * 1024,                 // size of the partition as specified in partitions.csv
        .blk_size = FLASH_ERASE_MIN_SIZE, // must be 4096 bytes
        .ops = {init, read, write, erase},
        .write_gran = 1, // 1 byte write granularity
};
