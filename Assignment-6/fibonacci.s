#####################
# Fibonnaci Example #
#####################


.data
  msg2: .string "The "
  msg3: .string " fibonnaci number is: "
  number: .word 10


.text
main:
  li t0, 0
  li t1, 1
     # reads an int and moves it to register t3 
  la t3, number
  lw t3, 0(t3)

  # prints msg2
  li a7, 4
  la a0, msg2
  ecall
  # prints the int value in t3
  li a7, 1
  mv a0, t3
  ecall
  # fibonnaci program

fib:
  beq t3, zero, finish
  add t2, t1, t0
  mv t0, t1
  mv t1, t2
  addi t3, t3, -1
  j fib
finish:
  # prints msg3
  li a7, 4
  la a0, msg3
  ecall
  # prints the result in t0
  li a7, 1
  mv a0, t0
  ecall
  # ends the program with status code 0
  li a7, 10
  ecall
