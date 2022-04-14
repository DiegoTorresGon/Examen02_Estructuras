#ifndef ED_MEM_H
#define ED_MEM_H

#include <inttypes.h>
#include <stdlib.h>
#include <imp.h>

typedef struct Memory Memory;

/**
 * @brief Creates a new heap allocated memory list. 
 * 
 * @return Memory* Valid memory location or NULL is allocation was unsuccesful. 
 */
Memory* mem_make();

/**
 * @brief Assigns the evaluation of value_exp to the position
 *  that is evaluated from index_exp. 
 * 
 * @param m Memory* to be modified with new assignment. 
 * @param index_exp Arithmethic expression with index value. 
 * @param value_exp Arithmethic expression with assignment value. 
 * @return Memory* Pointer to m. NULL if operation was unsuccesful. 
 */
Memory* mem_assign(Memory* m, aexp_t* index_exp, aexp_t* value_exp); 

/**
 * @brief Returns the value stored at that index.
 *
 * By default, uninitialized memory locations store the value 0. 
 * @param m Memory list. 
 * @param index_exp Arithmethic expression with index. 
 * @return uint64_t Value stores at that index. 
 */
uint64_t mem_eval(Memory* m, aexp_t* index_exp);

/**
 * @brief Deletes all data inside the memory list.
 * 
 * @param m Memory list to be freed. 
 */
void mem_free(Memory* m);

#endif