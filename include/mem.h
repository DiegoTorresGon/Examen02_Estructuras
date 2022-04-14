#ifndef ED_MEM_H
#define ED_MEM_H

#include <inttypes.h>
#include <stdlib.h>
#include <imp.h>

typedef struct mem_t mem_t;

/**
 * @brief Creates a new heap allocated memory list. 
 * 
 * @return mem_t* Valid memory location or NULL is allocation was unsuccesful. 
 */
mem_t* mem_make();

/**
 * @brief Assigns the evaluation of value_exp to the position
 *  that is evaluated from index_exp. 
 * 
 * @param m mem_t* to be modified with new assignment. 
 * @param index_exp Arithmethic expression with index value. 
 * @param value_exp Arithmethic expression with assignment value. 
 * @return mem_t* Pointer to m. NULL if operation was unsuccesful. 
 */
mem_t* mem_assign(mem_t* m, aexp_t* index_exp, aexp_t* value_exp); 

/**
 * @brief Returns the value stored at that index.
 *
 * By default, uninitialized memory locations store the value 0. 
 * @param m Memory list. 
 * @param index_exp Arithmethic expression with index. 
 * @return uint64_t Value stores at that index. 
 */
uint64_t mem_eval(mem_t* m, aexp_t* index_exp);

/**
 * @brief Deletes all data inside the memory list.
 * 
 * @param m Memory list to be freed. 
 */
void mem_free(mem_t* m);

#endif