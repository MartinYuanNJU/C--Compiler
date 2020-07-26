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

main:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -56
li $t0, 0
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -16($fp)
move $t0, $v0
sw $t0, -16($fp)
lw $t0, -16($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -24($fp)
move $t0, $v0
sw $t0, -24($fp)
lw $t0, -24($fp)
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
lw $t0, -20($fp)
lw $t1, -28($fp)
ble $t0, $t1, LABEL2
lw $t0, -20($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
j LABEL3
LABEL2:
lw $t0, -28($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL3:
lw $t0, -12($fp)
li $t1, 0
bne $t0, $t1, LABEL6
lw $t0, -32($fp)
lw $t1, -20($fp)
lw $t2, -36($fp)
div $t2, $t0, $t1
sw $t2, -36($fp)
lw $t0, -36($fp)
lw $t1, -20($fp)
lw $t2, -40($fp)
mul $t2, $t0, $t1
sw $t2, -40($fp)
lw $t0, -32($fp)
lw $t1, -40($fp)
bne $t0, $t1, LABEL8
lw $t0, -32($fp)
lw $t1, -28($fp)
lw $t2, -44($fp)
div $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -44($fp)
lw $t1, -28($fp)
lw $t2, -48($fp)
mul $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -32($fp)
lw $t1, -48($fp)
bne $t0, $t1, LABEL11
lw $t0, -32($fp)
lw $t1, -52($fp)
move $t1, $t0
sw $t1, -52($fp)
li $t0, 1
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
j LABEL12
LABEL11:
lw $t0, -32($fp)
li $t1, 1
lw $t2, -56($fp)
add $t2, $t0, $t1
sw $t2, -56($fp)
lw $t0, -56($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL12:
j LABEL9
LABEL8:
lw $t0, -32($fp)
li $t1, 1
lw $t2, -60($fp)
add $t2, $t0, $t1
sw $t2, -60($fp)
lw $t0, -60($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL9:
j LABEL3
LABEL6:
lw $t0, -52($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -64($fp)
move $t1, $t0
sw $t1, -64($fp)
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
