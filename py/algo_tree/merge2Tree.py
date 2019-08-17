'''
valuable technique -- setting t1 and t2 to default objects, to avoid the excessive null check. In this problem, this technique is not absolutely necessary, but very useful in general. See blog for more details
'''
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution(object):
  def mergeTrees(self, t1, t2): #rtype: TreeNode representing merging t1 and t2
    if t1 is None and t2 is None: return None
    if t1 is None: t1 = TreeNode(0)
    if t2 is None: t2 = TreeNode(0)
    print 't1=', (t1.val if t1 else '-'),
    print '; t2=', (t2.val if t2 else '-')
    t1.val += t2.val #OK
        
    t1.left = self.mergeTrees(t1.left, t2.left) 
    t1.right= self.mergeTrees(t1.right, t2.right)    
    return t1
'''
https://bintanvictor.wordpress.com/wp-admin/post.php?post=33877&action=edit
'''