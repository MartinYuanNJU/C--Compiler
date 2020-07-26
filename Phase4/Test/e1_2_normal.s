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
addi $sp, $sp, -280
li $t0, 0
lw $t1, -172($fp)
move $t1, $t0
sw $t1, -172($fp)
li $t0, 12
lw $t1, -176($fp)
move $t1, $t0
sw $t1, -176($fp)
li $t0, 0
lw $t1, -180($fp)
move $t1, $t0
sw $t1, -180($fp)
LABEL1:
lw $t0, -172($fp)
li $t1, 5
bge $t0, $t1, LABEL3
addi $t0, $fp, -88
li $t1, 0
lw $t2, -184($fp)
add $t2, $t0, $t1
sw $t2, -184($fp)
lw $t0, -172($fp)
li $t1, 4
lw $t2, -188($fp)
mul $t2, $t0, $t1
sw $t2, -188($fp)
lw $t0, -184($fp)
lw $t1, -188($fp)
lw $t2, -192($fp)
add $t2, $t0, $t1
sw $t2, -192($fp)
lw $t0, -176($fp)
lw $t1, -192($fp)
sw $t0, 0($t1)
addi $t0, $fp, -88
li $t1, 40
lw $t2, -196($fp)
add $t2, $t0, $t1
sw $t2, -196($fp)
lw $t0, -172($fp)
li $t1, 4
lw $t2, -200($fp)
mul $t2, $t0, $t1
sw $t2, -200($fp)
lw $t0, -196($fp)
lw $t1, -200($fp)
lw $t2, -204($fp)
add $t2, $t0, $t1
sw $t2, -204($fp)
lw $t0, -176($fp)
lw $t1, -176($fp)
lw $t2, -208($fp)
mul $t2, $t0, $t1
sw $t2, -208($fp)
lw $t0, -208($fp)
lw $t1, -204($fp)
sw $t0, 0($t1)
lw $t0, -176($fp)
li $t1, 1
lw $t2, -212($fp)
sub $t2, $t0, $t1
sw $t2, -212($fp)
lw $t0, -212($fp)
lw $t1, -176($fp)
move $t1, $t0
sw $t1, -176($fp)
addi $t0, $fp, -168
li $t1, 0
lw $t2, -216($fp)
add $t2, $t0, $t1
sw $t2, -216($fp)
lw $t0, -172($fp)
li $t1, 4
lw $t2, -220($fp)
mul $t2, $t0, $t1
sw $t2, -220($fp)
lw $t0, -216($fp)
lw $t1, -220($fp)
lw $t2, -224($fp)
add $t2, $t0, $t1
sw $t2, -224($fp)
lw $t0, -176($fp)
lw $t1, -224($fp)
sw $t0, 0($t1)
addi $t0, $fp, -168
li $t1, 40
lw $t2, -228($fp)
add $t2, $t0, $t1
sw $t2, -228($fp)
lw $t0, -172($fp)
li $t1, 4
lw $t2, -232($fp)
mul $t2, $t0, $t1
sw $t2, -232($fp)
lw $t0, -228($fp)
lw $t1, -232($fp)
lw $t2, -236($fp)
add $t2, $t0, $t1
sw $t2, -236($fp)
lw $t0, -176($fp)
li $t1, 3
lw $t2, -240($fp)
div $t2, $t0, $t1
sw $t2, -240($fp)
lw $t0, -240($fp)
lw $t1, -236($fp)
sw $t0, 0($t1)
lw $t0, -172($fp)
li $t1, 1
lw $t2, -244($fp)
add $t2, $t0, $t1
sw $t2, -244($fp)
lw $t0, -244($fp)
lw $t1, -172($fp)
move $t1, $t0
sw $t1, -172($fp)
j LABEL1
LABEL3:
li $t0, 0
lw $t1, -172($fp)
move $t1, $t0
sw $t1, -172($fp)
LABEL4:
lw $t0, -172($fp)
li $t1, 5
bge $t0, $t1, LABEL6
addi $t0, $fp, -88
li $t1, 0
lw $t2, -248($fp)
add $t2, $t0, $t1
sw $t2, -248($fp)
lw $t0, -172($fp)
li $t1, 4
lw $t2, -252($fp)
mul $t2, $t0, $t1
sw $t2, -252($fp)
lw $t0, -248($fp)
lw $t1, -252($fp)
lw $t2, -256($fp)
add $t2, $t0, $t1
sw $t2, -256($fp)
li $t0, 4
lw $t1, -172($fp)
lw $t2, -260($fp)
sub $t2, $t0, $t1
sw $t2, -260($fp)
addi $t0, $fp, -168
li $t1, 40
lw $t2, -264($fp)
add $t2, $t0, $t1
sw $t2, -264($fp)
lw $t0, -260($fp)
li $t1, 4
lw $t2, -268($fp)
mul $t2, $t0, $t1
sw $t2, -268($fp)
lw $t0, -264($fp)
lw $t1, -268($fp)
lw $t2, -272($fp)
add $t2, $t0, $t1
sw $t2, -272($fp)
lw $t0, -256($fp)
lw $t0, 0($t0)
lw $t1, -272($fp)
lw $t1, 0($t1)
lw $t2, -276($fp)
mul $t2, $t0, $t1
sw $t2, -276($fp)
lw $t0, -180($fp)
lw $t1, -276($fp)
lw $t2, -280($fp)
add $t2, $t0, $t1
sw $t2, -280($fp)
lw $t0, -280($fp)
lw $t1, -180($fp)
move $t1, $t0
sw $t1, -180($fp)
lw $t0, -172($fp)
li $t1, 1
lw $t2, -284($fp)
add $t2, $t0, $t1
sw $t2, -284($fp)
lw $t0, -284($fp)
lw $t1, -172($fp)
move $t1, $t0
sw $t1, -172($fp)
j LABEL4
LABEL6:
lw $t0, -180($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -288($fp)
move $t1, $t0
sw $t1, -288($fp)
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
