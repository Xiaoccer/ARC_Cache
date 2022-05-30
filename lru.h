#pragma once

#include <unordered_map>
#include <list>
#include <sstream>

class LRUCache {

public:
  explicit LRUCache(int c, std::string file_name): 
      _capacity(c), _file_name(file_name), _hit_count(0), _get_count(0){}

  LRUCache(const LRUCache&) = delete;
  LRUCache& operator=(const LRUCache&) = delete;

  ~LRUCache() {}

public:
  int get(int target);
  std::string statics();

private: 
  std::list<std::pair<int, int>> _items; // (target, cache_addr) 
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> _table;
  int _capacity;
  uint _hit_count;
  uint _get_count;
  std::string _file_name;
};
