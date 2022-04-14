#include "mem.h"

//The memory of a program will be represented with a linked list with sentinel.
struct Memory {
    Memory* next;
    uint64_t value;
    uint64_t pos; 
};

Memory* mem_make() {
    Memory* sent = (Memory*)malloc(sizeof(Memory));

    if (sent == NULL) return NULL;
   
    sent->next = NULL;
    sent->value = sent->pos = 0;
    
    return sent;
} 

Memory* mem_assign(Memory* m, aexp_t* index_exp, aexp_t* value_exp) {
    uint64_t index = aexp_eval(index_exp);
    uint64_t value = aexp_eval(value_exp); 
    
    Memory* iter = m;

    while(iter->next != NULL && iter->next->pos <= index) iter = iter->next;

    if (iter->pos == index) {
        iter->value = value;
        return m;
    } 

    Memory* new_pos = mem_make();
    if (new_pos == NULL) return NULL;

    new_pos->next = m->next;
    m->next = new_pos;
    new_pos->pos = index;
    new_pos->value = value;

    return m; 
}

uint64_t mem_eval(Memory* m, aexp_t* index_exp) {
    uint64_t index = aexp_eval(index_exp);

    while(m->next != NULL) {
        m = m->next;
        if (m->pos == index) return m->value; 
    } 

    return 0;
}

void mem_free(Memory* m) {
    if (m == NULL) return;

    Memory* next = m->next;
    free(m);

    while(next != NULL) {
        m = next;
        next = next->next;

        free(m);
    }
}
