#!/bin/bash

non_zero=0

function run_cmd_with_check() {
  "$@"
  if [[ $? -ne 0 ]] 
  then
    printf "failed"
    ((non_zero++))
  fi
}

REPO=$PWD
cd $REPO/Arraylist
run_cmd_with_check make clean
run_cmd_with_check make 
# cd $REPO/Cipher
# run_cmd_with_check make clean
# run_cmd_with_check make
cd $REPO/word-count
run_cmd_with_check make clean
run_cmd_with_check make
cd $REPO
run_cmd_with_check python3 driver.py 
cat LOG.md >> LOG

exit ${non_zero}
