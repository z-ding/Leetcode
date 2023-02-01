class LFUCache {
public:
    typedef tuple<int, int, int> tu;
    typedef list<tu>::iterator idll; //iterator od double linked list
    unordered_map<int, idll> keymap; //store the key as the int key, the ptr of the tuple as value as a reference to find certain node in the double linked list
    unordered_map<int, list<tu>> freqmap; //store the count as key, corresponding Node* <head,tail> with this count number as value
    int min_freq = 0;
    int cap = 0;
    void remove(idll l, int key, int curcount) {
        freqmap[curcount].erase(l);
        keymap.erase(key);
        if (curcount == min_freq && freqmap[min_freq].size() == 0) {
            min_freq = curcount + 1;
        }
    }
    void add(int key, int val, int newcount) {
        tu t = make_tuple(key, val, newcount);
        freqmap[newcount].emplace_back(t);
        keymap.emplace(key, --freqmap[newcount].end());
        if (newcount == 1) {
            min_freq = 1;
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
            int curcount = std::get<2>(*keymap[key]);
            int newcount = curcount + 1;
            int val = std::get<1>(*keymap[key]);
            //remove this node* in curcount double linked list
            remove(keymap[key], key, curcount);
            //add this node in the back of newcount double linked list           
            //add_node(key,val,newcount );
            add(key, val, newcount);
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
                //cout << min_freq << ","<< freqmap[min_freq].size()<< endl;
                int k = std::get<0>(freqmap[min_freq].front());
                freqmap[min_freq].pop_front();
                keymap.erase(k);
            }
            add(key, value, 1);

        }
        else { //existing key
            //remove this node* in curcount double linked list
            int curcount = std::get<2>(*keymap[key]);
            remove(keymap[key], key, curcount);
            //add this node in the back of newcount double linked list           
            add(key, value, curcount + 1);
        }
    }
};