import sys

# Cache is a data structure that stores the most recently accessed N pages.
# See the below test cases to see how it should work.
class Cache:
  # Initializes the cache.
  # |n|: The size of the cache.
  def __init__(self, n):
    assert(n >= 1)
    self.list_head_ = {"url": "", "contents": "", "prev": None, "next": None}
    self.list_tail_ = {"url": "", "contents": "", "prev": None, "next": None}
    self.list_head_["next"] = self.list_tail_
    self.list_tail_["prev"] = self.list_head_
    self.n_ = n
    self.count_ = 0
    self.url_to_node_ = {}

  # Access a page and update the cache so that it stores the most
  # recently accessed N pages. This needs to be done with mostly O(1).
  # |url|: The accessed URL
  # |contents|: The contents of the URL
  def access_page(self, url, contents):
    node = None
    if url in self.url_to_node_:
      node = self.url_to_node_[url]
      assert(node["prev"])
      assert(node["next"])
      node["prev"]["next"] = node["next"]
      node["next"]["prev"] = node["prev"]
    else:
      if self.count_ >= self.n_:
        tail = self.list_tail_["prev"]
        del self.url_to_node_[tail["url"]]
        tail["prev"]["next"] = self.list_tail_
        self.list_tail_["prev"] = tail["prev"]
        self.count_ -= 1
      node = {"url": url, "contents": contents, "prev": None, "next": None}
      self.url_to_node_[url] = node
      self.count_ += 1
    node["next"] = self.list_head_["next"]
    node["prev"] = self.list_head_
    self.list_head_["next"]["prev"] = node
    self.list_head_["next"] = node

  # Return the URLs stored in the cache. The URLs are ordered
  # in the order in which the URLs are mostly recently accessed.
  def get_pages(self):
    node = self.list_head_["next"]
    urls = []
    count = 0
    while node["next"]:
      assert(node["url"] != "")
      assert(self.url_to_node_[node["url"]] == node)
      assert(node["prev"]["next"] == node)
      assert(node["next"]["prev"] == node)
      urls.append(node["url"])
      node = node["next"]
      count += 1
    assert(count == self.count_)
    return urls


# Does your code pass all test cases? :)
def cache_test():
  # Set the size of the cache to 4.
  cache = Cache(4)
  # Initially, no page is cached.
  equal(cache.get_pages(), [])
  # Access "a.com".
  cache.access_page("a.com", "AAA")
  # "a.com" is cached.
  equal(cache.get_pages(), ["a.com"])
  # Access "b.com".
  cache.access_page("b.com", "BBB")
  # The cache is updated to:
  #   (most recently accessed)<-- "b.com", "a.com" -->(least recently accessed)
  equal(cache.get_pages(), ["b.com", "a.com"])
  # Access "c.com".
  cache.access_page("c.com", "CCC")
  # The cache is updated to:
  #   (most recently accessed)<-- "c.com", "b.com", "a.com" -->(least recently accessed)
  equal(cache.get_pages(), ["c.com", "b.com", "a.com"])
  # Access "d.com".
  cache.access_page("d.com", "DDD")
  # The cache is updated to:
  #   (most recently accessed)<-- "d.com", "c.com", "b.com", "a.com" -->(least recently accessed)
  equal(cache.get_pages(), ["d.com", "c.com", "b.com", "a.com"])
  # Access "d.com" again.
  cache.access_page("d.com", "DDD")
  # The cache is updated to:
  #   (most recently accessed)<-- "d.com", "c.com", "b.com", "a.com" -->(least recently accessed)
  equal(cache.get_pages(), ["d.com", "c.com", "b.com", "a.com"])
  # Access "a.com" again.
  cache.access_page("a.com", "AAA")
  # The cache is updated to:
  #   (most recently accessed)<-- "a.com", "d.com", "c.com", "b.com" -->(least recently accessed)
  equal(cache.get_pages(), ["a.com", "d.com", "c.com", "b.com"])
  cache.access_page("c.com", "CCC")
  equal(cache.get_pages(), ["c.com", "a.com", "d.com", "b.com"])
  cache.access_page("a.com", "AAA")
  equal(cache.get_pages(), ["a.com", "c.com", "d.com", "b.com"])
  cache.access_page("a.com", "AAA")
  equal(cache.get_pages(), ["a.com", "c.com", "d.com", "b.com"])
  # Access "e.com".
  cache.access_page("e.com", "EEE")
  # The cache is full, so we need to remove the least recently accessed page "b.com".
  # The cache is updated to:
  #   (most recently accessed)<-- "e.com", "a.com", "c.com", "d.com" -->(least recently accessed)
  equal(cache.get_pages(), ["e.com", "a.com", "c.com", "d.com"])
  # Access "f.com".
  cache.access_page("f.com", "FFF")
  # The cache is full, so we need to remove the least recently accessed page "c.com".
  # The cache is updated to:
  #   (most recently accessed)<-- "f.com", "e.com", "a.com", "c.com" -->(least recently accessed)
  equal(cache.get_pages(), ["f.com", "e.com", "a.com", "c.com"])
  print("OK!")

# A helper function to check if the contents of the two lists is the same.
def equal(list1, list2):
  assert(list1 == list2)
  for i in range(len(list1)):
    assert(list1[i] == list2[i])

if __name__ == "__main__":
  cache_test()
