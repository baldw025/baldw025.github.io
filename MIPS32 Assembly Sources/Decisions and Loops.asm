#Program Description:	This program program is written to calculate the sum of all numbers divisbible by 6 and 1 <= x <= 100 based on user-input. 
#			Loop inputs can only be 1 <= x <= 20. Numbers to add to sum can only be 1 <= x <= 100. Numbers to sum up must be divisble by 6.
#Author:		DeAndre Baldwin
#Creation Date:		07/02/2019

.data 
userLoopInput: .asciiz "\nHow many positive numbers, divisible by 6, do you want to add?: "
userNumberInput: .asciiz "\nEnter a number: "
numberIsDivisble: .asciiz " is divisible by 6."
mainErrorString: .asciiz "(!)ERROR: "
error1.1String: .asciiz " is less than 1. Enter another number."
error2String: .asciiz " is less than 1. Enter another number."
error3String: .asciiz " is greater than 20. Enter another number."
error4String: .asciiz " is greater than 100. Enter another number."
error5String: .asciiz " is not divisble by 6. Enter another number."
sumString: .asciiz "\nThe Sum of the positive numbers between 1 and 100 that are devisable by 6, is: "
.text
#-------------------------#
#	 Registers	  #
#-------------------------#
# $s0 - Iterator	  #
# $s1 - User Loop Length  #
# $s2 - User Number Input #
# $s3 - Sum		  #
# $t0 - Comparer	  #	
# $t1 - Remainder	  #
#-------------------------#
getLoopInput: 
li $v0, 4
la $a0, userLoopInput
syscall 

li $v0, 5
syscall 

li $s0, 0						# Initialize our iterator register to 0
add $s1, $0, $v0					# Store our user's input
li $t0, 1						# Store 1 into a comparing register to see if user's input is valid
blt $s1, $t0, Error1					# If the user's loop input is less than "1", goto "Error2
li $t0, 20						# Store 20 into a comparing register to see if the user's input is valid
bgt $s1, $t0, Error3					# If the user's loop input is greater than "20", goto "Error3"

getUserNumberInput:
beq $s0, $s1, Done					# Condition that checks how many successful loops completed (in respect to user-input)
li $v0, 4
la $a0, userNumberInput
syscall

li $v0, 5
syscall

add $s2, $0, $v0
li $t0, 1
blt $s2, $t0, Error2
li $t0, 100
bgt $s2, $t0, Error4
li $t0, 6						# Lines 57 - 60 check if the user's number input is divisble by 6
div $s2, $t0						# If false, Error5 is called and we jump back to Line 43.	
mfhi $t1
beq $t1, 0, Divisble
j Error5

Divisble:
add $a0, $0, $s2
li $v0, 1
syscall

li $v0, 4
la $a0, numberIsDivisble
syscall

add $s3, $s2, $s3					# Keeps track of total sum of user-input numbers divisble by 6
addi $s0, $s0, 1					# Increments our iterator by "1" upon a successful numerical user-input.
j getUserNumberInput

Done:
li $v0, 4
la $a0, sumString
syscall

add $a0, $0, $s3
li $v0, 1
syscall

li $v0, 10
syscall


#-----------Errors-----------#
Error1:							# The user's number to check if divisble by 6 is less than 1
li $v0, 4
la $a0, mainErrorString
syscall

add $a0, $0, $s1
li $v0, 1
syscall

li $v0, 4
la $a0, error2String
syscall

j getLoopInput

Error2:							# The user's loop count is less than 1
li $v0, 4
la $a0, mainErrorString
syscall

add $a0, $0, $s2
li $v0, 1
syscall

li $v0, 4
la $a0, error1.1String
syscall

j getUserNumberInput
#----------------------------#
Error3:							# The user's loop count is greater than 20
li $v0, 4
la $a0, mainErrorString
syscall

add $a0, $0, $s1
li $v0, 1
syscall

li $v0, 4
la $a0, error3String
syscall

j getLoopInput
#----------------------------#
Error4:							# The user's number to add to sum is greater than 100
add $a0, $0, $s1
li $v0, 1
syscall

li $v0, 4
la $a0, error4String
syscall

j getUserNumberInput
#----------------------------#
Error5:							# The user's number is not divisble by 6
add $a0, $0, $s2
li $v0, 1
syscall

li $v0, 4
la $a0, error5String
syscall 

j getUserNumberInput
#----------------------------#