import sys, random

with open("words_original.txt", encoding="utf8", errors='ignore') as f:
    for line in f:
        line = line.rstrip('\n').lower()
        if line.isalpha():
            print(line)
