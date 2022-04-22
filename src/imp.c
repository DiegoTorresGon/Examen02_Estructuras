#include <mem.h>
#include <imp.h>

/***************************/
/* EXPRESIONES ARITMÉTICAS */
/***************************/

typedef enum {
    AEXP_NUM,
    AEXP_ADD,
    AEXP_SUB,
    AEXP_MUL,
    AEXP_MEM
} AEXP_TYPE;

typedef struct aexp_t {
    AEXP_TYPE type;
    union {
        uint64_t num;
        struct {
            struct aexp_t *left;
            struct aexp_t *right;
        };
        aexp_t* index;
    };
} aexp_t;

bool aexp_is_num(aexp_t *a) {
    return a->type == AEXP_NUM;
}

bool aexp_is_add(aexp_t *a) {
    return a->type == AEXP_ADD;
}

bool aexp_is_sub(aexp_t *a) {
    return a->type == AEXP_SUB;
}

bool aexp_is_mul(aexp_t *a) {
    return a->type == AEXP_MUL;
}

bool aexp_is_mem(aexp_t *a) {
    return a->type == AEXP_MEM;
}

uint64_t aexp_num(aexp_t *a) {
    return a->num;
}

aexp_t *aexp_index(aexp_t *a) {
    return a->index;
}

aexp_t *aexp_left(aexp_t *a) {
    return a->left;
}

aexp_t *aexp_right(aexp_t *a) {
    return a->right;
}

aexp_t *aexp_make_num(uint64_t num) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_NUM;
    a->num = num;
    return a;
}

aexp_t *aexp_make_mem(aexp_t* index) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_MEM;
    a->index = index;
    return a;
}

aexp_t *aexp_make_add(aexp_t *left, aexp_t *right) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_ADD;
    a->left = left;
    a->right = right;
    return a;
}

aexp_t *aexp_make_sub(aexp_t *left, aexp_t *right) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_SUB;
    a->left = left;
    a->right = right;
    return a;
}

aexp_t *aexp_make_mul(aexp_t *left, aexp_t *right) {
    aexp_t *a = (aexp_t *)malloc(sizeof(aexp_t));
    if (a == NULL) return NULL;
    a->type = AEXP_MUL;
    a->left = left;
    a->right = right;
    return a;
}

void aexp_free(aexp_t *a) {
    if (a == NULL) return;
    
    if (aexp_is_mem(a)) {
        aexp_free(aexp_index(a));
    } else if (!aexp_is_num(a)) {
        aexp_free(aexp_left(a));
        aexp_free(aexp_right(a));
    }
    free(a);
}

uint64_t aexp_eval(aexp_t *a, mem_t* m) {
    if (aexp_is_num(a)) return aexp_num(a);
    if (aexp_is_mem(a)) return mem_eval(m, a->index);

    uint64_t nleft = aexp_eval(aexp_left(a), m);
    uint64_t nright = aexp_eval(aexp_right(a), m);

    if (aexp_is_add(a)) return nleft + nright;
    if (aexp_is_mul(a)) return nleft * nright;

    if (nright > nleft) return 0;
        return nleft - nright;
}

/*************************/
/* EXPRESIONES BOOLEANAS */
/*************************/

typedef enum {
    BEXP_BASURA,
    BEXP_EQUAL,
    BEXP_LESS,
    BEXP_AND,
    BEXP_OR,
    BEXP_NEG
} BEXP_TYPE;

typedef struct bexp_t {
    BEXP_TYPE type;
    union {
        struct {
            struct aexp_t *aleft;
            struct aexp_t *aright;
        };
        struct {
            struct bexp_t *bleft;
            struct bexp_t *bright;
        };
        struct bexp_t *child;
    };
} bexp_t;

bexp_t bexp_true;
bexp_t bexp_false;

bool bexp_is_true(bexp_t *b) {
    return b == &bexp_true;
}

bool bexp_is_false(bexp_t *b) {
    return b == &bexp_false;
}

bool bexp_is_equal(bexp_t *b) {
    return b->type == BEXP_EQUAL;
}

bool bexp_is_less(bexp_t *b) {
    return b->type == BEXP_LESS;
}

bool bexp_is_and(bexp_t *b) {
    return b->type == BEXP_AND;
}

bool bexp_is_or(bexp_t *b) {
    return b->type == BEXP_OR;
}

bool bexp_is_neg(bexp_t *b) {
    return b->type == BEXP_NEG;
}

aexp_t *bexp_aleft(bexp_t *b) {
    return b->aleft;
}

aexp_t *bexp_aright(bexp_t *b) {
    return b->aright;
}

bexp_t *bexp_bleft(bexp_t *b) {
    return b->bleft;
}

bexp_t *bexp_bright(bexp_t *b) {
    return b->bright;
}

bexp_t *bexp_nchild(bexp_t *b) {
    return b->child;
}

bexp_t *bexp_make_true() {
    return &bexp_true;
}

bexp_t *bexp_make_false() {
    return &bexp_false;
}

bexp_t *bexp_make_equal(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_EQUAL;
    root->aleft = left;
    root->aright = right;
    return root;
}
bexp_t *bexp_make_less(aexp_t *left, aexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_LESS;
    root->aleft = left;
    root->aright = right;
    return root;
}
bexp_t *bexp_make_and(bexp_t *left, bexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_AND;
    root->bleft = left;
    root->bright = right;
    return root;
}
bexp_t *bexp_make_or(bexp_t *left, bexp_t *right) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_OR;
    root->bleft = left;
    root->bright = right;
    return root;
}
bexp_t *bexp_make_neg(bexp_t *child) {
    bexp_t *root = (bexp_t *)malloc(sizeof(bexp_t));
    if (root == NULL) return NULL;
    root->type = BEXP_NEG;
    root->child = child;
    return root;
}

void bexp_free(bexp_t *b) {
    if (b == NULL) return;

    if (bexp_is_true(b) || bexp_is_false(b))
        return;

    if (bexp_is_equal(b) || bexp_is_less(b)) {
        aexp_free(bexp_aleft(b));
        aexp_free(bexp_aright(b));
        free(b);
        return;
    }

    if (bexp_is_and(b) || bexp_is_or(b)) {
        bexp_free(bexp_bleft(b));
        bexp_free(bexp_bright(b));
        free(b);
        return;
    }

    bexp_free(bexp_nchild(b));
    free(b);
}

bool bexp_eval(bexp_t *b, mem_t* m) {
    if (bexp_is_true(b)) return true;
    if (bexp_is_false(b)) return false;

    if (bexp_is_neg(b)) return !bexp_eval(bexp_nchild(b), m);

    if (bexp_is_equal(b))
        return aexp_eval(bexp_aleft(b), m) == aexp_eval(bexp_aright(b), m);

    if (bexp_is_less(b))
        return aexp_eval(bexp_aleft(b), m) < aexp_eval(bexp_aright(b), m);

    if (bexp_is_and(b))
        return bexp_eval(bexp_bleft(b), m) && bexp_eval(bexp_bright(b), m);

    return bexp_eval(bexp_bleft(b), m) || bexp_eval(bexp_bright(b), m);
}

/***************************/
/* EXPRESIONES DE PROGRAMA */
/***************************/
typedef enum {
    PEXP_SKP,
    PEXP_ASS,
    PEXP_SQN,
    PEXP_WHL,
    PEXP_CON,
} PEXP_TYPE;

typedef struct pexp_t {
    PEXP_TYPE type;
    union {
        struct {
            struct aexp_t *index;
            struct aexp_t *rvalue;
        };
        struct{
            struct pexp_t *pfirst;
            struct pexp_t *psecond;
        };
        struct{
            struct bexp_t *condition;
            struct pexp_t *ptrue;
            struct pexp_t *pfalse;
        };
    };
} pexp_t;

//Predicados
bool pexp_is_skip(pexp_t *p) {
    return p->type == PEXP_SKP;
}

bool pexp_is_assign(pexp_t *p) {
    return p->type == PEXP_ASS;
}

bool pexp_is_sequence(pexp_t *p) {
    return p->type == PEXP_SQN;
}

bool pexp_is_while(pexp_t *p) {
    return p->type == PEXP_WHL;
}

bool pexp_is_conditional(pexp_t *p) {
    return p->type == PEXP_CON;
}

//Selectores
pexp_t* pexp_pfirst(pexp_t *p){
    return p->pfirst;
}

pexp_t* pexp_psecond(pexp_t *p){
    return p->psecond;
}

pexp_t* pexp_pfalse(pexp_t *p){
    return p->pfalse;
}

pexp_t* pexp_ptrue(pexp_t *p){
    return p->ptrue;
}

aexp_t* pexp_index(pexp_t* p){
    return p->index;
}

aexp_t* pexp_rvalue(pexp_t* p){
    return p->rvalue;
}

bexp_t* bexp_rvalue(pexp_t* p){
    return p->condition;
}

//Constructores

pexp_t *pexp_make_skip() {
    pexp_t *p = (pexp_t *)malloc(sizeof(pexp_t));
    if (p == NULL) return NULL;
    p->type = PEXP_SKP;
    return p;
}

pexp_t *pexp_make_assign(aexp_t *index, aexp_t *rvalue) {
    pexp_t *p = (pexp_t *)malloc(sizeof(pexp_t));
    if (p == NULL) return NULL;
    p->type = PEXP_ASS;
    p->index = index;
    p->rvalue = rvalue;
    return p;
}

pexp_t *pexp_make_sequence(pexp_t *pfirst, pexp_t *psecond) {
    pexp_t *p = (pexp_t *)malloc(sizeof(pexp_t));
    if (p == NULL) return NULL;
    p->type = PEXP_SQN;
    p->pfirst = pfirst;
    p->psecond = psecond;
    return p;
}

pexp_t *pexp_make_cicle(bexp_t *condition, pexp_t *ptrue) {
    pexp_t *p = (pexp_t *)malloc(sizeof(pexp_t));
    if (p == NULL) return NULL;
    p->type = PEXP_WHL;
    p->condition = condition;
    p->ptrue= ptrue;
    return p;
}

pexp_t *pexp_make_conditional(bexp_t *condition, pexp_t *ptrue, pexp_t *pfalse) {
    pexp_t *p = (pexp_t *)malloc(sizeof(pexp_t));
    if (p == NULL) return NULL;
    p->type = PEXP_CON;
    p->condition = condition;
    p->ptrue = ptrue;
    p->pfalse = pfalse;
    return p;
}

void pexp_free(pexp_t *p) {
    if (p == NULL) return;

}

//Evaluador pexp_t
pexp_t *pexp_t_eval(pexp_t *p, mem_t* m)
{
    if(pexp_is_skip(p)) return pexp_t_eval(pexp_make_skip() ,m);
    if(pexp_is_ass(p)) return pexp_t_eval(pexp_make_assign(p->index, p->rvalue), m);
    if(pexp_is_sequence(p)) return pexp_t_eval(pexp_make_sequence(p->pfirst, p->psecond), m);
    if(pexp_is_while(p)) return pexp_t_eval(pexp_make_cicle(p->condition, p->ptrue), m);
    if(pexp_is_conditional(p)) return pexp_t_eval(pexp_make_conditional(p->condition, p->ptrue, p->pfalse), m);
}
