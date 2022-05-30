#include "arc.h"

#define min(a,b) ((a < b)? a : b)
#define max(a,b) ((a > b)? a : b)


int ARCCache::get(int target) {
  if (_c <= 0) {
    return -1;
  }

  ++_get_count;
  auto it = _table.find(target);
  if (it != _table.end()) {

    // case1
    if (it->second->lru_type == T1 || it->second->lru_type == T2) {
      move_to_lru(it->second, T2);
      assert_c();
      ++_hit_count;
      return it->second->addr;
    }

    // case2
    if (it->second->lru_type == B1) {
      auto t = _b1.size() >= _b2.size() ? 1: _b2.size() / (double)_b1.size(); 
      _p = min(_p + t, _c);
      replace(false);
      move_to_lru(it->second, T2);
      it->second->addr = target;
      assert_c();
      return it->second->addr;
    }

    // case3
    if (it->second->lru_type == B2) {
      auto t = _b2.size() >= _b1.size() ? 1: _b1.size() / (double)_b2.size(); 
      _p = max(_p - t, 0);
      replace(true);
      move_to_lru(it->second, T2);
      it->second->addr = target;
      assert_c();
      return it->second->addr;
    }

  }

  // case4
  assert(_t1.size() + _b1.size() <= _c); 
  if (_t1.size() + _b1.size() == _c) {
    // case4.1
    if (_t1.size() < _c) {
      _table.erase(_b1.back()->target);
      _b1.pop_back();
      replace(false);
    } else {
      _table.erase(_t1.back()->target);
      _t1.pop_back();
    }
  } else {
    // case 4.2
    assert(_t1.size() + _b1.size() < _c);
    auto size = _t1.size() + _t2.size() + _b1.size() + _b2.size();
    if (size >= _c) {
      if (size == _c * 2) {
        _table.erase(_b2.back()->target);
        _b2.pop_back();
      }
      replace(false);
    }
  }
  std::shared_ptr<ArcEntry> entry = std::make_shared<ArcEntry>();
  entry->target = target;
  entry->addr = target;
  entry->lru_type = T1;
  _t1.push_front(entry);
  _t1.front()->iter = _t1.begin();
  _table[target] = entry;
  assert_c();
  return _t1.front()->addr;

}

void ARCCache::replace(bool in_b2) {
  if (_t1.size() != 0 &&
       ((_t1.size() > _p) || (in_b2 && _t1.size() == _p))) {
    _t1.back()->addr = -1;
    assert(_t1.back()->lru_type == T1);
    move_to_lru(_t1.back(), B1);
  } else {
    _t2.back()->addr = -1;
    assert(_t2.back()->lru_type == T2);
    move_to_lru(_t2.back(), B2);
  }
}

std::string ARCCache::statics() {
  std::stringstream s;
  s << "trace:" << _file_name << " arc_cache:"
    << " cache_size:" << _c
    << " request:" <<  _get_count 
    << " hit:" << _hit_count
    << " hit_rate:" << 1.0 * _hit_count / _get_count << std::endl; 
  return s.str();
}