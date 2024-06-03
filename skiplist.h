//
#include <stdlib.h>

#define SKIPLIST_MAXLEVEL 32
#define SKIPLIST_P 0.25

typedef struct slobj {
    char *ptr;
    size_t length;
} slobj;

typedef struct skiplistNode {
    slobj* obj;
    int64_t score;
    struct skiplistNode *backward;
    struct skiplistLevel {
        struct skiplistNode *forward;
        unsigned int span;
    }level[];
} skiplistNode;

typedef struct skiplist {
    struct skiplistNode *header, *tail;
    unsigned long length;
    int level;
} skiplist;

typedef void (*slDeleteCb) (void *ud, slobj *obj);
slobj* slCreateObj(const char* ptr, size_t length);
void slFreeObj(slobj *obj);

skiplist *slCreate(void);
void slFree(skiplist *sl);
void slDump(skiplist *sl);

void slInsert(skiplist *sl, int64_t score, slobj *obj);
int slDelete(skiplist *sl, int64_t score, slobj *obj);
unsigned long slDeleteByScore(skiplist *sl, int64_t min, int64_t max, slDeleteCb cb, void* ud);
unsigned long slDeleteByRank(skiplist *sl, unsigned int start, unsigned int end, slDeleteCb cb, void* ud);

unsigned long slGetRank(skiplist *sl, int64_t score, slobj *o);
skiplistNode* slGetNodeByRank(skiplist *sl, unsigned long rank);

skiplistNode *slFirstInRange(skiplist *sl, int64_t min, int64_t max);
skiplistNode *slLastInRange(skiplist *sl, int64_t min, int64_t max);

