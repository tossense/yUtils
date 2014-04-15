#!/usr/bin/python
# coding=gbk

def get_hz_py(str):
    hz, py, jp = ("" , "", "")
    i=0
    firstpych = True 
    while i < len(str):
        if str[i] >= 'a' and str[i] <= 'z' or str[i] == '\'' or str[i] == '-':
            if firstpych:
                jp += str[i];
            firstpych = False
            py += str[i]
            i += 1
        else:
            py += '\''
            hz += str[i:i+2]
            i += 2;
            firstpych = True
    return (hz,py,jp)

if __name__ == '__main__':
    import sys,getopt

    try:
        opts, args = getopt.getopt(sys.argv[1:], "f:")
    except getopt.GetoptError, err:
        print >> sys.stderr, str(err)
        sys.exit(2)
    fields=1
    for o, a in opts:
        if o == '-f':
            fields=int(a)
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        (istart, iend, cf)= (0, 0, 0)
        (hzs,pys) = ([0]*fields,[0]*fields)
        while cf < fields:
            while iend < len(line) and not line[iend].isspace():
                iend += 1
            hz,py,jp = get_hz_py(line[istart:iend])
            (hzs[cf], pys[cf]) = (hz, py)
            cf += 1
            while iend < len(line) and line[iend].isspace():
                iend +=1
            if iend >= len(line):
                break
            istart = iend
        print '\t'.join([line.rstrip(), '\t'.join(hzs), '\t'.join(pys)])
 
