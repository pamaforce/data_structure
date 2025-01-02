void insertAtBottom(std::stack<int>& stack, int item) {
    if (stack.empty()) {
        stack.push(item);
        return;
    }

    int top = stack.top();
    stack.pop();
    insertAtBottom(stack, item);

    stack.push(top);
}

void reverseStack(std::stack<int>& stack) {
    if (stack.empty()) {
        return;
    }

    int top = stack.top();
    stack.pop();

    reverseStack(stack);

    insertAtBottom(stack, top);
}