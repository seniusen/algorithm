
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-53cf410738017faf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

#### 2.1. 方法一

我们从前往后遍历字符串，start 代表最长子串的起始位置，一开始设置为零。

如果没有遇到重复字符，则更新子串的长度，向后遍历。

如果遇到重复字符时，则更新字符串起始位置为**上一个相同字符的后面一个位置**，同时更新子串长度。

重复上面这个过程，直到遍历完毕。

>'abcabc'，start = 0，str_len = 1, 2, 3
此时第二次遇到 'a'，start = 1，str_len = 3
此时第二次遇到 'b'，start = 2，str_len = 3
此时第二次遇到 'c'，start = 3，str_len = 3


```python
class Solution:
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """

        max_len = 0
        str_len = 0
        start = 0      # 最长子串的起始位置
        index = 0     # 上一个相同字符在子串中的位置，是一个相对位置，不是在原字符串中的位置
        
        for i in range(len(s)):
            
            if (s[i] not in s[start:i]):
                str_len += 1
               
            # 如果遇到重复字符，更新子串的起始位置为上一个相同字符的后面一个位置
            # 同时我们需要更新子串长度
            else:
                max_len = max(max_len, str_len)
                index = s[start:i].find(s[i])
                str_len = str_len - index
                start = start + index + 1 
                
        max_len = max(max_len, str_len) # 一直没有遇到重复字符
        return max_len
```
#### 2.2. 方法二

方法一中，我们每次判断当前字符是否为重复字符时，都需要在子串中进行搜索，更新子串起始位置时，也要在子串中搜索上一个相同字符的位置，效率很低。

其实我们需要知道的就是**一个子串的起始位置**，然后往后遍历的时候只需要在适当的时候更新这个起始位置重新计算子串长度即可。

因此，我们可以建立一个**当前字符和当前字符下一个位置**的映射。

所有映射全部初始化为零，start = 0。从前往后开始遍历字符串，同时更新映射，计算子串长度。

**如果当前字符的映射大于 start，说明在 satrt 后面出现过当前字符，就更新 start**。


```python
class Solution:
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len = 0
        str_len = 0
        start = 0    # 最长子串的起始位置
        index = 0   # 重复的字符在子串中的位置
        
        # 初始化映射
        table = []
        for i in range(128):
            table.append(0)
                
        for i in range(len(s)):
            
            start =  max(start, table[ord(s[i])])

            str_len = i - start + 1    
            max_len = max(max_len, str_len)
            
            table[ord(s[i])] = i + 1
            
        return max_len
```

```c
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        int table[128] = {0}; // 自动初始化为零
        int max_len = 0;
        int str_len = 0;
        int start = 0;
        
        string::iterator it = s.begin();
            
        for (int j = 0; it != s.end(); it++, j++)
        {
            start = start > table[*it] ? start : table[*it];
            table[*it] = j + 1;
            str_len = j - start + 1;
            max_len = max_len < str_len ? str_len : max_len;
        }
        
        return max_len;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

