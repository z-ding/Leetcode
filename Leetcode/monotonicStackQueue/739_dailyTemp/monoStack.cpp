class Solution {
public:
    /*
        monotonic stack. e.g. [2,3,1,3,4]
        if (index ==0 ){
            push nums[i] to stack
        } else if (nums[i] > stack.back()){
            while (stack not empty && nums[i] > stack.back()){
                //pop until there is no bigger number in stack than nums[i]
                update result for stack.back()
                stack.pop_back();
            }
            push nums[i] to stack
        } else{//nums[i] > stack.back()
            push nums[i] to stack
        }

        index 0: stack [2]      res[0,0,0,0,0]
        index 1: stack[3]       res[1,0,0,0,0]
        index 2: stack[3,1]     res[1,0,0,0,0]
        index 3: stack[3,3]     res[1,0,1,0,0]
        index 3: stack[4]       res[1,3,1,1,0]
    */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> stack;
        vector<int> res(temperatures.size(), 0);
        stack.push_back(0);//push index for easy calculation
        for (int i = 1; i < temperatures.size(); i++) {
            if (temperatures[i] > temperatures[stack.back()]) {
                while (stack.size() && temperatures[i] > temperatures[stack.back()]) {
                    //pop until there is no bigger number in stack than nums[i]
                    res[stack.back()] = i - stack.back();
                    stack.pop_back();
                }
            }
            stack.push_back(i);
        }
        return res;
    }
};