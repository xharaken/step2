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


# dfs_with_recursion finds A -> B -> C -> D -> E -> F first.
def dfs_with_recursion(start, goal):
    print("dfs_with_recursion:")
    visited = {}
    path = []

    visited[start] = True
    if recursion(start, goal, visited, path):
        print(" -> ".join(path))
        return
    print("Not found")

def recursion(node, goal, visited, path):
    path.append(node)
    if node == goal:
        return True
    for child in links[node]:
        if not child in visited:
            visited[child] = True
            if recursion(child, goal, visited, path):
                return True
    path.pop()
    return False


# dfs_with_stack finds A -> G -> F first.
def dfs_with_stack(start, goal):
    print("dfs_with_stack:")
    stack = collections.deque()
    visited = {}
    previous = {}

    stack.append(start)
    visited[start] = True
    previous[start] = None
    while len(stack):
        node = stack.pop()
        if node == goal:
            break
        for child in links[node]:
            if not child in visited:
                stack.append(child)
                visited[child] = True
                previous[child] = node

    if goal in previous:
        path = []
        node = goal
        path.append(node)
        while previous[node]:
            node = previous[node]
            path.append(node)
        path.reverse()
        print(" -> ".join(path))
        return
    print("Not found")


# Challenge quiz: Implement DFS using a stack that visits nodes and edges
# in the same order as dfs_with_recursion. In other words, implement DFS that
# finds A -> B -> C -> D -> E -> F first using a stack.
def dfs_with_stack_in_the_recursion_order(start, goal):
    print("dfs_with_stack_in_the_recursion_order:")
    stack = collections.deque()
    visited = {}
    previous = {}

    #------------------------#
    # Write your code here!  #
    #------------------------#

    if goal in previous:
        path = []
        node = goal
        path.append(node)
        while previous[node]:
            node = previous[node]
            path.append(node)
        path.reverse()
        print(" -> ".join(path))
        return
    print("Not found")


dfs_with_stack("A", "F")
dfs_with_recursion("A", "F")
dfs_with_stack_in_the_recursion_order("A", "F")
