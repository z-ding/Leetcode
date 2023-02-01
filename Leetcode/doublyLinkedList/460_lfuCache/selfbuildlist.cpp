class LFUCache {
public:
    typedef tuple<int, int, int> tu;
    class Node { // double linked list
    public:
        tu t;//key, val, count
        Node* next;
        Node* prev;
        Node(int x, int y, int z) {
            t = make_tuple(x, y, z);
            next = nullptr;
            prev = nullptr;
        }
    };
    unordered_map<int, Node*> keymap; //store the key as the int key, the ptr of the tuple as value as a reference to find certain node in the double linked list
    unordered_map<int, pair<Node*, Node*>> freqmap; //store the count as key, corresponding Node* <head,tail> with this count number as value
    //priority_queue<int,vector<int>,greater<int> > pq; //min heap to track current LFU
    int min_freq = 0;
    int cap = 0;

    void viewlist(Node* h, Node* t) {
        cout << "from head" << endl;
        Node* cur = h;
        while (cur != nullptr) {
            int v = std::get<1>(cur->t);
            cout << v << ",";
            cur = cur->next;
        }
        cout << endl;
        cout << "from tail" << endl;
        cur = t;
        while (cur != nullptr) {
            int v = std::get<1>(cur->t);
            cout << v << ",";
            cur = cur->prev;
        }
        cout << endl;
    }

    inline void remove_node(Node* cur, int key) {
        //remove from double linekd list
        //cout << "removing " << key << endl;
        int c = std::get<2>(cur->t);
        Node* before = cur->prev;
        Node* after = cur->next;
        int v1 = std::get<1>(before->t);
        int v2 = std::get<1>(after->t);
        //delete cur;
        before->next = after;
        after->prev = before;
        //remove this node* in keymap
        keymap.erase(key);
        //if there is no node in this list, need to update lfu

        //cout << "after removing" << endl;
        //viewlist(freqmap[c].first,freqmap[c].second);
    }
    inline void add_node(int key, int val, int newcount) {
        //add in double linked list
        //cout << "adding " << key << "," << newcount << endl;
        Node* head;
        Node* tail;
        if (freqmap.find(newcount) == freqmap.end()) {
            head = new Node(newcount, -1, 0);//dummy
            tail = new Node(newcount, -2, 0);; // dummy
            head->next = tail;
            tail->prev = head;
            pair<Node*, Node*> p = { head,tail };
            freqmap.emplace(newcount, p);
        }
        else {
            head = freqmap[newcount].first;
            tail = freqmap[newcount].second;
            //cout <<"before add" << endl;
            //viewlist(headtailmap[1],headtailmap[-1]);
        }

        //if (std::get<1>(head->next->t)==-2){//head connected to tail, empty double linked list
            //min_freq = newcount;
        //}
        Node* before = tail->prev;
        Node* cur = new Node(key, val, newcount);
        before->next = cur;
        cur->prev = before;
        cur->next = tail;
        tail->prev = cur;
        //freqmap[newcount] = head;
        //add in key map
        keymap.emplace(key, cur);
        //cout << "after adding" << endl;
        //viewlist(freqmap[newcount].first,freqmap[newcount].second);
    }

    inline void updatemin(int oldmin, int newmin) {
        if (std::get<1>(freqmap[oldmin].first->next->t) == -2) {
            min_freq = newmin;
        }
    }

    LFUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        //cout << "get " << key << endl;
        if (cap == 0) {
            return -1;
        }
        if (keymap.find(key) == keymap.end()) {
            return -1;
        }
        else {
            int curcount = std::get<2>(keymap[key]->t);
            int newcount = curcount + 1;
            int val = std::get<1>(keymap[key]->t);
            //remove this node* in curcount double linked list
            remove_node(keymap[key], key);
            if (curcount == min_freq) {
                updatemin(curcount, curcount + 1);
            }
            //add this node in the back of newcount double linked list           
            add_node(key, val, newcount);
            return val;
        }
    }

    void put(int key, int value) {
        if (cap == 0) {
            return;
        }
        //cout << "put " << key << " " << value << endl;
        if (keymap.find(key) == keymap.end()) {//new key
            if (keymap.size() == cap) { //must remove LFU node before emplace new node
                //cout << min_freq << endl;
                Node* l = freqmap[min_freq].first->next;
                int k = std::get<0>(l->t);
                remove_node(l, k);
                min_freq = 1;
            }
            //add new node
            min_freq = 1;
            add_node(key, value, 1);

        }
        else { //existing key
            //remove this node* in curcount double linked list
            int curcount = std::get<2>(keymap[key]->t);
            remove_node(keymap[key], key);
            if (curcount == min_freq) {
                updatemin(curcount, curcount + 1);
            }
            //add this node in the back of newcount double linked list           
            add_node(key, value, curcount + 1);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */