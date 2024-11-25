from pythonMain import Solutions
import random
import time
import tracemalloc
from collections import deque
from binaryTree import BinaryTreeNode
import sys
sys.setrecursionlimit(2000)

class Tester:
    # generates test cases for two sum
    @staticmethod
    def generateTwoSumTestCases(num_cases=10000, max_length=100, value_range=(-10**9, 10**9)):
        test_cases = []
        for _ in range(num_cases):
            length = random.randint(2, max_length)
            nums = [random.randint(value_range[0], value_range[1]) for _ in range(length)]
            index1, index2 = random.sample(range(length), 2)
            target = nums[index1] + nums[index2]
            test_cases.append({
                "nums": nums,
                "target": target,
                "expected": sorted([index1, index2])
            })
        return test_cases

    # makes sorting test cases
    @staticmethod
    def generateSortTestCases(num_cases=10000, max_length=300, value_range=(-10**9, 10**9)):
        test_cases = []
        for _ in range(num_cases):
            length = random.randint(1, max_length)
            nums = [random.randint(value_range[0], value_range[1]) for _ in range(length)]
            expected = sorted(nums)
            test_cases.append({
                "nums": nums,
                "expected": expected
            })
        return test_cases

    # makes test cases for merging two arrays
    @staticmethod
    def generateArrayMergeTestCases(num_cases=10000, max_length=1000, value_range=(-10**9, 10**9)):
        test_cases = []
        for _ in range(num_cases):
            length1 = random.randint(1, max_length)
            length2 = random.randint(1, length1)

            arr2 = [random.randint(value_range[0], value_range[1]) for _ in range(length2)]

            arr1 = [random.randint(value_range[0], value_range[1]) for _ in range(length1 - length2)]
            arr1 = sorted(arr1)
            arr1.extend([0] * (length2))

            expected = sorted(arr1[:length1 - length2] + arr2)
            arr2 = sorted(arr2)

            test_cases.append({
                "arr1": arr1,
                "arr2": arr2,
                "m": length1 - length2,
                "n": length2,
                "expected": expected
            })
        return test_cases

    # generates test cases for finding min depth of binary trees
    def generate_minimum_binary_tree_depth_test_cases(num_cases=10000, max_depth=1500):
        test_cases = []

        for _ in range(num_cases):
            root = BinaryTreeNode(1)
            min_depth = random.randint(2, max_depth)

            current_level_nodes = [root]
            for depth in range(2, min_depth):
                next_level_nodes = []
                for node in current_level_nodes:
                    if random.choice([True, False]):
                        node.insertLeft(depth)
                        next_level_nodes.append(node.left)
                    else:
                        node.insertRight(depth)
                        next_level_nodes.append(node.right)

                current_level_nodes = next_level_nodes

            leaf_node = random.choice(current_level_nodes)
            if random.choice([True, False]):
                leaf_node.insertLeft(min_depth)
            else:
                leaf_node.insertRight(min_depth)

            current_level_nodes = [node for node in current_level_nodes if node != leaf_node]

            current_depth = min_depth + 1

            while current_depth <= max_depth:
                next_level_nodes = []
                for node in current_level_nodes:
                    if random.choice([True, False]):
                        node.insertLeft(current_depth)
                        next_level_nodes.append(node.left)
                    if random.choice([True, False]):
                        node.insertRight(current_depth)
                        next_level_nodes.append(node.right)

                current_level_nodes = next_level_nodes
                current_depth += 1

                if not current_level_nodes:
                    break

            test_cases.append({"root": root, "expected": min_depth})

        return test_cases

    # runs two sum test cases
    @staticmethod
    def runTwoSumTestCases(test_cases, solution_func):
        tracemalloc.start()
        passed_cases = 0
        start_time = time.time()

        for i, case in enumerate(test_cases):
            nums = case["nums"]
            target = case["target"]
            expected = case["expected"]

            try:
                result = solution_func(nums, target)
                if sorted(result) == expected:
                    passed_cases += 1
                else:
                    print(f"Test case {i + 1} failed:")
                    print(f"  Input: nums={nums}, target={target}")
                    print(f"  Expected: {expected}, but got: {result}")
            except Exception as e:
                print(f"Test case {i + 1} encountered an error: {e}")

        end_time = time.time()
        _, peak_memory = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        total_time = end_time - start_time
        avg_time_per_case = total_time / len(test_cases)

        print(f"\nResults for {solution_func.__name__}:")
        print(f"Passed {passed_cases} out of {len(test_cases)} test cases.")
        print(f"Total time taken: {total_time:.4f} seconds")
        print(f"Average time per test case: {avg_time_per_case:.4f} seconds")
        print(f"Peak memory usage: {peak_memory / (1024 * 1024):.4f} MB")

    # runs sort test cases
    @staticmethod
    def runSortTestCases(test_cases, solution_func):
        tracemalloc.start()
        passed_cases = 0
        start_time = time.time()

        for i, case in enumerate(test_cases):
            nums = case["nums"]
            expected = case["expected"]

            try:
                result = solution_func(nums)
                if result == expected:
                    passed_cases += 1
                else:
                    print(f"Test case {i + 1} failed:")
                    print(f"  Input: nums={nums}")
                    print(f"  Expected: {expected}, but got: {result}")
            except Exception as e:
                print(f"Test case {i + 1} encountered an error: {e}")

        end_time = time.time()
        _, peak_memory = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        total_time = end_time - start_time
        avg_time_per_case = total_time / len(test_cases)

        print(f"\nResults for {solution_func.__name__}:")
        print(f"Passed {passed_cases} out of {len(test_cases)} test cases.")
        print(f"Total time taken: {total_time:.4f} seconds")
        print(f"Average time per test case: {avg_time_per_case:.4f} seconds")
        print(f"Peak memory usage: {peak_memory / (1024 * 1024):.4f} MB")

    # runs array merge test cases
    @staticmethod
    def runArrayMergeTestCases(test_cases, solution_func):
        tracemalloc.start()
        passed_cases = 0
        start_time = time.time()

        for i, case in enumerate(test_cases):
            arr1 = case["arr1"][:]
            arr2 = case["arr2"]
            m = case["m"]
            n = case["n"]
            expected = case["expected"]

            try:
                result = solution_func(arr1, m, arr2, n)
                if result == expected:
                    passed_cases += 1
                else:
                    print(f"Test case {i + 1} failed:")
                    print(f"  Input: arr1={arr1}, arr2={arr2}")
                    print(f"  Expected: {expected}, but got: {result}")
            except Exception as e:
                print(f"Test case {i + 1} encountered an error: {e}")

        end_time = time.time()
        _, peak_memory = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        total_time = end_time - start_time
        avg_time_per_case = total_time / len(test_cases)

        print(f"\nResults for {solution_func.__name__}:")
        print(f"Passed {passed_cases} out of {len(test_cases)} test cases.")
        print(f"Total time taken: {total_time:.4f} seconds")
        print(f"Average time per test case: {avg_time_per_case:.4f} seconds")
        print(f"Peak memory usage: {peak_memory / (1024 * 1024):.4f} MB")

    # runs binary tree depth test cases
    @staticmethod
    def runMinimumBinaryTreeDepthTestCases(test_cases, solution_func):
        tracemalloc.start()
        passed_cases = 0
        start_time = time.time()

        for i, case in enumerate(test_cases):
            root = case["root"]
            expected = case["expected"]

            try:
                result = solution_func(root)
                if result == expected:
                    passed_cases += 1
                else:
                    print(f"Test case {i + 1} failed:")
                    print(f"  Input: root={root}")
                    print(f"  Expected: {expected}, but got: {result}")
            except Exception as e:
                print(f"Test case {i + 1} encountered an error: {e}")

        end_time = time.time()
        _, peak_memory = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        total_time = end_time - start_time
        avg_time_per_case = total_time / len(test_cases)

        print(f"\nResults for {solution_func.__name__}:")
        print(f"Passed {passed_cases} out of {len(test_cases)} test cases.")
        print(f"Total time taken: {total_time:.4f} seconds")
        print(f"Average time per test case: {avg_time_per_case:.4f} seconds")
        print(f"Peak memory usage: {peak_memory / (1024 * 1024):.4f} MB")

    @staticmethod
    def run_all_tests():
        solutions = Solutions()

        print("-----Two Sum-----")

        twoSumTestCases = Tester.generateTwoSumTestCases()
        Tester.runTwoSumTestCases(twoSumTestCases, solutions.twoSumHash)
        Tester.runTwoSumTestCases(twoSumTestCases, solutions.twoSumLoop)

        print("-----Sorting Algorithms-----")

        sortTestCases = Tester.generateSortTestCases()
        Tester.runSortTestCases(sortTestCases, solutions.simpleSortQuick)
        Tester.runSortTestCases(sortTestCases, solutions.simpleSortBubble)
        Tester.runSortTestCases(sortTestCases, solutions.simpleSortBuiltIn)
        Tester.runSortTestCases(sortTestCases, solutions.simpleSortMerge)
        Tester.runSortTestCases(sortTestCases, solutions.simpleSortSelection)
        Tester.runSortTestCases(sortTestCases, solutions.simpleSortInsertion)

        print("-----Array Merge-----")

        arrayMergeTestCases = Tester.generateArrayMergeTestCases()
        Tester.runArrayMergeTestCases(arrayMergeTestCases, solutions.arrayMergeBuiltIn)
        Tester.runArrayMergeTestCases(arrayMergeTestCases, solutions.arrayMergeLoop)
        Tester.runArrayMergeTestCases(arrayMergeTestCases, solutions.arrayMergeNormal)

        print("-----Minimum Binary Tree Depth-----")

        minimumBinaryTreeDepthTestCases = Tester.generate_minimum_binary_tree_depth_test_cases()
        Tester.runMinimumBinaryTreeDepthTestCases(minimumBinaryTreeDepthTestCases, solutions.minimumBinaryTreeDepthBFS)
        Tester.runMinimumBinaryTreeDepthTestCases(minimumBinaryTreeDepthTestCases, solutions.minimumBinaryTreeDepthDFS)

if __name__ == "__main__":
    Tester.run_all_tests()