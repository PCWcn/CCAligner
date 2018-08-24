# CCAligner
ICSE 2018 paper, see https://dl.acm.org/citation.cfm?doid=3180155.3180179


Running on 64 bit Linux OS.
Need to install g++, flex and libboost before running.

Conduct ./runner to run the tool.

In this runner file, source files input:/home/wpc/Example

./detect: no filter, complete performance；

./detect2: with filter, for a pair of code, filter minSizeCode1 < 0.5 maxSizeCode2, so faster than ./detect
