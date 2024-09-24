#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/string.h>

// #define FAL_DEBUG 1
#define FAL_PART_HAS_TABLE_CFG
#define NOR_FLASH_DEV_NAME "norflash0"

// #define FAL_PART_TABLE_FLASH_DEV_NAME NOR_FLASH_DEV_NAME
// #define FAL_PART_TABLE_END_OFFSET      65536

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE \
    {                       \
        &nor_flash0,        \
    }
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                   \
    {                                                                                    \
        {FAL_PART_MAGIC_WORD, "fdb_kvdb1", NOR_FLASH_DEV_NAME, 0, 16 * 1024, 0},         \
        {FAL_PART_MAGIC_WORD, "fdb_tsdb1", NOR_FLASH_DEV_NAME, 16 * 1024, 16 * 1024, 0}, \
    }
#endif /* FAL_PART_HAS_TABLE_CFG */

#define FAL_MALLOC(s) kmalloc(s, GFP_KERNEL)
#define FAL_CALLOC(n, s) kzalloc((n * s), GFP_KERNEL)
#define FAL_REALLOC(p, s) krealloc(p, s, GFP_KERNEL)
#define FAL_FREE(ptr) kfree(ptr)

#define FAL_PRINTF(...) printk(__VA_ARGS__)

#endif /* _FAL_CFG_H_ */
