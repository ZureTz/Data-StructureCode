#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
using std::cout;

constexpr size_t CHUNKSIZE = 25;
struct Chunk {
  char chars[CHUNKSIZE];
  Chunk *prev = nullptr, *next = nullptr;
  Chunk() { std::fill(chars, chars + CHUNKSIZE, 0); }
};

struct LString {
  Chunk *_beginChunk, *_endChunk;
  char *_begin, *_end;

  LString(const char *src) {
    _beginChunk = new Chunk();
    _begin = _beginChunk->chars;
    _endChunk = _beginChunk;
    _end = _begin;
    while (*src) {
      *_end = *src;
      src++;
      _end++;
      if (_end >= _endChunk->chars + CHUNKSIZE) {
        _endChunk->next = new Chunk();
        _endChunk->next->prev = _endChunk;
        _end = _endChunk->next->chars;
        _endChunk = _endChunk->next;
      }
    }
  }

  struct iterator {
    Chunk *atChunk;
    char *ptr;
    explicit iterator(Chunk *atChunk, char *ptr) : atChunk(atChunk), ptr(ptr) {}

    char &operator*() { return *ptr; }
    iterator &operator++() {
      ptr++;
      if (ptr >= atChunk->chars + CHUNKSIZE) {
        atChunk = atChunk->next;
        ptr = atChunk->chars;
      }
      return *this;
    }
    iterator &operator--() {
      ptr--;
      if (ptr < atChunk->chars) {
        atChunk = atChunk->prev;
        ptr = atChunk->chars + CHUNKSIZE - 1;
      }
      return *this;
    }
    bool operator<(const iterator &rhs) const {
      // if in the same chunk
      if (this->atChunk == rhs.atChunk) {
        // cout << "same" << this->ptr - rhs.ptr << std::endl;
        return (this->ptr < rhs.ptr);
      }
      // if not in the same chunk
      auto t1 = this->atChunk, t2 = rhs.atChunk;
      while (t1) {
        if (t1 == t2) {
          return true;
        }
        t1 = t1->next;
      }
      return false;
    }
  };
  iterator begin() const { return iterator(_beginChunk, _begin); }
  iterator end() const { return iterator(_endChunk, _end); }
};

template <typename iterator> bool isReversible(iterator begin, iterator end) {
  --end;
  while (begin < end) {
    // cout << *begin << ' ' << *end << std::endl;
    if (*begin != *end) {
      return false;
    }
    ++begin;
    --end;
  }
  return true;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  const char *stri =
      "abcddcbaabcddcbaabcddcbaabcddcbaabcddcbaabcddcbaabcddcbaabcddcbaabcddcba"
      "abcddcbaabcddcbaabcddcbaabcddcbaabcddcbaabcddcbaabcddcba";
  const LString str(stri);
  int length = strlen(stri);
  cout << str._end[-1] << str._end - str._endChunk->chars << std::endl;

  for (auto it = str.begin(); it < str.end(); ++it) {
    cout.put(*it) << " @ " << it.atChunk << ' ' << it.ptr - it.atChunk->chars
                  << std::endl;
  }
  auto t = str.end();
  cout << *(t) << ' ' << t.atChunk << ' ' << t.ptr - t.atChunk->chars
       << std::endl;
  cout << isReversible(str.begin(), str.end());

  return 0;
}