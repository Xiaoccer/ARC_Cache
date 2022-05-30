#include "lru.h"

int LRUCache::get(int target) {
  if (_capacity <= 0) {
    return -1;
  }

  ++_get_count;
  auto it = _table.find(target);
  if (it != _table.end()) {

    ++_hit_count;
    _items.splice(_items.begin(), _items, it->second);
    return _items.front().second;
  } else {
    if (_items.size() >= _capacity) {
      _table.erase(_items.back().first);
      _items.pop_back();
    }
    _items.emplace_front(target, target);
    _table[target] = _items.begin();
    return _items.front().second;
  }
}

std::string LRUCache::statics() {
  std::stringstream s;
  s << "trace:" << _file_name << " lru_cache:"
    << " cache_size:" << _capacity
    << " request:" <<  _get_count 
    << " hit:" << _hit_count
    << " hit_rate:" << 1.0 * _hit_count / _get_count << std::endl; 
  return s.str();
}