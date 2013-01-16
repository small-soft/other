
/**
 * Copyright 2006, Micah Villmow, All Rights Reserved
 * @file Node.h
 * @Author Micah Villmow
 * @brief header file for the Node implementation
 */
#ifndef NODE_H_
#    define NODE_H_
#include "gen/gen_stdint.h"
#    include <stdlib.h>
#include "gen/data_types.h"
#include "gen/function_signatures.h"

typedef struct _Node Node;


#ifdef __cplusplus
extern "C" {
#endif
/** 
 * @fn Node* construct_Node(size_t)
 * @param nlinks the number of links the Node should have
 * @return an allocated Node or NULL on error
 */
CSTL_API Node *construct_Node(size_t nlinks);

/**
 * @fn void destruct_Node(Node*)
 * @param node the Node to deallocate
 */
CSTL_API void  destruct_Node(Node * node);
#ifdef __cplusplus
}
#endif
#endif
