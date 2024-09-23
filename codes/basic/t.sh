#!/bin/bash
f=${1?"fn"}
o=./.${f%.*}
hf=($(md5sum $f))
mkdir -p .t
p=${f:0:1}
cp -n $f .t/$f.$hf
for i in $p/*.in; do
  a=${i/.in/.ans}
  echo $i
  diff --color $a <($o.$hf* < $i)
done
