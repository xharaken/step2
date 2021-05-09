#! /usr/bin/python3

import sys

# How to use:
#
# $ python3 score_checker.py your_answer_file
#

# SCORES of the characters:
# ----------------------------------------
# | 1 point  | a, e, h, i, n, o, r, s, t |
# | 2 points | c, d, l, m, u             |
# | 3 points | b, f, g, p, v, w, y       |
# | 4 points | j, k, q, x, z             |
# ----------------------------------------
SCORES = [1, 3, 2, 2, 1, 3, 3, 1, 1, 4, 4, 2, 2, 1, 1, 3, 4, 1, 1, 1, 2, 3, 3, 4, 3, 4]

WORDS_FILE = "words.txt"

def calculate_score(word):
    score = 0
    for character in list(word):
        score += SCORES[ord(character) - ord('a')]
    return score

def read_words(word_file):
    words = []
    with open(word_file) as f:
        for line in f:
            line = line.rstrip('\n')
            words.append(line)
    return words

def is_anagram(anagram, data):
    data_table = [0] * 26
    for character in data:
        data_table[ord(character) - ord('a')] += 1
    for character in anagram:
        if (data_table[ord(character) - ord('a')] == 0):
            return False
        data_table[ord(character) - ord('a')] -= 1
    return True

def main(data_file, answer_file):
    valid_words = read_words(WORDS_FILE)
    data_words = read_words(data_file)
    answer_words = read_words(answer_file)
    if len(data_words) != len(answer_words):
        print("The number of words in %s and %s doesn't match." %
              (data_file, answer_file))
        exit(1)
    score = 0
    for i in range(len(data_words)):
        if not is_anagram(answer_words[i], data_words[i]):
            print("'%s' is not an anagram of '%s'." %
                  (answer_words[i], data_words[i]))
            exit(1)
        if answer_words[i] not in valid_words:
            print("'%s' is not a valid word!" % answer_words[i])
            exit(1)
        score += calculate_score(answer_words[i])
    print('You answer is correct! Your score is %d.' % score)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: %s data_file your_answer_file" % sys.argv[0])
        exit(1)
    main(sys.argv[1], sys.argv[2])
