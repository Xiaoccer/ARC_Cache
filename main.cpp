#include <iostream>
#include <fstream>
#include <string>
#include "arc.h"
#include "lru.h"

struct trace_line {
  int starting_block;
  int number_of_blocks;
  int ignore;
  int request_number;
};

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "usage: " << argv[0] << " <c> <trace_file>\n"
              << "       <c>           -- cache_size\n"
              << "       <trace_file>  -- path of trace_file" << std::endl;
    return 1;
  }

  int c = std::stoi(argv[1]);
  FILE * pFile;
  pFile = fopen(argv[2], "r");
  if (pFile == NULL) {
    std::cerr << "can't not find trace_file" << std::endl;
    return -1;
  }
  
  LRUCache lru_cache(c, argv[2]);
  ARCCache arc_cache(c, argv[2]);

  trace_line l; 
  while (fscanf(pFile, "%d %d %d %d\n",
            &l.starting_block, &l.number_of_blocks, &l.ignore, &l.request_number) != EOF) {
    
    for (auto i = l.starting_block; i < (l.starting_block + l.number_of_blocks); ++i) {
      auto res1 = lru_cache.get(i);
      assert(res1 != -1);
      auto res2 = arc_cache.get(i);
      assert(res2 != -1);
    }
  }
  std::cout << lru_cache.statics();
  std::cout << arc_cache.statics();
  return 0;
}