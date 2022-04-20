#include <mem.h>

//The memory of a program will be represented with a linked list with sentinel.
struct mem_t {
    mem_t* next;
    uint64_t value;
    uint64_t pos; 
};

mem_t* mem_make() {
    mem_t* sent = (mem_t*)malloc(sizeof(mem_t));

    if (sent == NULL) return NULL;
   
    sent->next = NULL;
    sent->value = sent->pos = 0;
    
    return sent;
} 

mem_t* mem_assign(mem_t* m, aexp_t* index_exp, aexp_t* value_exp) {
    uint64_t index = aexp_eval(index_exp, m);
    uint64_t value = aexp_eval(value_exp, m); 
    
    mem_t* iter = m;

    while(iter->next != NULL && iter->next->pos <= index) 
        iter = iter->next;

    if (iter != m && iter->pos == index) {
        iter->value = value;
        return m;
    } 

    mem_t* new_pos = mem_make();
    if (new_pos == NULL) return NULL;

    new_pos->next = iter->next;
    iter->next = new_pos;
    new_pos->pos = index;
    new_pos->value = value;

    return m; 
}

uint64_t mem_eval(mem_t* m, aexp_t* index_exp) {
    uint64_t index = aexp_eval(index_exp, m);

    while(m->next != NULL && m->next->pos <= index) {
        m = m->next;
        if (m->pos == index) return m->value; 
    } 

    return 0;
}

uint64_t mem_eval_num(mem_t* m, uint64_t index) {
    while(m->next != NULL && m->next->pos <= index) {
        m = m->next;
        if (m->pos == index) return m->value; 
    } 

    return 0;
}

void mem_free(mem_t* m) {
    if (m == NULL) return;

    mem_t* next = m->next;
    free(m);

    while(next != NULL) {
        m = next;
        next = next->next;

        free(m);
    }
}
