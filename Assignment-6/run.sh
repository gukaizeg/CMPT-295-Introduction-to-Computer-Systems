




#!/bin/bash

non_zero=0

function run_multiline_cmd_with_check() {
  bash -c "$@"
  if [[ $? -ne 0 ]] 
  then
    printf "failed"
    ((non_zero++))
  fi
}

function run_cmd_with_check() {
  "$@"
  if [[ $? -ne 0 ]] 
  then
    printf "failed"
    ((non_zero++))
  fi
}

REPO=$PWD
# Build SIMD
# cd $REPO
# mkdir build
# rm -rf build/*
# cd build; cmake ../SIMD/
# run_cmd_with_check make


# Build tracegen
cd $REPO
echo $REPO
run_cmd_with_check python3 driver.py
#run_cmd_with_check python3 driver.py 
cat LOG.md >> LOG

exit ${non_zero}
