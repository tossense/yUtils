#!/bin/bash -x
gprof $@ gmon.out > report.txt

gprof2dot report.txt | dot -Tpng -o report.png

#yum install graphviz
#yum install graphviz-gd.x86_64

