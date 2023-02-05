class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        //for each ingredient, build a hashmap based on which recipe needs this ingreient
        //meanwhile, build a hashmap recording each recipe requires how many ingredient
        unordered_map<string, vector<int>> mustHaveIng;
        unordered_map<int, int> numOfIng;
        queue<string> q;
        for (int i = 0; i < ingredients.size(); i++) {
            numOfIng.emplace(i, ingredients[i].size());//recipe index as key
            for (int j = 0; j < ingredients[i].size(); j++) {
                if (mustHaveIng.find(ingredients[i][j]) == mustHaveIng.end()) {
                    vector<int> v;
                    v.push_back(i);
                    mustHaveIng.emplace(ingredients[i][j], v);
                    if (find(supplies.begin(), supplies.end(), ingredients[i][j]) != supplies.end()) {
                        q.push(ingredients[i][j]);
                    }
                }
                else {
                    mustHaveIng[ingredients[i][j]].push_back(i);
                }

            }
            //push this ingredient to the queue if we have this ingredient

        }
        //loop through mustHaveIng hash map, if an ingredient isn't a recipe, check whether it is available in supplies
        vector<string> res;
        unordered_set<string> checked;
        while (!q.empty()) {
            //cout << q.front() << endl;
            checked.emplace(q.front());
            for (int i = 0; i < mustHaveIng[q.front()].size(); i++) {
                //decrement the num of required ingredients for each recipe
                int rn = mustHaveIng[q.front()][i];
                numOfIng[rn]--;
                if (!numOfIng[rn]) {//we can build this recipe
                    cout << "made " << recipes[rn] << endl;
                    res.push_back(recipes[rn]);
                    //if this recipe is also an ingredient, we can push this recipe to the queue
                    if (mustHaveIng.find(recipes[rn]) != mustHaveIng.end()) {
                        q.push(recipes[rn]);
                    }
                }

            }
            q.pop();
        }
        return res;
    }
};