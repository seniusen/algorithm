#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-07cb136bd1996498.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

```python
class Solution:
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        
        brace = {'(':')', '{':'}','[':']'}
        left_brace = ['(', '{', '[']
        stack = []
        
        # 建立一个栈，如果是左括号则压栈；
        # 如果是右括号，则与栈顶元素进行匹配，如果刚好匹配，弹出栈顶元素，继续向后进行；
        # 如果不匹配，或者没有元素，返回 false
        # 最后，若栈内还有剩余元素，说明有多余的左括号，返回 false；否则返回 true
        for i in range(len(s)):
        
            if s[i] in left_brace:
                stack.append(s[i])
            
            else:
                if len(stack) == 0 or brace[stack[-1]] != s[i]:
                    return False                
                else:
                    stack.pop()
                    
        if len(stack) == 0: return True
        else: return False
```
