# CCAligner
Our ICSE 2018 paper, see https://dl.acm.org/citation.cfm?doid=3180155.3180179


Running on 64 bit Linux OS.
Need to install g++, flex and libboost before running.

Conduct ./runner to run the tool.

For example, in this runner file, source files input:/home/wpc/Example

./detect: no filter, complete performance；

./detect2: with filter, for a pair of code, filter minSizeCode1 < 0.5 maxSizeCode2, so faster than ./detect

We recommend the configurations as winsize=6 and edit-distance=1 in our paper which balance recall and precision with performance, shown as ./detect ./token ./output ./function.file 6 1 0.6


Also, you can try other configurations as you like, such as winsize=3 (or 4, 5, 8), and edit-distance=0 (1 or 2).
