from typing import Optional

def anan():
    print(3)

class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:

   def isValidBST(self, root: Optional[TreeNode]) -> bool:
       ninf, inf = float('-inf'), float('inf')
       def isValidBSTAux(left, root, right):
           if not root:
               return True

           if left > root.val:
               return False
           
           if right < root.val:
               return False

           return isValidBSTAux(left, root.left, root.val) and isValidBSTAux(root.val, root.right, right) 


       return isValidBSTAux(ninf, root, inf)

sol = Solution()
t = TreeNode(5, TreeNode(1), TreeNode(6, TreeNode(3), TreeNode(7)))
print(sol.isValidBST(t))

        
