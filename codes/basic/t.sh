#!/bin/bash
f=${1?"fn"}
ext="${f##*.}"
hf=($(md5sum $f))
mkdir -p .t
p=${f:0:1}
cp -n $f .t/$f.$hf
case $ext in
  cpp)  r=(~/r.sh $f)   ;;
  py)   r=(python3 $f)  ;;
  *)    exit -1         ;;
esac
for i in $p/*.in; do
  a=${i/.in/.ans}
  echo $i
  diff --color -s $a <(${r[*]} < $i) # nl
done
