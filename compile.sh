#!/bin/sh
set -eu

srcdir="$HOME/projects/stm32_test"
blddir="/tmp/stm32_test"

case "${1:-}" in
  clean)
    rm -rf "$blddir"
    ;;
  *)
    if ! [ -e "$blddir/build.ninja" ]; then
      meson setup --cross-file "$srcdir/meson-cross.txt" "$srcdir" "$blddir"
    fi
    meson compile -C "$blddir" $@
esac
