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

func_hanoi:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -40
lw $t0, 0($fp)
li $t1, 1
bne $t0, $t1, LABEL2
lw $t0, 4($fp)
li $t1, 1000000000
lw $t2, -12($fp)
mul $t2, $t0, $t1
sw $t2, -12($fp)
lw $t0, -12($fp)
lw $t1, 12($fp)
lw $t2, -16($fp)
add $t2, $t0, $t1
sw $t2, -16($fp)
lw $t0, -16($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
j LABEL3
LABEL2:
lw $t0, 0($fp)
li $t1, 1
lw $t2, -24($fp)
sub $t2, $t0, $t1
sw $t2, -24($fp)
addi $sp, $sp, -4
lw $t0, 8($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 12($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 4($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -24($fp)
sw $t0, 0($sp)
jal func_hanoi
lw $t0, -28($fp)
move $t0, $v0
sw $t0, -28($fp)
addi $sp, $sp, 16
lw $t0, 4($fp)
li $t1, 1000000000
lw $t2, -32($fp)
mul $t2, $t0, $t1
sw $t2, -32($fp)
lw $t0, -32($fp)
lw $t1, 12($fp)
lw $t2, -36($fp)
add $t2, $t0, $t1
sw $t2, -36($fp)
lw $t0, -36($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, 0($fp)
li $t1, 1
lw $t2, -44($fp)
sub $t2, $t0, $t1
sw $t2, -44($fp)
addi $sp, $sp, -4
lw $t0, 12($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 4($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, 8($fp)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -44($fp)
sw $t0, 0($sp)
jal func_hanoi
lw $t0, -48($fp)
move $t0, $v0
sw $t0, -48($fp)
addi $sp, $sp, 16
LABEL3:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra

main:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -12
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -12($fp)
move $t0, $v0
sw $t0, -12($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
addi $sp, $sp, -4
li $t0, 3
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 2
sw $t0, 0($sp)
addi $sp, $sp, -4
li $t0, 1
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -16($fp)
sw $t0, 0($sp)
jal func_hanoi
lw $t0, -20($fp)
move $t0, $v0
sw $t0, -20($fp)
addi $sp, $sp, 16
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
