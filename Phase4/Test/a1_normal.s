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
addi $sp, $sp, -36
li $t0, 12
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 4
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
li $t0, 5
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
li $t0, 48
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
li $t0, 49
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
li $t0, 244
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
li $t0, 244
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
li $t0, 946
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
li $t0, 1043
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
li $t0, 946
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
li $t0, 1043
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
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
