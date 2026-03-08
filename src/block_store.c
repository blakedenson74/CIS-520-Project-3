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

size_t block_store_allocate(block_store_t *const bs)
{
	UNUSED(bs);
	return 0;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
	UNUSED(bs);
	UNUSED(block_id);
	return false;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
	UNUSED(bs);
	UNUSED(block_id);
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

size_t block_store_get_total_blocks()
{
	return 0;
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

