# the C++ implement of Adaptive Replacement Cache (ARC) Algorithm

the C++ implement of ARC cache replacement algorithm, refer to the [paper](https://www.usenix.org/conference/fast-03/arc-self-tuning-low-overhead-replacement-cache).

## Build
``make``

## Usage
Output the hit rate of ARC and LRU cache algorithm.
```
./cahce <c> <trace_file>
        <c>           -- cache_size
        <trace_file>  -- path of trace_file
```

## Tests
Run tests of all traces. The result is written on output.txt, and the result is same to the paper.

``make test``

## Notes
* [知乎专栏](https://zhuanlan.zhihu.com/p/522306900)

## Reference resources
* [caching](https://github.com/djblue/caching)
* [IBM Resarch](https://researcher.watson.ibm.com/researcher/view_person_subpage.php?id=4700)
