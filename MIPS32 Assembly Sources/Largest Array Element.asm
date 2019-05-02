#----------------------------------------------------------------------------------------------------------------------------------------
#Program Description:	This program program is written to calculate the largest element in a user-generated array
#Author:		DeAndre Baldwin
#----------------------------------------------------------------------------------------------------------------------------------------
.data
userArray: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
getUserArraySizeString: .asciiz "Please enter an array size (must be positive and less than or equal to 10): "
userArraySizeErrorString: .asciiz  "Error: Invalid Input. Array size must be positive and less than or equal to 10.\n"
getInputFillArrayString: .asciiz "Input a number: "
outputLargestElementString: .asciiz "The largest element in your array is: "
.text
#-------------------------#
#        Registers        #
#-------------------------#
# $s0 - Array Address     #
# $s1 - Array Size        #
# $s2 - Largest Element   #
# $t0 - Counter	          #
#-------------------------#
getUserArraySize:
li $v0, 4
la $a0, getUserArraySizeString
syscall

li $v0, 5
syscall

checkArraySize:
add $s1, $0, $v0
addi $t1, $0, 10
ble $s1, $0, userArraySizeError
bgt $s1, $t1, userArraySizeError
addi $t0, $0, 0
la $s0, userArray

fillArray:
beq $t0, $s1, findLargestElement
li $v0, 4
la $a0, getInputFillArrayString
syscall

li $v0, 5
syscall

sw $v0, 0($s0)
addi $t0, $t0, 1
addi $s0, $s0, 4
j fillArray

findLargestElement:
la $s0, userArray
addi $t0, $0, 0
add $s2, $0, $ 
lw $t1, 0($s0)
add $s2, $0, $t1

compare:
beq $t0, $s1, outputLargestElement
bgt $t1, $s2, greater
lw $t1, 4($s0)
addi $s0, $s0, 4
addi $t0, $t0, 1
j compare

greater:
add $s2, $0, $t1
j compare

outputLargestElement:
li $v0, 4
la $a0, outputLargestElementString
syscall

add $a0, $0, $s2
li $v0, 1
syscall

li $v0, 10
syscall

#-------------------------#
#          Errors         #
#-------------------------#
userArraySizeError:
li $v0, 4
la $a0, userArraySizeErrorString
syscall

j getUserArraySize
