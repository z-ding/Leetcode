class Twitter {
public:
    unordered_map<int, unordered_set<int>> follower;//userid: [following1 2 3...]
    unordered_map<int, vector<pair<int, int>>> tweets;//userid:[tweetsid1 id2 ...] latest tweets in the back
    int t = 0;
    Twitter() {

    }

    void postTweet(int userId, int tweetId) {
        t++;//post time
        pair<int, int> p = { tweetId,t };
        tweets[userId].push_back(p);
    }

    vector<int> getNewsFeed(int userId) {
        vector<pair<int, int>> pool;
        vector<int> res;
        pair<int, int> user = { userId,tweets[userId].size() - 1 };//userID: pointer for last tweet not incldued in feed
        pool.emplace_back(user);
        for (auto& e : follower[userId]) {
            pair<int, int> p = { e, tweets[e].size() - 1 };
            pool.emplace_back(p);
        }
        priority_queue<tuple<int, int, int, int>> pq;//post time,userid, pointer location, tweetId
        for (int i = 0; i < pool.size(); i++) {
            if (pool[i].second >= 0) {
                int ptime = tweets[pool[i].first][pool[i].second].second;
                int tid = tweets[pool[i].first][pool[i].second].first;
                tuple<int, int, int, int> t = make_tuple(ptime, pool[i].first, pool[i].second, tid);
                pq.push(t);
            }
        }
        while (!pq.empty() && res.size() < 10) {
            //top item is the latest item, push the previous tweets of this user to the pq
            int ptime = get<0>(pq.top());
            int uid = get<1>(pq.top());
            int pos = get<2>(pq.top());
            int tid = get<3>(pq.top());
            pq.pop();
            res.push_back(tid);
            if (pos > 0) {//this user has a previous tweets
                tuple<int, int, int, int> t = make_tuple(tweets[uid][pos - 1].second, uid, pos - 1, tweets[uid][pos - 1].first);
                pq.push(t);
            }
        }
        return res;

    }

    void follow(int followerId, int followeeId) {
        follower[followerId].emplace(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        follower[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */