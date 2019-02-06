#Program Description:	This program program is written to calculate the sum of all even numbers entered from user-input. 
#			All odd numbers will be disregarded in this program.
#Author:		DeAndre Baldwin
#Creation Date:		05/02/2019

.data
str1: .asciiz "How many even numbers would you like to add together?: "
str2: .asciiz "\nThe sum of your numbers is: "
str3: .asciiz "Enter an even number: "
.text
#-----------------------------------------------------------------------------------#
# $s0 = Iterator Counter (Initializes at 0 : C equivalent of "i" iterator for loops)
# $s1 = User's-Defined "Loop Length"
# $s2 = The current sum/total of all input numbers
#-----------------------------------------------------------------------------------#

li $v0, 4
la $a0, str1
syscall					# Asks the user how many numbers they would like to enter (loopCount)

li $v0, 5
syscall					# Reads the user's input from previous syscall and stores it into $v0

add $s1, $0, $v0			# Moves the user's input from $v0 to $s1. ($0 + $v0 = $s1)
li $s0, 0				# Initalize $s0 to 0. This is our iterator/loop counter (i).

Loop:
beq $s0, $s1, Done			# When $s0 == $s1, goto "Done" label which will display the sum of all even numbers and cleanly exit the program
li $v0, 4
la $a0, str3
syscall					# Tells the user to input an even number

li $v0, 5
syscall					# Gets the user's number input

add $s3, $v0, $0			# Move the user's input from $v0 to $s3
li $t0, 2				# $t0 will be used as a divisor to see if a number is even or odd
div $s3, $t0
mfhi $t1				# Store the remainder of the above division operation so we can test and identify if the dividend is even or odd

beq $t1, 0, Even  			#If the remainder of the user's number divided by 2 is 0, jump to "Even" label.
j Loop					#Keep jumping to the "Loop" label until the "beq" condition becomes True.

Even:
add $s2, $v0, $s2			# Since the user's number is even, add it to the current sum of all the user's even numbers
addi $s0, $s0, 1			# Increments our iterator $s0 by 1 each time an even number is accounted for
j Loop					# We don't care for odd numbered inputs, so an "Odd" label is not needed and can be discarded

Done:
li $v0, 4
la, $a0, str2
syscall

add $a0, $0, $s2
li $v0, 1
syscall					# Outputs the sum of all even numbers the user provided (All odd numbers are disregarded)

li $v0, 10
syscall					# Cleanly exits the program when program is finished with all required routines