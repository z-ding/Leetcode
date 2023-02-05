class Solution {
public:
    unordered_map<string, bool> canmake;
    vector<string> res;
    bool make(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies, string cur) {
        cout << cur << endl;
        if (canmake.find(cur) != canmake.end()) {
            return canmake[cur];
        }
        canmake.emplace(cur, false);

        auto it_cur = find(recipes.begin(), recipes.end(), cur);
        if (it_cur != recipes.end()) {
            int index = it_cur - recipes.begin();
            for (int i = 0; i < ingredients[index].size(); i++) {
                auto it1 = find(recipes.begin(), recipes.end(), ingredients[index][i]);
                if (it1 != recipes.end()) {// check other recipes
                    if (!make(recipes, ingredients, supplies, (*it1))) {
                        return false;
                    }
                }
                else {//this ingredient is not a recipe, check supplies
                    if (!make(recipes, ingredients, supplies, ingredients[index][i])) {
                        return false;
                    }
                }


            }
        }
        else {
            auto it = find(supplies.begin(), supplies.end(), cur);
            if (it != supplies.end()) {//we are given the required ingredients
                canmake[cur] = true;
                return true;
            }
            else {
                return false;
            }
        }

        canmake[cur] = true;
        cout << cur << " res " << canmake[cur] << endl;
        return true;
    }
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        for (int i = 0; i < recipes.size(); i++) {
            make(recipes, ingredients, supplies, recipes[i]);
        }
        for (int i = 0; i < recipes.size(); i++) {
            if (canmake[recipes[i]]) {
                res.push_back(recipes[i]);
            }
        }
        for (auto& e : canmake) {
            cout << e.first << "," << e.second << endl;
        }
        return res;
    }
};