#! /usr/bin/python3
import collections


# An example graph structure
links = {"A": ["B","E","G"],
         "B": ["C"],
         "C": ["D"],
         "D": ["E"],
         "E": ["B","F"],
         "F": [],
         "G": ["F"]}


# dfs_with_stack visits the nodes in the order of:
#   A -> B -> E -> G -> F -> C -> D
def dfs_with_stack():
    print("dfs_with_stack:")
    start = "A"
    stack = collections.deque()
    visited = {}
    visited_order = []

    stack.append(start)
    visited[start] = True
    visited_order.append(start)
    while len(stack):
        node = stack.pop()
        for child in links[node]:
            if not child in visited:
                stack.append(child)
                visited[child] = True
                visited_order.append(child)
    print(" -> ".join(visited_order))


# dfs_with_recursion visits the nodes in the order of:
#   A -> B -> C -> D -> E -> F -> G
def dfs_with_recursion():
    print("dfs_with_recursion:")
    start = "A"
    visited = {}
    visited_order = []

    visited[start] = True
    visited_order.append(start)
    recursion(start, visited, visited_order)
    print(" -> ".join(visited_order))

def recursion(current, visited, visited_order):
    for child in links[current]:
        if not child in visited:
            visited[child] = True
            visited_order.append(child)
            recursion(child, visited, visited_order)


# Challenge quiz: Implement DFS that visits the nodes in the same order as
# dfs_with_recursion without using recursion (i.e., using a stack)
#   A -> B -> C -> D -> E -> F -> G
def dfs_with_stack_in_the_recursion_order():
    print("dfs_with_stack_in_the_recursion_order:")
    start = "A"
    stack = collections.deque()
    visited = {}
    visited_order = []

    #------------------------#
    # Write your code here!  #
    #------------------------#
    print(" -> ".join(visited_order))


dfs_with_stack()
dfs_with_recursion()
dfs_with_stack_in_the_recursion_order()
