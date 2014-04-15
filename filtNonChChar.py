#!/usr/bin/env python
#! coding: GBK

import os , sys , re 

ch_part = re.compile(u"[\u4e00-\u9fa5]+")

verseflag = 0
if len(sys.argv) > 1:
    if(sys.argv[1] == '-v'):
        verseflag = 1

for line in sys.stdin:
    line_beifen = line.strip()

    line = line.strip().decode('GBK','ignore').split()[ 0 ]

    cnFlag = 1
        
    if len( ch_part.findall(line) ) > 0 and len( ch_part.findall(line)[0] ) == len( line ):
        cnFlag = 1
    else:
        cnFlag = 0
    if (cnFlag == 1 and verseflag == 0) or (cnFlag == 0 and verseflag == 1):
        print line_beifen
    else:
        pass
