class RangeFreqQuery {
public:
    /*
    We just need to maintain a vector of indices for each element in the order they occur.
    Then querying for frequency between a range [L, R] is simply finding highest index and lowest index of that element within the given range and returning number of elements between them in the vector of indices.
    The highest and lowest index can be found using binary search (upper_bound and lower_bound) in O(logN) time.
    */
    unordered_map<int, vector<int>> mp;
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < size(arr); i++) {
            if (mp.find(arr[i]) == mp.end()) {
                vector<int> v = { i };
                mp.emplace(arr[i], v);
            }
            else {
                mp[arr[i]].push_back(i);
            }
        }
    }

    int query(int L, int R, int V) {
        /* e.g. vector<int> :[2,3,9]
        //int a =*(upper_bound(begin(mp[V]), end(mp[V]), R));//Returns an iterator pointing to the first element in the range [first,last) which compares stirctly greater than val
            1upper 2           -- begin()+1
            2upper 3           -- begin()+2
            3upper 9           -- begin()+3
            4upper 9           -- begin()+3
            5upper 9           -- begin()+3
            6upper 9           -- begin()+3
            7upper 9           -- begin()+3
            8upper 9           -- begin()+3
            9upper -1094795586 --end()
        //int b = *(lower_bound(begin(mp[V]), end(mp[V]), L));//Returns an iterator pointing to the first element in the range [first, last) that element >= value
            1lower 2           -- begin()+1
            2lower 2           -- begin()+1
            3lower 3           -- begin()+2
            4lower 9           -- begin()+3
            5lower 9           -- begin()+3
            6lower 9           -- begin()+3
            7lower 9           -- begin()+3
            8lower 9           -- begin()+3
            9lower 9           -- begin()+3
            10lower -1094795586-- end()
            upper - lower is the number of element that's in this range (inclusive)
        */
        return upper_bound(begin(mp[V]), end(mp[V]), R) - lower_bound(begin(mp[V]), end(mp[V]), L);
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */