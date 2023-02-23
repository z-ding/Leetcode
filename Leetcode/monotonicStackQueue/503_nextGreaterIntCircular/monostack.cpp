class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> stack;
        vector<int> res(nums.size(), -1);
        stack.push_back(0);//push index for easy calculation
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[stack.back()]) {
                while (stack.size() && nums[i] > nums[stack.back()]) {
                    //pop until there is no bigger number in stack than nums[i]
                    res[stack.back()] = nums[i];
                    stack.pop_back();
                }
            }
            stack.push_back(i);
        }
        //we've done a first round of iterating, now the elements on our stack should be monotonic decreasing like [5,4,3]... && there is no bigger number in the right of the array. if we start from the index 0  and iterating once more to the number/index before the last number on the stack, we should be able to find some bigger numbers for the numbers in the stack
        int last = stack.back();
        for (int i = 0; i < last; i++) {
            if (nums[i] > nums[stack.back()]) {
                while (stack.size() && nums[i] > nums[stack.back()]) {
                    //pop until there is no bigger number in stack than nums[i]
                    res[stack.back()] = nums[i];
                    stack.pop_back();
                }
            }
        }

        return res;
    }
};