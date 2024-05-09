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
# Build mystery caches
#run_multiline_cmd_with_check "TEST_CACHE=caches/mystery0.o  make cache-test"
#mv cache-test cache-test-mystery0.bin
#run_multiline_cmd_with_check "TEST_CACHE=caches/mystery1.o make cache-test"
#mv cache-test cache-test-mystery1.bin
#run_multiline_cmd_with_check "TEST_CACHE=caches/mystery2.o make cache-test"
#mv cache-test cache-test-mystery2.bin

#
cd model
run_cmd_with_check make clean
run_cmd_with_check make
cd ../


# Build tracegen
#run_cmd_with_check make
run_cmd_with_check python3 driver.py 

cat LOG.md >> LOG

exit ${non_zero}
