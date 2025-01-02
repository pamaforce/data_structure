void reverseQueue(std::queue<int>& Q) {
    std::stack<int> S;

    while (!Q.empty()) {
        S.push(Q.front());
        Q.pop();
    }

    while (!S.empty()) {
        Q.push(S.top());
        S.pop();
    }
}