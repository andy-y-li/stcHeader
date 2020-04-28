#! /bin/sh

libtoolize --automake --copy --force

aclocal

autoheader

automake --foreign --add-missing --copy

autoconf

