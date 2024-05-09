## ********************FAILED********************

****************************************
## ********************SUCCESS********************
#### *****diff <(./model/cache-ref -v -s 4 -E 1 -b 4 -L -t ./model/traces/fifo_s1.trace) <(./model/cache -v -s 4 -E 1 -b 4 -t ./model/traces/fifo_s1.trace)*****
 ```
```
#### *****diff <(./model/cache-ref -v -s 8 -E 1 -b 5 -L -t ./model/traces/fifo_m1.trace) <(./model/cache -v -s 8 -E 1 -b 5 -t ./model/traces/fifo_m1.trace)*****
 ```
```
#### *****diff <(./model/cache-ref -v -s 10 -E 8 -b 6  -L -t ./model/traces/fifo_l.trace) <(./model/cache -v -s 10 -E 8 -b 6  -t ./model/traces/fifo_l.trace)*****
 ```
```
#### *****diff <(./model/cache-ref -v -s 10 -E 8 -b 6  -L -t ./model/traces/long.trace) <(./model/cache -v -s 10 -E 8 -b 6  -t ./model/traces/long.trace)*****
 ```
```
#### *****diff <(./model/2level-ref -c ./model/2level_1.config  -t ./model/traces/fifo_s2.trace) <(./model/2level -c ./model/2level_1.config -t ./model/traces/fifo_s2.trace)*****
 ```
```
#### *****diff <(./model/2level-ref  -c ./model/2level_2.config -t ./model/traces/long.trace) <(./model/2level -c ./model/2level_2.config -t ./model/traces/long.trace)*****
 ```
```
#### *****diff <(./model/2level-ref -L -c ./model/2level_2.config -t ./model/traces/long.trace) <(./model/2level -L -c ./model/2level_2.config -t ./model/traces/long.trace)*****
 ```
```
#### *****diff <(./model/2level-ref -L -c ./model/2level_3.config -t ./model/traces/long.trace) <(./model/2level -L -c ./model/2level_3.config -t ./model/traces/long.trace)*****
 ```
```
