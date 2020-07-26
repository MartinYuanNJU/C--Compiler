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

func_isStudentInClass:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -48
li $t0, 0
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
LABEL1:
lw $t0, -12($fp)
li $t1, 10
bge $t0, $t1, LABEL3
lw $t0, 0($fp)
li $t1, 0
lw $t2, -16($fp)
add $t2, $t0, $t1
sw $t2, -16($fp)
lw $t0, -16($fp)
li $t1, 0
lw $t2, -20($fp)
add $t2, $t0, $t1
sw $t2, -20($fp)
lw $t0, -12($fp)
li $t1, 4
lw $t2, -24($fp)
mul $t2, $t0, $t1
sw $t2, -24($fp)
lw $t0, -20($fp)
lw $t1, -24($fp)
lw $t2, -28($fp)
add $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, 4($fp)
li $t1, 0
lw $t2, -32($fp)
add $t2, $t0, $t1
sw $t2, -32($fp)
lw $t0, -32($fp)
li $t1, 0
lw $t2, -36($fp)
add $t2, $t0, $t1
sw $t2, -36($fp)
lw $t0, -28($fp)
lw $t0, 0($t0)
lw $t1, -36($fp)
lw $t1, 0($t1)
bne $t0, $t1, LABEL5
lw $t0, 0($fp)
li $t1, 0
lw $t2, -40($fp)
add $t2, $t0, $t1
sw $t2, -40($fp)
lw $t0, -40($fp)
li $t1, 40
lw $t2, -44($fp)
add $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -12($fp)
li $t1, 4
lw $t2, -48($fp)
mul $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -44($fp)
lw $t1, -48($fp)
lw $t2, -52($fp)
add $t2, $t0, $t1
sw $t2, -52($fp)
lw $ra, -4($fp)
move $sp, $fp
lw $t0, -52($fp)
lw $t0, 0($t0)
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL5:
lw $t0, -12($fp)
li $t1, 1
lw $t2, -56($fp)
add $t2, $t0, $t1
sw $t2, -56($fp)
lw $t0, -56($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
j LABEL1
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
addi $sp, $sp, -240
li $t0, 0
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
addi $t0, $fp, -176
li $t1, 0
lw $t2, -180($fp)
add $t2, $t0, $t1
sw $t2, -180($fp)
lw $t0, -180($fp)
li $t1, 0
lw $t2, -184($fp)
add $t2, $t0, $t1
sw $t2, -184($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -188($fp)
move $t0, $v0
sw $t0, -188($fp)
lw $t0, -188($fp)
lw $t1, -184($fp)
sw $t0, 0($t1)
addi $t0, $fp, -176
li $t1, 40
lw $t2, -192($fp)
add $t2, $t0, $t1
sw $t2, -192($fp)
lw $t0, -192($fp)
li $t1, 0
lw $t2, -196($fp)
add $t2, $t0, $t1
sw $t2, -196($fp)
li $t0, 0
lw $t1, -196($fp)
sw $t0, 0($t1)
addi $t0, $fp, -92
li $t1, 80
lw $t2, -200($fp)
add $t2, $t0, $t1
sw $t2, -200($fp)
li $t0, 0
lw $t1, -200($fp)
sw $t0, 0($t1)
LABEL6:
lw $t0, -96($fp)
li $t1, 10
bge $t0, $t1, LABEL8
addi $t0, $fp, -92
li $t1, 0
lw $t2, -204($fp)
add $t2, $t0, $t1
sw $t2, -204($fp)
lw $t0, -204($fp)
li $t1, 0
lw $t2, -208($fp)
add $t2, $t0, $t1
sw $t2, -208($fp)
lw $t0, -96($fp)
li $t1, 4
lw $t2, -212($fp)
mul $t2, $t0, $t1
sw $t2, -212($fp)
lw $t0, -208($fp)
lw $t1, -212($fp)
lw $t2, -216($fp)
add $t2, $t0, $t1
sw $t2, -216($fp)
lw $t0, -96($fp)
lw $t1, -216($fp)
sw $t0, 0($t1)
addi $t0, $fp, -92
li $t1, 0
lw $t2, -220($fp)
add $t2, $t0, $t1
sw $t2, -220($fp)
lw $t0, -220($fp)
li $t1, 40
lw $t2, -224($fp)
add $t2, $t0, $t1
sw $t2, -224($fp)
lw $t0, -96($fp)
li $t1, 4
lw $t2, -228($fp)
mul $t2, $t0, $t1
sw $t2, -228($fp)
lw $t0, -224($fp)
lw $t1, -228($fp)
lw $t2, -232($fp)
add $t2, $t0, $t1
sw $t2, -232($fp)
lw $t0, -96($fp)
lw $t1, -96($fp)
lw $t2, -236($fp)
mul $t2, $t0, $t1
sw $t2, -236($fp)
lw $t0, -236($fp)
lw $t1, -232($fp)
sw $t0, 0($t1)
lw $t0, -96($fp)
li $t1, 1
lw $t2, -240($fp)
add $t2, $t0, $t1
sw $t2, -240($fp)
lw $t0, -240($fp)
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
j LABEL6
LABEL8:
addi $sp, $sp, -4
addi $t0, $fp, -176
sw $t0, 0($sp)
addi $sp, $sp, -4
addi $t0, $fp, -92
sw $t0, 0($sp)
jal func_isStudentInClass
lw $t0, -244($fp)
move $t0, $v0
sw $t0, -244($fp)
addi $sp, $sp, 8
lw $t0, -244($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -248($fp)
move $t1, $t0
sw $t1, -248($fp)
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
