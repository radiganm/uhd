#!/bin/bash
## bootstrap.sh
## Mac Radigan

  d=${0%/*}; f=${0##*/}; n=${f%.*}; e=${f##*.}
  r=`readlink -f $d`

  dest=/opt/uhd
  mkdir -p ${dest}
 (                                         \
  rm -f ./CMakeCache.txt;                  \
  cmake                                    \
   -DCMAKE_INSTALL_PREFIX=${dest}          \
   -DCMAKE_CXX_FLAGS="-std=c++11"          \
   -DBUILD_STATIC_LIBS=ON                  \
   -DBUILD_SHARED_LIBS=ON                  \
   -DCMAKE_VERBOSE=1                       \
   -DCMAKE_VERBOSE_MAKEFILE=ON             \
   -DBOOST_ROOT=/opt/boost                 \
   -DBOOST_INCLUDEDIR=/opt/boost/include   \
   -DBOOST_LIBRARYDIR=/opt/boost/lib       \
   -DBoost_NO_SYSTEM_PATHS=ON              \
   -DBoost_ADDITIONAL_VERSIONS=106501      \
   .                                       \
  )

  make

## *EOF*
