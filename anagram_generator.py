import sys, random

def read_words(word_file, min_threshold, max_threshold):
    words = []
    with open(word_file) as f:
        for line in f:
            line = line.rstrip('\n')
            if (min_threshold <= len(line) and len(line) <= max_threshold):
                words.append(line)
    return words

def main(word_file, n, min_threshold, max_threshold):
    words = read_words(word_file, min_threshold, max_threshold)
    # print(len(words))
    for i in range(n):
        word = words[int(random.random() * len(words))]
        characters = list(word)
        for j in range(max_threshold - len(characters)):
            characters.append(chr(ord('a') + int(random.random() * 26)))
        assert(len(characters) == max_threshold)
        random.shuffle(characters)
        print(''.join(characters))

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("usage: %s word_file n min_threshold max_threshold" % sys.argv[0])
        exit(1)
    main(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]))
