bool isSymmetric(DNode* head) {
    if (head == NULL || head->next == head) {
        return true;
    }
    DNode* left = head->next;
    DNode* right = head->prev;
    while (left != right && left->prev != right) {
        if (left->data != right->data) {
            return false;
        }
        left = left->next;
        right = right->prev;
    }
    return true;
}
