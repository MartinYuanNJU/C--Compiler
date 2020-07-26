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
addi $sp, $sp, -48
addi $t0, $fp, -16
li $t1, 0
lw $t2, -28($fp)
add $t2, $t0, $t1
sw $t2, -28($fp)
li $t0, 1
lw $t1, -28($fp)
sw $t0, 0($t1)
addi $t0, $fp, -16
li $t1, 4
lw $t2, -32($fp)
add $t2, $t0, $t1
sw $t2, -32($fp)
li $t0, 2
lw $t1, -32($fp)
sw $t0, 0($t1)
addi $t0, $fp, -24
li $t1, 0
lw $t2, -36($fp)
add $t2, $t0, $t1
sw $t2, -36($fp)
li $t0, 3
lw $t1, -36($fp)
sw $t0, 0($t1)
addi $t0, $fp, -24
li $t1, 4
lw $t2, -40($fp)
add $t2, $t0, $t1
sw $t2, -40($fp)
li $t0, 4
lw $t1, -40($fp)
sw $t0, 0($t1)
addi $t0, $fp, -24
li $t1, 0
lw $t2, -44($fp)
add $t2, $t0, $t1
sw $t2, -44($fp)
addi $t0, $fp, -16
li $t1, 4
lw $t2, -48($fp)
add $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -44($fp)
lw $t0, 0($t0)
lw $t1, -48($fp)
lw $t1, 0($t1)
lw $t2, -52($fp)
add $t2, $t0, $t1
sw $t2, -52($fp)
lw $t0, -52($fp)
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
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
