#!/bin/awk -f
# accumulate results for all results machine files

FNR==1{
  x=0
  # print "resetting";
}

/ALL TIMES:/{
  x=1;
  getline;
  # print "processing"
}

x==1{
  res[$1] = res[$1] "|" $2
}

END{
  for(k in res){
    print k,res[k]
  }
}
