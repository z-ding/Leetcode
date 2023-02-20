class MyCircularQueue {
public:
    /*
    we will have a fixed size vector
    _ _ _ _
    0 1 2 3
    push: if (full) return -1; else place the value in the next empty place after current rear and this number becomes new rear
    pop: if (empty) return -1; else pop the value on current front, mark the next number as new front
    */
    vector<int> q;
    int numberInQ;
    int front = -1;
    int rear = -1;
    MyCircularQueue(int k) {
        for (int i = 0; i < k; i++) {
            q.push_back(-1);
        }
        numberInQ = 0;
    }

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        numberInQ++;
        if (front == -1) {
            front = 0;
        }
        q[(rear + 1) % q.size()] = value;
        rear = (rear + 1) % q.size();
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        numberInQ--;
        if (!numberInQ) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % q.size();
        }

        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return q[front];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return q[rear];
    }

    bool isEmpty() {
        if (!numberInQ) {
            return true;
        }
        return false;
    }

    bool isFull() {
        if (numberInQ == q.size()) {
            return true;
        }
        return false;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */