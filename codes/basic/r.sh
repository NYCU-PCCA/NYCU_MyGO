#!/bin/bash
f=${1?"fn"}
o=./.${f%.*}
hf=($(md5sum $f))
if [ $# = 1 ] || [ $2 = 1 ]; then
  ARGS="-DDEBUG -I$HOME/include_debug"
else
  ARGS="-I$HOME/include"
fi
ARGS+="${@:2:$#}"
ha=($(echo "$ARGS" | md5sum))
s=.$hf.$ha
if [ -e $o$s ]; then
  time >&2 echo cached
else
  rm $o* || true
  set -eux
  time g++ -std=c++20 -Wall -Wextra -Wshadow \
    -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
    -Wconversion $ARGS $f -o $o$s
  # -fsanitize=address -fsanitize=undefined
fi
time $o$s
