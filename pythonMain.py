from collections import deque
from binaryTree import BinaryTreeNode

class Solutions:
    # O(n) time and O(n) space by hashing
    def twoSumHash(self, nums, target):
        hash_map = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in hash_map:
                return [hash_map[complement], i]
            hash_map[num] = i

    # slow nested loop
    def twoSumLoop(self, nums, target):
        for i in range(len(nums)):
            for j in range(len(nums)): # nested loop mess
                if i != j and nums[i] + nums[j] == target:
                    return i, j

    # builtin sort
    def simpleSortBuiltIn(self, nums):
        return sorted(nums)

    # poor O(n^2)
    def simpleSortBubble(self, nums):
        n = len(nums)
        for i in range(n):
            for j in range(n - i - 1):
                if nums[j] > nums[j + 1]:
                    nums[j], nums[j + 1] = nums[j + 1], nums[j]
        return nums

    def simpleSortMerge(self, nums):
        if len(nums) <= 1:
            return nums
        mid = len(nums) // 2
        left = nums[:mid]
        right = nums[mid:]  # split array
        left = self.simpleSortMerge(left)
        right = self.simpleSortMerge(right)
        return self.merge(left, right)

    # merge helper
    def merge(self, left, right):
        sorted_list = []
        i = j = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                sorted_list.append(left[i])
                i += 1
            else:
                sorted_list.append(right[j])
                j += 1
        sorted_list.extend(left[i:])
        sorted_list.extend(right[j:])
        return sorted_list

    # quick sort with recursive pivot
    def simpleSortQuick(self, nums):
        if len(nums) <= 1:
            return nums
        pivot = nums[0] 
        left = []
        right = []
        for num in nums[1:]:
            if num < pivot:
                left.append(num)
            else:
                right.append(num)
        return self.simpleSortQuick(left) + [pivot] + self.simpleSortQuick(right)
    
    # selection and insertion are similar
    def simpleSortSelection(self, nums):
        n = len(nums)
        for i in range(n):
            min_index = i
            for j in range(i + 1, n): 
                if nums[j] < nums[min_index]:
                    min_index = j
            nums[i], nums[min_index] = nums[min_index], nums[i]
        return nums
    

    def simpleSortInsertion(self, nums):
        n = len(nums)
        for i in range(1, n):
            key = nums[i]
            j = i - 1
            while j >= 0 and key < nums[j]:
                nums[j + 1] = nums[j]
                j -= 1
            nums[j + 1] = key
        return nums
    
    # merge arrays with two "pointers"
    def arrayMergeNormal(self, nums1, m, nums2, n):
        i = m - 1
        j = n - 1
        k = m + n - 1
        while i >= 0 and j >= 0:
            if nums1[i] > nums2[j]:
                nums1[k] = nums1[i]
                i -= 1
            else:
                nums1[k] = nums2[j]
                j -= 1
            k -= 1
        while j >= 0:
            nums1[k] = nums2[j]
            j -= 1
            k -= 1
        return nums1
    
    # merge arrays with built-in sort
    def arrayMergeBuiltIn(self, nums1, m, nums2, n):
        nums1[m:] = nums2
        return sorted(nums1)
    
    # merge arrays manually with loops
    def arrayMergeLoop(self, nums1, m, nums2, n):
        arr = []
        i, j = 0, 0
        while i < m and j < n:
            if nums1[i] < nums2[j]:
                arr.append(nums1[i])
                i += 1
            else:
                arr.append(nums2[j])
                j += 1
        while i < m:
            arr.append(nums1[i])
            i += 1
        while j < n:
            arr.append(nums2[j])
            j += 1
        return arr
    
    # dfs for min depth of tree
    def minimumBinaryTreeDepthDFS(self, root):
        if not root:
            return 0
        left = self.minimumBinaryTreeDepthDFS(root.left)
        right = self.minimumBinaryTreeDepthDFS(root.right)
        if left == 0 or right == 0:
            return max(left, right) + 1
        return min(left, right) + 1
    
    # bfs for min depth of tree
    def minimumBinaryTreeDepthBFS(self, root):
        if not root:
            return 0
        queue = deque([(root, 1)])
        while queue:
            node, depth = queue.popleft()
            if not node.left and not node.right:
                return depth
            if node.left:
                queue.append((node.left, depth + 1))
            if node.right:
                queue.append((node.right, depth + 1))
