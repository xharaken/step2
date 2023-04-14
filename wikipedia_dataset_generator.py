import sys

class Wikipedia:

    def __init__(self, pages_file, links_file):
        self.titles = {}
        with open(pages_file) as file:
            for line in file:
                (id, title) = line.rstrip().split(" ")
                id = int(id)
                assert not id in self.titles
                self.titles[id] = title
        print("Finished reading %s" % pages_file)

        self.links = {}
        with open(links_file) as file:
            for line in file:
                (src, dst) = line.rstrip().split(" ")
                src = int(src)
                dst = int(dst)
                # assert src in self.titles, "%d" % src
                # assert dst in self.titles, "%d" % dst
                if not src in self.links:
                    self.links[src] = []
                self.links[src].append(dst)
        print("Finished reading %s" % links_file)


    def generate_dataset(self):
        id_max = max(self.titles)
        print(id_max)
        THRESHOLD = id_max / 4

        with open("pages_large.txt", mode="w") as file:
            for id in sorted(self.titles.keys()):
                file.write("%d %s\n" % (id, self.titles[id]))

        with open("links_large.txt", mode="w") as file:
            for id in sorted(self.titles.keys()):
                if id in self.links:
                    for dst in sorted(self.links[id]):
                        if dst in self.titles:
                            file.write("%d %d\n" % (id, dst))

        with open("pages_medium.txt", mode="w") as file:
            for id in sorted(self.titles.keys()):
                if id < THRESHOLD:
                    file.write("%d %s\n" % (id, self.titles[id]))

        with open("links_medium.txt", mode="w") as file:
            for id in sorted(self.titles.keys()):
                if id < THRESHOLD and id in self.links:
                    for dst in sorted(self.links[id]):
                        if dst < THRESHOLD and dst in self.titles:
                            file.write("%d %d\n" % (id, dst))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: %s pages_file links_file" % sys.argv[0])
        exit(1)

    wikipedia = Wikipedia(sys.argv[1], sys.argv[2])
    wikipedia.generate_dataset()
