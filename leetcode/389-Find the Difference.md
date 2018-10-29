
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-79e172f7da6c7466.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

#### 2.1. 方法一

将 s 和 t 转化为 Python 的列表，然后遍历列表  s 的元素，**将它们从列表 t 中删除，最后列表 t 中会余下一个元素，即为所求**。
```python
class Solution:
    def findTheDifference(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        s_list = list(s)
        t_list = list(t)
        for i in s_list:
            t_list.remove(i)
        return t_list[0]
```
#### 2.2. 方法二

将 t 转化为 Python 的集合，由于集合元素的互异性，这个过程会去掉重复元素，然后再将其转化为列表 r，此时 r 包含 t 中的所有字符。

遍历 r 中的字符，然后**分别计数其在  s 和 t 中出现的次数，如果二者不相等，则当前字符即为所求**。
```python
class Solution:
    def findTheDifference(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """

        r = list(set(t))
        result = ' '
        for i in r:
            if s.count(i) != t.count(i):
                result = i
                return result
```

#### 2.3. 方法三

将 **t 中所有字符的 ASCII 码之和减去 s 中所有字符的 ASCII 码之和**，最后的差对应的字符即为所求。

```c
class Solution {
public:
    char findTheDifference(string s, string t) {
        
        int count = 0;
        
        string::iterator i1 = s.begin(), i2 = t.begin();
        
        for (; i1 != s.end() && i2 != t.end(); i1++, i2++)
        {
            count += *i2 - *i1; 
        }
        
        count = count + *i2;
        
        return char(count);
        
    }
};
```

#### 2.4. 方法四

利用**按位异或运算**。假设有两个数 a， b，按位异或可以实现两个数的交换。
```c
a = a ^ b
b = a ^ b = a ^ b ^ b = a ^ 0 = a
a = a ^ b =  a ^ b ^ a = b
```
因此，我们可以将 s 和 t 中的元素按位异或，**相同的元素按位异或之后都会变成零**，最后的结果即为所求。

```c
class Solution {
public:
    char findTheDifference(string s, string t) {
              
        int count = 0;
        
        string::iterator i1 = s.begin(), i2 = t.begin();
        
        for (; i1 != s.end() && i2 != t.end(); i1++, i2++)
        {
            count = *i2 ^ *i1 ^ count; 
        }
        
        count = count ^ *i2;
        
        return char(count);
        
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
