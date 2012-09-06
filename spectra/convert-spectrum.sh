#!/bin/bash

# See http://reat.space.qinetiq.com/gps/new_gps_sum_files/gps_sum.htm
# and http://reat.space.qinetiq.com/gps/examples/examples.htm (example 19)

F=("$@")
NEWF=$F.converted

out="/gps/hist/point `sed ':a;N;$!ba;s/\n/\n\/gps\/hist\/point /g' $F`"

#echo $out

echo "/gps/hist/point" > $NEWF
sed ':a;N;$!ba;s/\n/\n\/gps\/hist\/point /g' $F >> $NEWF
sed -i ':a;N;$!ba;s/point\n/point /g' $NEWF



