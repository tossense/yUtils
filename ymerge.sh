gawk '{OFS="\t";if($1 in buf) { key=$1; $1=""; buf[key]=buf[key]$0;} else buf[$1]=$0; } END{for(c in buf) print buf[c];}'
