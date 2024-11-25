class BinaryTreeNode:
    def __init__(self, root):
        self.key = root
        self.left = None
        self.right = None

    def insertLeft(self, newNode):
        if self.left == None:
            self.left = BinaryTreeNode(newNode)
        else:
            t = BinaryTreeNode(newNode)
            t.left = self.left
            self.left = t

    def insertRight(self, newNode):
        if self.right == None:
            self.right = BinaryTreeNode(newNode)
        else:
            t = BinaryTreeNode(newNode)
            t.right = self.right
            self.right = t

    def right(self):
        return self.right

    def left(self):
        return self.left

    def setVal(self, val):
        self.key = val

    def getVal(self):
        return self.key