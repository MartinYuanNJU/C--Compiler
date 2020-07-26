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

func_compare:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, 0
lw $t0, 0($fp)
lw $t1, 4($fp)
ble $t0, $t1, LABEL2
lw $ra, -4($fp)
move $sp, $fp
lw $t0, 0($fp)
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL2:
lw $t0, 0($fp)
lw $t1, 4($fp)
bge $t0, $t1, LABEL4
lw $ra, -4($fp)
move $sp, $fp
lw $t0, 4($fp)
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL4:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra

func_add:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -4
lw $t0, 0($fp)
lw $t1, 4($fp)
lw $t2, -12($fp)
add $t2, $t0, $t1
sw $t2, -12($fp)
lw $ra, -4($fp)
move $sp, $fp
lw $t0, -12($fp)
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
addi $sp, $sp, -168
li $t0, 0
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
LABEL5:
lw $t0, -72($fp)
li $t1, 10
bge $t0, $t1, LABEL7
lw $t0, -72($fp)
li $t1, 4
lw $t2, -76($fp)
mul $t2, $t0, $t1
sw $t2, -76($fp)
addi $t0, $fp, -48
lw $t1, -76($fp)
lw $t2, -80($fp)
add $t2, $t0, $t1
sw $t2, -80($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -84($fp)
move $t0, $v0
sw $t0, -84($fp)
lw $t0, -84($fp)
lw $t1, -80($fp)
sw $t0, 0($t1)
lw $t0, -72($fp)
li $t1, 1
lw $t2, -88($fp)
add $t2, $t0, $t1
sw $t2, -88($fp)
lw $t0, -88($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
j LABEL5
LABEL7:
li $t0, 0
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
li $t0, 0
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
LABEL8:
lw $t0, -72($fp)
li $t1, 10
bge $t0, $t1, LABEL10
lw $t0, -92($fp)
li $t1, 4
lw $t2, -96($fp)
mul $t2, $t0, $t1
sw $t2, -96($fp)
addi $t0, $fp, -68
lw $t1, -96($fp)
lw $t2, -100($fp)
add $t2, $t0, $t1
sw $t2, -100($fp)
lw $t0, -72($fp)
li $t1, 4
lw $t2, -104($fp)
mul $t2, $t0, $t1
sw $t2, -104($fp)
addi $t0, $fp, -48
lw $t1, -104($fp)
lw $t2, -108($fp)
add $t2, $t0, $t1
sw $t2, -108($fp)
lw $t0, -72($fp)
li $t1, 1
lw $t2, -112($fp)
add $t2, $t0, $t1
sw $t2, -112($fp)
lw $t0, -112($fp)
li $t1, 4
lw $t2, -116($fp)
mul $t2, $t0, $t1
sw $t2, -116($fp)
addi $t0, $fp, -48
lw $t1, -116($fp)
lw $t2, -120($fp)
add $t2, $t0, $t1
sw $t2, -120($fp)
addi $sp, $sp, -4
lw $t0, -120($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -108($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
jal func_compare
lw $t0, -124($fp)
move $t0, $v0
sw $t0, -124($fp)
addi $sp, $sp, 8
lw $t0, -124($fp)
lw $t1, -100($fp)
sw $t0, 0($t1)
lw $t0, -72($fp)
li $t1, 2
lw $t2, -128($fp)
add $t2, $t0, $t1
sw $t2, -128($fp)
lw $t0, -128($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
lw $t0, -92($fp)
li $t1, 1
lw $t2, -132($fp)
add $t2, $t0, $t1
sw $t2, -132($fp)
lw $t0, -132($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
j LABEL8
LABEL10:
li $t0, 0
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
LABEL11:
lw $t0, -72($fp)
li $t1, 5
bge $t0, $t1, LABEL13
lw $t0, -72($fp)
li $t1, 4
lw $t2, -136($fp)
mul $t2, $t0, $t1
sw $t2, -136($fp)
addi $t0, $fp, -68
lw $t1, -136($fp)
lw $t2, -140($fp)
add $t2, $t0, $t1
sw $t2, -140($fp)
lw $t0, -72($fp)
li $t1, 4
lw $t2, -144($fp)
mul $t2, $t0, $t1
sw $t2, -144($fp)
addi $t0, $fp, -68
lw $t1, -144($fp)
lw $t2, -148($fp)
add $t2, $t0, $t1
sw $t2, -148($fp)
lw $t0, -72($fp)
li $t1, 4
lw $t2, -152($fp)
mul $t2, $t0, $t1
sw $t2, -152($fp)
addi $t0, $fp, -48
lw $t1, -152($fp)
lw $t2, -156($fp)
add $t2, $t0, $t1
sw $t2, -156($fp)
addi $sp, $sp, -4
lw $t0, -156($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
addi $sp, $sp, -4
lw $t0, -148($fp)
lw $t0, 0($t0)
sw $t0, 0($sp)
jal func_add
lw $t0, -160($fp)
move $t0, $v0
sw $t0, -160($fp)
addi $sp, $sp, 8
lw $t0, -160($fp)
lw $t1, -140($fp)
sw $t0, 0($t1)
lw $t0, -72($fp)
li $t1, 4
lw $t2, -164($fp)
mul $t2, $t0, $t1
sw $t2, -164($fp)
addi $t0, $fp, -68
lw $t1, -164($fp)
lw $t2, -168($fp)
add $t2, $t0, $t1
sw $t2, -168($fp)
lw $t0, -168($fp)
lw $t0, 0($t0)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -172($fp)
move $t1, $t0
sw $t1, -172($fp)
lw $t0, -72($fp)
li $t1, 1
lw $t2, -176($fp)
add $t2, $t0, $t1
sw $t2, -176($fp)
lw $t0, -176($fp)
lw $t1, -72($fp)
move $t1, $t0
sw $t1, -72($fp)
j LABEL11
LABEL13:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
