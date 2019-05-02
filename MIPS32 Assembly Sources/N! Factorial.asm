#----------------------------------------------------------------------------------------------------------------------------------------
#Program Description:	This program program is written to recursively calculate the factorial of "N!". 
#			"N" can be any number ranging from 0 - 10. (0 <= N <= 10)
#Author:		DeAndre Baldwin
#----------------------------------------------------------------------------------------------------------------------------------------
.data
userInput: .asciiz "Enter a number (0 - 10) to calculate its factorial!: "
badUserInputBLT: .asciiz " is not a valid number to check (Less than 0). Please select a number ranging from 0 - 10, like we asked. Think of the poor processor!\n"
badUserInputBGT: .asciiz " is not a valid number to check (Greater than 10). Please select a number ranging from 0 - 10, like we asked. Think of the poor processor!\n"
factorialOutput: .asciiz "The calculated factorial(N!) of your number(N) is: "
productThing: .asciiz "\nProduct: "
.text
#-------------------------#
#	 Registers	  #
#-------------------------#
# $s0 - User Input	  #
# $s1 - Factorial Product #
# $s2 - Iterator	  #	
# $s3 - Recursive Input   #
# $s4 - (N-(N-1)	  #
# $t1 - Low Register	  #
# %t2 - blt Compare (0)   #
# $t3 - bgt Compare (10)  #
#-------------------------#
getUserInput:
li $v0, 4
la $a0, userInput
syscall

li $v0, 5
syscall

add $s0, $0, $v0
addi $s2, $0, 0
sub $s3, $s0, 1						# Initialize to (N-1)
sub $s4, $s0, 1
addi $t2, $0, 0
addi $t3, $0, 10
blt $s0, $t2, Error1
bgt $s0, $t3, Error2
beq $s0, $t2, ZeroCase					# Issa 1

beginLoop:
beq $s2, $s4, Finished					# Once we loop through the factorial calculation "N-1" times, goto Finished
add $s2, $s2, 1						# Increase our iterator register by "1" until $s2 == ($s0 - 1)

calculateFactorial:					# This section is solely responsible for calculating the factorial of the user's number
mult $s0, $s3						# N(N-1) until N == 1
mflo $t1
add $s1, $0, $t1					# Add the product to our sum
add $s0, $0, $t1					# Set the first operand to the resulting product
sub $s3, $s3, 1						# Decrease the second operand by 1 N(N-1)
j beginLoop

Finished:
li $v0, 4
la $a0, factorialOutput
syscall

li $v0, 1
add $a0, $0, $s1
syscall

li $v0, 10
syscall

ZeroCase:
li $v0, 4
la $a0, factorialOutput
syscall

li $v0, 1
addi $a0, $0, 1
syscall

li $v0, 10
syscall
#-------------------------#
#          Errors         #
#-------------------------#
Error1:							# User's input is less than "0"
add $a0, $0, $s0
li $v0, 1
syscall

li $v0, 4
la $a0, badUserInputBLT
syscall

j getUserInput
#-------------------------#
Error2:							# User's input is greater than "10"
add $a0, $0, $s0
li $v0, 1
syscall

li $v0, 4
la $a0, badUserInputBGT
syscall

j getUserInput
#-------------------------#
