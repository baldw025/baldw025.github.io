#Program Description:	This program program is written to mimic a *very* basic addition-subtraction-multiplication-division calculator. 
# 			We're just brushing the surface here.
#Author:		DeAndre Baldwin
#Creation Date:		31/01/2019

.data
####--For outputting numerical calculations--####
str1: .asciiz "\nPlease input two numbers:\n"
str2: .asciiz "\nThe sum is: "
str3: .asciiz "\nThe difference is: "
str4: .asciiz "\nThe product is: "
str5: .asciiz "\nThe quotient is: "
str6: .asciiz "\nThe remainder is: "

####--For outputting program header information--####
hdr1: .asciiz "=========================================================================================================="
hdr2: .asciiz "\nProgram Description:	This program program is written to mimic a very basic calculator (Two User Inputs)"
hdr3: .asciiz "\n\nAuthor:			DeAndre Baldwin"
hdr4: .asciiz "\n\nCreation Date:		"
hdr5: .asciiz "/" #A little slashy boi
hdr6: .asciiz "\n========================================================================================================="
.text

main:
li $v0, 4	# Service Code 4 to print hdr1
la $a0, hdr1	# Load address of hdr1 into register a0
syscall		# To print the first header string

la $a0, hdr2	# Load address of hdr2 into register a0
syscall		# To print the second header string

la $a0, hdr3	# Load address of hdr3 into register a0
syscall		# To print the third header string

la $a0, hdr4	# Load address of hdr4 into register a0
syscall		# To print the fourth header string

li $v0, 1 	# Service Code 1 to print integer
li $a0, 31 	# Store today's day into $a0
syscall

li $v0, 4	# Service Code 4 to print hdr1
la $a0, hdr5	# Load address of hdr5 into register a0
syscall		# To print the fifth header string

li $v0, 1 	# Service Code 1 to print integer
li $a0, 01 	# Store today's month into $a0
syscall

li $v0, 4	# Service Code 4 to print hdr5
la $a0, hdr5	# Load address of hdr5 into register a0
syscall	

li $v0, 1 	# Service Code 1 to print integer
li $a0, 2019 	# Store the current year into $a0
syscall

li $v0, 4	# Service Code 4 to print hdr6
la $a0, hdr6	# Load address of hdr6 into register a0
syscall		# To print the sixth header string

la $a0, str1	# Load address of hdr6 into register a0
syscall		# To print the first string
	
####--This Section Gets and Stores Input from the User--####
li $v0,5 	 # Service Code 5 to read/get the first integer from the user and store it into $v0
syscall 

add $s0, $0, $v0 # Store first integer ($v0) into register ($s0)
add $a0, $s0, $0 # Store $s0 into $a0

li $v0,5
syscall

add $s1, $0, $v0 # Store second integer ($v0) into register ($s1)
add $a1, $s1, $0 # Store $s1 into $a1

####--This Section Conducts All Addition Operations--####
li $v0, 4	# Service Code 4 to print str2
la $a0, str2	# Load address of str2 into register a0
syscall		# To print the first string (Sum)

add $s2, $s0, $s1 # Adds $s0 and $s1 and stores the result in $s2
add $a0, $s2, $0  # Store $22 into $a0
li $v0,1 	  # Outputs the sum of $s0 + $s1
syscall

####--This Section Conducts All Subtraction Operations--####
li $v0, 4	# Service Code 4 to print str3
la $a0, str3	# Load address of str3 into register a0
syscall		# To print the first string (Difference)

sub $s2, $s0, $s1 # Adds $s0 and $s1 and stores the result in $s2
add $a0, $s2, $0  # Store $s2 into $a0
li $v0, 1 	# Outputs the sum of $s0 + $s1
syscall

####--This Section Conducts All Multiplication Operations--####
li $v0, 4	# Service Code 4 to print str4
la $a0, str4	# Load address of str4 into register a0
syscall		# To print the first string (Product)

mult $s0, $s1 # Multiplies $s0 and $s1
mfhi $t0 # Moves data from hi to $t0
mflo $t1 # Moves data from lo to $t1
add $a0, $t1, $t0
li $v0, 1
syscall

####--This Section Conducts All Division Operations--####
li $v0, 4	# Service Code 4 to print str5
la $a0, str5	# Load address of str5 into register a0
syscall		# To print the first string (Quotient)

div $s0, $s1	# Divides $s0 and $s1
mfhi $t0	# Move data from hi (remainder) to $t0
mflo $t1	# Move data from lo (quotient) to $t1
li $v0, 1	# Outputs the remaind of $s0 / $s2
add $a0, $t1, $0 # Stores the value of $t1 to $a0
syscall		# Outputs the remaind of $s0 / $s2

li $v0, 4	# Service Code 4 to print str6
la $a0, str6	# Load address of str6 into register a0
syscall		# To print the first string (Remainder)

li $v0, 1
add $a0, $t0, $0
syscall
