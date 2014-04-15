LC_ALL=C sort | LC_ALL="zh_CN.GB18030" gawk 'BEGIN{lastkey="__dummy__"} {
                    if(lastkey!="__dummy__" && $1!=lastkey){
                        printf("%s", lastkey);
                        for(i=2;i<=lastNF;++i){ printf("\t%s", val[i]); val[i]=0;}
                        print "";
                    }
                    for(i=2;i<=NF;++i) { val[i]+=$i; }
                    lastNF=NF;
                    lastkey=$1;
                }END{ printf("%s", lastkey); for(i=2;i<=lastNF;++i){ printf("\t%s", val[i]);} print "";}'

