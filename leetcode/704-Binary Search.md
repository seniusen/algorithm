
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        /*
        // 循环法
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;
            
        while(left <= right)
        {
            mid = left + ((right - left) >> 1);
            
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        
        return -1;*/
        
        
        // 递归法
        
        int left = 0;
        int right = nums.size() - 1;
        return binary_search(nums, left, right, target);
    }
    
    int binary_search(vector<int>& nums, int left, int right, int target)
    {

        int mid = 0;

        if (left <= right)
        {
            mid = left + ((right - left) >> 1);

            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                return binary_search(nums, mid+1, right, target);
            }
            else
            {
                return binary_search(nums, left, mid-1, target);
            }
        }

        return -1;
    }
};
