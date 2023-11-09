class Solution {
public:
    /*
    e.g. 1 2 3 1 2
    num #distinct
    1   3
    2   2
    3   1
    when the second one comes in, increment the distinct count for 3 & 2 by 1
    1   3
    2   2+1 = 3
    3   1+1 =2
    1   1
    when the second two comes in, increment the distinct count for 1 & 3 by 1
    1   3
    2   3
    3   2+1 = 3
    1   1+1 = 2
    2   1
    so when i th number comes in, we increment the distinct count for i-1 --- the number before its last appearance by 1
    for the squares we are asking in the question
    1   3^2 + 3^2 +3^2+ 2^2 + 1^2 = 32
    2   3^2 +3^2+ 2^2 + 1^2 = 23
    3   3^2 + 2^2 + 1^2 = 14
    1   2^2 + 1^2 = 5
    2   1^2 = 1
    for each number, we are summing up the square of range [i,n-1]
    so if we increment x numbers by 1, say a, b, c..
    a^2 + b^2 + c^2 becomes
    (a+1) ^2 + (b+1) ^2 + (c+1) ^2
    the difference is 2* (a+b+c)+x
    so we can use range based query to get our sum
    */
    int mod = 1000000007;
    vector<pair<int, int>> tree; //1 indexed 
    vector<int> lazy;
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            // Leaf node will have a single element
            tree[node] = { 0,0 };
        }
        else
        {
            int mid = (start + end) / 2;
            // Recurse on the left child
            build(2 * node, start, mid);
            // Recurse on the right child
            build(2 * node + 1, mid + 1, end);
            // Internal node will have the sum of both of its children
            tree[node].first = tree[2 * node].first + tree[2 * node + 1].first;
            tree[node].second = tree[2 * node].second + tree[2 * node + 1].second;
        }
    }
    void update(int node, int start, int end, int idx, int val)
    {
        if (start == end)
        {
            // Leaf node
            tree[node].first += val;
            tree[node].second = tree[node].first * tree[node].first;
        }
        else
        {
            int mid = (start + end) / 2;
            if (start <= idx and idx <= mid)
            {
                // If idx is in the left child, recurse on the left child
                update(2 * node, start, mid, idx, val);
            }
            else
            {
                // if idx is in the right child, recurse on the right child
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            // Internal node will have the sum of both of its children
            tree[node].first = tree[2 * node].first + tree[2 * node + 1].first;
            tree[node].second = tree[2 * node].second + tree[2 * node + 1].second;
        }
    }
    int query(int node, int start, int end, int l, int r)
    {
        if (r < start or end < l)
        {
            // range represented by a node is completely outside the given range
            return 0;
        }
        if (l <= start and end <= r)
        {
            // range represented by a node is completely inside the given range
            return tree[node].second;
        }
        // range represented by a node is partially inside and partially outside the given range
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return (p1 + p2);
    }
    void view() {
        for (int i = 0; i < tree.size(); i++) {
            cout << i << ":" << tree[i].first << "," << tree[i].second << endl;
        }
    }
    //lazy propagation
    void updateRange(int node, int start, int end, int l, int r, int val)
    {
        if (lazy[node] != 0)
        {
            // This node needs to be updated
            //a*a+b*b+c*c bs (a+x)*(a+x) + (b+x)*(b+x) + (c+x)*(c+x)
            // = 2ax+ 2bx + 2cx + n*x*x
            tree[node].second += 2 * tree[node].first * lazy[node] + (end - start + 1) * lazy[node] * lazy[node];
            tree[node].first += (end - start + 1) * lazy[node];    // Update it
            //tree[node].second = tree[node].first * tree[node].first;
            if (start != end)
            {
                lazy[node * 2] += lazy[node];                  // Mark child as lazy
                lazy[node * 2 + 1] += lazy[node];                // Mark child as lazy
            }
            lazy[node] = 0;                                  // Reset it
        }
        if (start > end or start > r or end < l)              // Current segment is not within range [l, r]
            return;
        if (start >= l and end <= r)
        {
            // Segment is fully within range
            long long cur = ((long long)tree[node].second % mod + (long long)2 * (long long)tree[node].first % mod + (long long)end - (long long)start + 1ll) % mod;
            tree[node].second = (int)cur;
            tree[node].first = (tree[node].first % mod + (end - start + 1) * val % mod) % mod;
            if (start != end)
            {
                // Not leaf node
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        updateRange(node * 2, start, mid, l, r, val);        // Updating left child
        updateRange(node * 2 + 1, mid + 1, end, l, r, val);   // Updating right child
        tree[node].first = (tree[2 * node].first % mod + tree[2 * node + 1].first % mod) % mod;
        tree[node].second = (tree[2 * node].second % mod + tree[2 * node + 1].second % mod) % mod;
    }

    int queryRange(int node, int start, int end, int l, int r)
    {
        if (start > end or start > r or end < l)
            return 0;         // Out of range
        if (lazy[node] != 0)
        {
            // This node needs to be updated
            tree[node].second += 2 * tree[node].first * lazy[node] + (end - start + 1) * lazy[node] * lazy[node];
            tree[node].first += (end - start + 1) * lazy[node];            // Update it
            if (start != end)
            {
                lazy[node * 2] += lazy[node];         // Mark child as lazy
                lazy[node * 2 + 1] += lazy[node];    // Mark child as lazy
            }
            lazy[node] = 0;                 // Reset it
        }
        if (start >= l and end <= r)             // Current segment is totally within range [l, r]
            return tree[node].second;
        int mid = (start + end) / 2;
        int p1 = queryRange(node * 2, start, mid, l, r);         // Query left child
        int p2 = queryRange(node * 2 + 1, mid + 1, end, l, r); // Query right child
        long long p = ((long long)p1 + (long long)p2) % mod;
        return (int)p;
    }
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i <= 4 * n; i++) {
            tree.push_back({ 0,0 });
            lazy.push_back(0);
        }
        //build(0,0,n-1);
        unordered_map<int, int> lastappear;
        int res = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int updatestart = 0;
            int updateend = i;
            if (lastappear.find(x) != lastappear.end()) {
                updatestart = lastappear[x] + 1;
            }
            lastappear[x] = i;
            //for (int j=updatestart; j<=updateend;j++){                
                //update(1,0,n-1,j,1);;
           //}
            updateRange(1, 0, n - 1, updatestart, updateend, 1);
            //view();
            res = (res % mod + queryRange(1, 0, n - 1, 0, i) % mod) % mod;
            //cout << i << "," << res << endl;
        }
        return res;
    }
};