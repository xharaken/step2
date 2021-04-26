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

def main(answer_file):
    words = read_words(WORDS_FILE)
    answer_words = read_words(answer_file)
    score = 0
    for answer_word in answer_words:
        if answer_word not in words:
            print("'%s' is not a valid word!" % answer_word)
            exit(1)
        score += calculate_score(answer_word)
    print('You answer is correct! Your score is %d.' % score)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: %s your_answer_file" % sys.argv[0])
        exit(1)
    main(sys.argv[1])
