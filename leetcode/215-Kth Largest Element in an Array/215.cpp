class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        
        int len = nums.size();
        int left = 0, right = len - 1;
        
        return quick_sort(nums, left, right, k);
    }
    
    int quick_sort(vector<int>& data, int left, int right, int k)
    {
        int i = left;
        int j = right;
        int pivot = data[right];
        int len = right - left + 1;

        if (left < right)
        {  
                    // 从大到小对数组进行快排
            while(i < j)
            {
                while(i < j && data[i] >= pivot) // 从左往右找第一个比 pivot 小的数
                {
                    i++;
                }
                if (i < j)
                {
                    data[j--] = data[i];
                }

                while(i < j && data[j] <= pivot) // 从右往左找第一个比 pivot 大的数
                {
                    j--;
                }
                if (i < j)
                {
                    data[i++] = data[j];
                }
            }
            
            data[i] = pivot; // 此时 i == j

            // pivot 此时位于索引 i 处，i - left + 1 表示 pivot 是第几大的数
            int which_max = i - left + 1;
            if (which_max == k) // pivot 正好是第 k 大的数
            {
                return pivot;
            }
  
            // 第 k 大的数在 pivot 右边，问题转化为找右边数组第 (k - which_max) 大的元素
            // 比如 pivot 是第四大的数，要找第五大的数，则继续找右边数组第一大的数即可
            else if(which_max < k)
            {
                return quick_sort(data, i + 1, right, k - which_max);
            }
            
            // 第 k 大的数在 pivot 左边，问题转化为找左边数组第 k 大的元素
            // 比如 pivot 是第三大的数，要找第二大的数，则继续找左边数组第二大的数即可
            else
            {
                return quick_sort(data, left, i - 1, k);
            }
        }
        else
        {
            return pivot;
        }
    }
    
    /*int quick_sort(vector<int>& data, int left, int right, int k)
    {
        int i = left;
        int j = left;
        int pivot = data[right];
        int len = right - left + 1;

        if (left < right)
        {
            
            // 从大到小对数组进行快排
            for (; j < right; j++)
            {
                if (data[j] > pivot)
                {
                    int temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                    i++;
                }
            }

            data[j] = data[i];
            data[i] = pivot;

            // pivot 此时位于索引 i 处，i - left + 1 表示 pivot 是第几大的数
            int which_max = i - left + 1;
            if (which_max == k) // pivot 正好是第 k 大的数
            {
                return pivot;
            }
  
            // 第 k 大的数在 pivot 右边，问题转化为找右边数组第 (k - which_max) 大的元素
            // 比如 pivot 是第四大的数，要找第五大的数，则继续找右边数组第一大的数即可
            else if(which_max < k)
            {
                return quick_sort(data, i + 1, right, k - which_max);
            }
            
            // 第 k 大的数在 pivot 左边，问题转化为找左边数组第 k 大的元素
            // 比如 pivot 是第三大的数，要找第二大的数，则继续找左边数组第二大的数即可
            else
            {
                return quick_sort(data, left, i - 1, k);
            }
        }
        else
        {
            return pivot;
        }
    }*/
};
