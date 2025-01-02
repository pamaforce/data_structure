void deleteNextNode(Node* p) {
    if (p == NULL || p->next == NULL) {
        return;
    }
    Node* q = p->next;
    p->next = q->next;
    free(q);
}
