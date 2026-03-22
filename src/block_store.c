#include <stdio.h>
#include <stdint.h>

#include "bitmap.h"
#include "block_store.h"
// include more if you need


// You might find this handy. I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

struct block_store {
	uint8_t data[BLOCK_STORE_NUM_BLOCKS][BLOCK_SIZE_BYTES];
        uint8_t *data_blocks;
        bitmap_t *fbm;
};

block_store_t *block_store_create()
{
        block_store_t *bs = malloc(sizeof(block_store_t));
        if (!bs) {
                return NULL;
        }

        bs->data_blocks = calloc(BLOCK_STORE_NUM_BLOCKS, BLOCK_SIZE_BYTES);
        if (!bs->data_blocks) {
                free(bs);
                return NULL;
        }

        bs->fbm = bitmap_overlay(BITMAP_SIZE_BITS, bs->data_blocks + (BITMAP_START_BLOCK * BLOCK_SIZE_BYTES));
        if (!bs->fbm) {
                free(bs->data_blocks);
                free(bs);
                return NULL;
        }

        for (size_t i = 0; i < BITMAP_NUM_BLOCKS; i++) {
                bitmap_set(bs->fbm, BITMAP_START_BLOCK + i);
        }

        return bs;
}

void block_store_destroy(block_store_t *const bs)
{
        if (!bs) {
                return;
        }

        if (bs->fbm) {
                bitmap_destroy(bs->fbm);
        }

        free(bs->data_blocks);
        free(bs);
}


// Finds the first free block using the bitmap, marks it as used, and returns the block id
size_t block_store_allocate(block_store_t *const bs)
{
        if (!bs) {
                return SIZE_MAX;
        }

        size_t block_id = bitmap_ffz(bs->fbm);
        if (block_id == SIZE_MAX) {
                return SIZE_MAX;
        }

        bitmap_set(bs->fbm, block_id);
        return block_id;
}

// Attempts to allocate the requested block, returning true if successful and false otherwise. 
bool block_store_request(block_store_t *const bs, const size_t block_id)
{
	if (!bs) {
                return false;
        }

        if (block_id >= BLOCK_STORE_NUM_BLOCKS) {
                return false;
        }

        if (bitmap_test(bs->fbm, block_id)) {
                return false;
        }

        bitmap_set(bs->fbm, block_id);

        return true;
}

// Marks a given block as free in the bitmap
void block_store_release(block_store_t *const bs, const size_t block_id)
{
	if (!bs) {
		return;
	}

	if (block_id >= BLOCK_STORE_NUM_BLOCKS) {
		return;
	}

	bitmap_reset(bs->fbm, block_id);
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
	UNUSED(bs);
	return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
	UNUSED(bs);
	return 0;
}

// Returns the number of blocks in the block store
size_t block_store_get_total_blocks()
{
	return BLOCK_STORE_NUM_BLOCKS;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
	UNUSED(bs);
	UNUSED(block_id);
	UNUSED(buffer);
	return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
	UNUSED(bs);
	UNUSED(block_id);
	UNUSED(buffer);
	return 0;
}

block_store_t *block_store_deserialize(const char *const filename)
{
	UNUSED(filename);
	return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
	UNUSED(bs);
	UNUSED(filename);
	return 0;
}

