from pythonTester import Tester

def main():
    test_cases = Tester.generateArrayMergeTestCases()
    for i, case in enumerate(test_cases):
        print(f"Test Case {i + 1}:")
        print(f"  arr1: {case['arr1']}")
        print(f"  arr2: {case['arr2']}")
        print(f"  m: {case['m']}")
        print(f"  n: {case['n']}")
        print(f"  expected: {case['expected']}\n")

if __name__ == "__main__":
    main()