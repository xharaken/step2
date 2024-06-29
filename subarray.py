import math, random

# Problem: L is an array of integers. K is an integer (1 <= K <= len(L)).
# Find a subarray of L such that 1) the length of the subarray is equal to or
# larger than K, and 2) the sum of the elements in the subarray is maximized.
#
# For example, if L is [2, -1, -1, -1, 4, -1, 3, 1] and K=3, the subarray
# [4, -1, 3, 1] maximizes the sum and the sum is 7.
#
# Input: L and K
# Output: The maximum sum


# O(N^3) algorithm
def solve_n3(L, K):
    N = len(L)
    max_sum = -math.inf
    for k in range(K, N + 1):
        for i in range(0, N - k + 1):
            sum = 0
            for j in range(i, i + k):
                sum += L[j]
            max_sum = max(max_sum, sum)
    return max_sum


# O(N^2) algorithm
def solve_n2(L, K):
    #-----------------------#
    # Write your code here! #
    #-----------------------#
    return 0


# O(N) algorithm
def solve_n(L, K):
    #-----------------------#
    # Write your code here! #
    #-----------------------#
    return 0


# For a given L and K, run the three algorithms (O(N^3), O(N^2) and O(N))
# and check that all the answers are equal.
def check_answers(L, K):
    answer_n3 = solve_n3(L, K)
    answer_n2 = solve_n2(L, K)
    answer_n = solve_n(L, K)
    if answer_n3 != answer_n2:
        print(L, K)
        print("Correct answer is %d but the O(N^2) algorithm answered %d" % (
            answer_n3, answer_n2))
        exit(0)
    if answer_n3 != answer_n:
        print(L, K)
        print("Correct answer is %d but the O(N) algorithm answered %d" % (
            answer_n3, answer_n))
        exit(0)


# Run tests.
def run_tests():
    # Add your test cases here.
    check_answers([1, -1, -1, -1, 3, 2], 1)
    check_answers([1, -1, -1, -1, 3, 2], 2)
    check_answers([1, -1, -1, -1, 3, 2], 3)
    check_answers([1, -1, -1, -1, 3, 2], 4)

    # Generate many test cases and run.
    for iteration in range(1000):
        length = random.randint(1, 30)
        L = [random.randint(-10, 10) for i in range(length)]
        for K in range(1, length + 1):
            check_answers(L, K)
    print("All tests pass!")


if __name__ == "__main__":
    run_tests()
