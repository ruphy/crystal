#!/bin/bash

F=("$@")
NEWF=$F.converted

out="/gps/hist/point `sed ':a;N;$!ba;s/\n/\n\/gps\/hist\/point /g' $F`"

#echo $out

echo "/gps/hist/point" > $NEWF
sed ':a;N;$!ba;s/\n/\n\/gps\/hist\/point /g' $F >> $NEWF
sed -i ':a;N;$!ba;s/point\n/point /g' $NEWF



