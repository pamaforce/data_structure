typedef struct DNode {
    int data;
    struct DNode* llink;
    struct DNode* rlink;
} DNode;

void swapNodes(DNode* p, DNode* q) {
    if (p == NULL || q == NULL || p == q) {
        return;
    }
    DNode* pPrev = p->llink;
    DNode* pNext = p->rlink;
    DNode* qPrev = q->llink;
    DNode* qNext = q->rlink;

    if (pNext == q) { // p 和 q 相邻
        p->rlink = qNext;
        p->llink = q;
        q->llink = pPrev;
        q->rlink = p;
    } else if (qNext == p) { // q 和 p 相邻
        q->rlink = pNext;
        q->llink = p;
        p->llink = qPrev;
        p->rlink = q;
    } else { // p 和 q 不相邻
        if (pPrev) pPrev->rlink = q;
        if (pNext) pNext->llink = q;
        if (qPrev) qPrev->rlink = p;
        if (qNext) qNext->llink = p;
        p->llink = qPrev;
        p->rlink = qNext;
        q->llink = pPrev;
        q->rlink = pNext;
    }
}
