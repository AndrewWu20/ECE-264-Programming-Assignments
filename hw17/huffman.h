#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <stdlib.h>

#include "frequencies.h"
#include "priority_queue.h"

typedef struct _TreeNode {
	uchar character;
	size_t frequency;
	struct _TreeNode* left;
	struct _TreeNode* right;
} TreeNode;

Node* make_huffman_pq(Frequencies freqs);

#endif
