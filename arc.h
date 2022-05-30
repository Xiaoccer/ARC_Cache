#pragma once

#include <cassert>
#include <list>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <sstream>

enum LruType {
  T1,
  B1,
  T2,
  B2,
  None,
};

struct ArcEntry;

using ArcEntryPtr = std::shared_ptr<ArcEntry>;

struct ArcEntry {
  int target;
  int addr;
  LruType lru_type;
  std::list<ArcEntryPtr>::iterator iter;
};

class ARCCache {

public:
  explicit ARCCache(int c, std::string file_name): _c(c), _p(0),
                            _file_name(file_name), _hit_count(0), _get_count(0) {
  
  _list_table[T1] = &_t1;
  _list_table[T2] = &_t2;
  _list_table[B1] = &_b1;
  _list_table[B2] = &_b2;
  }

  ARCCache(const ARCCache&) = delete;
  ARCCache& operator=(const ARCCache&) = delete;

  ~ARCCache() {}

public:
  int get(int target);
  std::string statics();

private:
  
  inline void move_to_lru(ArcEntryPtr entry, const LruType& lru_type) {
    auto l = _list_table[lru_type]; 
    l->splice(l->begin(), *_list_table[entry->lru_type], entry->iter);
    entry->lru_type = lru_type;
  }

  void replace(bool in_b2);

  inline void assert_c() {
    assert(_t1.size() + _t2.size() <= _c);
    assert(_t1.size() + _b1.size() <= _c);
    assert(_t2.size() + _b2.size() <= _c * 2);
    assert(_t1.size() + _b1.size()  + _t2.size() + _b2.size() <= _c * 2);
  }

private:
  std::list<ArcEntryPtr> _t1;
  std::list<ArcEntryPtr> _b1;
  std::list<ArcEntryPtr> _t2;
  std::list<ArcEntryPtr> _b2;
  std::unordered_map<LruType, std::list<ArcEntryPtr>*> _list_table;
  std::unordered_map<int, ArcEntryPtr> _table;
  int _c;
  double _p;
  uint _hit_count;
  uint _get_count;
  std::string _file_name;

};