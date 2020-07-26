.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
li $v0, 4
la $a0, _prompt
syscall
li $v0, 5
syscall
jr $ra

write:
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
move $v0, $0
jr $ra

func_mod:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -20
lw $t0, 0($fp)
lw $t1, 4($fp)
lw $t2, -12($fp)
div $t2, $t0, $t1
sw $t2, -12($fp)
lw $t0, -12($fp)
lw $t1, 4($fp)
lw $t2, -16($fp)
mul $t2, $t0, $t1
sw $t2, -16($fp)
lw $t0, 0($fp)
lw $t1, -16($fp)
lw $t2, -20($fp)
sub $t2, $t0, $t1
sw $t2, -20($fp)
lw $t0, -20($fp)
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
lw $t0, -24($fp)
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
lw $ra, -4($fp)
move $sp, $fp
lw $t0, -24($fp)
lw $fp, -8($fp)
move $v0, $t0
jr $ra

func_power:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -52
li $t0, 1
lw $t1, 4($fp)
lw $t2, -12($fp)
add $t2, $t0, $t1
sw $t2, -12($fp)
lw $t0, -12($fp)
lw $t1, 4($fp)
lw $t2, -16($fp)
sub $t2, $t0, $t1
sw $t2, -16($fp)
lw $t0, -16($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
LABEL1:
lw $t0, -20($fp)
lw $t1, -20($fp)
lw $t2, -24($fp)
sub $t2, $t0, $t1
sw $t2, -24($fp)
lw $t0, -24($fp)
li $t1, 90
lw $t2, -28($fp)
add $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, -28($fp)
li $t1, 89
lw $t2, -32($fp)
sub $t2, $t0, $t1
sw $t2, -32($fp)
lw $t0, -32($fp)
li $t1, 1
lw $t2, -36($fp)
add $t2, $t0, $t1
sw $t2, -36($fp)
lw $t0, -36($fp)
li $t1, 2
lw $t2, -40($fp)
sub $t2, $t0, $t1
sw $t2, -40($fp)
lw $t0, 4($fp)
lw $t1, -40($fp)
ble $t0, $t1, LABEL3
lw $t0, -20($fp)
lw $t1, 0($fp)
lw $t2, -44($fp)
mul $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -44($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
li $t0, 2
lw $t1, 4($fp)
lw $t2, -48($fp)
mul $t2, $t0, $t1
sw $t2, -48($fp)
li $t0, 1
lw $t1, 4($fp)
lw $t2, -52($fp)
mul $t2, $t0, $t1
sw $t2, -52($fp)
lw $t0, -48($fp)
lw $t1, -52($fp)
lw $t2, -56($fp)
sub $t2, $t0, $t1
sw $t2, -56($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -60($fp)
sub $t2, $t0, $t1
sw $t2, -60($fp)
lw $t0, -60($fp)
lw $t1, 4($fp)
move $t1, $t0
sw $t1, 4($fp)
j LABEL1
LABEL3:
lw $ra, -4($fp)
move $sp, $fp
lw $t0, -20($fp)
lw $fp, -8($fp)
move $v0, $t0
jr $ra

func_getNumDigits:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -20
li $t0, 0
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, 0($fp)
li $t1, 0
bge $t0, $t1, LABEL5
lw $ra, -4($fp)
move $sp, $fp
li $t0, -1
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL5:
lw $t0, 0($fp)
li $t1, 0
ble $t0, $t1, LABEL8
lw $t0, 0($fp)
li $t1, 10
lw $t2, -16($fp)
div $t2, $t0, $t1
sw $t2, -16($fp)
lw $t0, -16($fp)
lw $t1, 0($fp)
move $t1, $t0
sw $t1, 0($fp)
lw $t0, -12($fp)
li $t1, 2
lw $t2, -20($fp)
add $t2, $t0, $t1
sw $t2, -20($fp)
lw $t0, -20($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -12($fp)
li $t1, 2
lw $t2, -24($fp)
add $t2, $t0, $t1
sw $t2, -24($fp)
lw $t0, -24($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -12($fp)
li $t1, 3
lw $t2, -28($fp)
sub $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, -28($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
j LABEL5
LABEL8:
lw $ra, -4($fp)
move $sp, $fp
lw $t0, -12($fp)
lw $fp, -8($fp)
move $v0, $t0
jr $ra

func_isNarcissistic:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -48
li $t0, 1
lw $t1, 0($fp)
lw $t2, -12($fp)
add $t2, $t0, $t1
sw $t2, -12($fp)
lw $t0, -12($fp)
li $t1, 1
lw $t2, -16($fp)
sub $t2, $t0, $t1
sw $t2, -16($fp)
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal func_getNumDigits
lw $t0, -20($fp)
move $t0, $v0
sw $t0, -20($fp)
addi $sp, $sp, 4
lw $t0, -20($fp)
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
li $t0, 0
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
lw $t0, 0($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL9:
lw $t0, -32($fp)
li $t1, 0
ble $t0, $t1, LABEL11
addi $sp, $sp, -4
li $t0, 10
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -32($fp)
sw $t0, 0($sp)
jal func_mod
lw $t0, -36($fp)
move $t0, $v0
sw $t0, -36($fp)
addi $sp, $sp, 8
lw $t0, -36($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -32($fp)
lw $t1, -40($fp)
lw $t2, -44($fp)
sub $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -44($fp)
li $t1, 10
lw $t2, -48($fp)
div $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -48($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
addi $sp, $sp, -4
lw $t0, -24($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -40($fp)
sw $t0, 0($sp)
jal func_power
lw $t0, -52($fp)
move $t0, $v0
sw $t0, -52($fp)
addi $sp, $sp, 8
lw $t0, -28($fp)
lw $t1, -52($fp)
lw $t2, -56($fp)
add $t2, $t0, $t1
sw $t2, -56($fp)
lw $t0, -56($fp)
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
j LABEL9
LABEL11:
lw $t0, -28($fp)
lw $t1, 0($fp)
bne $t0, $t1, LABEL13
lw $ra, -4($fp)
move $sp, $fp
li $t0, 1
lw $fp, -8($fp)
move $v0, $t0
jr $ra
j LABEL14
LABEL13:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL14:

main:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -28
li $t0, 0
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 300
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
LABEL15:
lw $t0, -16($fp)
li $t1, 500
bge $t0, $t1, LABEL17
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal func_isNarcissistic
lw $t0, -20($fp)
move $t0, $v0
sw $t0, -20($fp)
addi $sp, $sp, 4
lw $t0, -20($fp)
li $t1, 1
bne $t0, $t1, LABEL19
lw $t0, -16($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
lw $t0, -12($fp)
li $t1, 1
lw $t2, -28($fp)
add $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, -28($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
LABEL19:
lw $t0, -16($fp)
li $t1, 1
lw $t2, -32($fp)
add $t2, $t0, $t1
sw $t2, -32($fp)
lw $t0, -32($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
j LABEL15
LABEL17:
lw $t0, -12($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -36($fp)
move $t1, $t0
sw $t1, -36($fp)
lw $ra, -4($fp)
move $sp, $fp
lw $t0, -12($fp)
lw $fp, -8($fp)
move $v0, $t0
jr $ra
