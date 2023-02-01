class Solution {
public:
    unordered_set<string> w;
    set<string> tmp;
    vector<string> res;
    bool f = false;
    void isconcat(string s, int start, int pos, int found) {
        if (pos == s.size()) {
            return;
        }
        string prefix = s.substr(start, pos - start + 1);
        //cout << start << "," << pos << ":" << prefix << endl;
        if (w.find(prefix) != w.end()) {
            if (pos + 1 == s.size()) {
                if (found > 0) {//there is already a matching prefix found
                    f = true;
                    res.push_back(s);
                }
                return;
            }
            else {
                string rest = s.substr(pos + 1);
                if (w.find(rest) != w.end()) {//rest match another word in dictionary
                    f = true;
                    res.push_back(s);
                    return;
                }
                else {//rest doesn't match, recursively check whether the rest match
                    isconcat(s, pos + 1, pos + 1, found + 1);
                }
            }
            //prefix doesn't match or we don't want to use this prefix, check next prefix           
            //check the rest of string
        }
        if (!f) {
            isconcat(s, start, pos + 1, found);
        }

        return;
    }
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            int s = words[i].size();
            w.emplace(words[i]);//all words are unique
        }
        for (int i = 0; i < words.size(); i++) {
            //cout << "checking " << words[i] << endl;
            f = false;
            isconcat(words[i], 0, 0, 0);
        }

        return res;
    }
};