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
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -20($fp)
move $t0, $v0
sw $t0, -20($fp)
lw $t0, -20($fp)
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
lw $t0, -16($fp)
lw $t1, -24($fp)
ble $t0, $t1, LABEL2
lw $t0, -24($fp)
li $t1, 2
lw $t2, -28($fp)
mul $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, -16($fp)
lw $t1, -28($fp)
ble $t0, $t1, LABEL5
lw $t0, -16($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
j LABEL6
LABEL5:
lw $t0, -24($fp)
li $t1, 2
lw $t2, -36($fp)
mul $t2, $t0, $t1
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
LABEL6:
j LABEL15
LABEL2:
lw $t0, -16($fp)
lw $t1, -24($fp)
bne $t0, $t1, LABEL8
lw $t0, -24($fp)
li $t1, 100
ble $t0, $t1, LABEL11
li $t0, 100
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -44($fp)
move $t1, $t0
sw $t1, -44($fp)
j LABEL12
LABEL11:
lw $t0, -24($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -48($fp)
move $t1, $t0
sw $t1, -48($fp)
LABEL12:
j LABEL15
LABEL8:
lw $t0, -16($fp)
li $t1, 2
lw $t2, -52($fp)
mul $t2, $t0, $t1
sw $t2, -52($fp)
lw $t0, -52($fp)
lw $t1, -24($fp)
bge $t0, $t1, LABEL14
lw $t0, -24($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
j LABEL15
LABEL14:
lw $t0, -16($fp)
li $t1, 2
lw $t2, -60($fp)
mul $t2, $t0, $t1
sw $t2, -60($fp)
lw $t0, -60($fp)
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
LABEL15:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
