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
addi $sp, $sp, -184
li $t0, 10
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 0
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
li $t0, 0
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
LABEL1:
lw $t0, -56($fp)
li $t1, 10
bge $t0, $t1, LABEL3
lw $t0, -56($fp)
li $t1, 4
lw $t2, -64($fp)
mul $t2, $t0, $t1
sw $t2, -64($fp)
addi $t0, $fp, -52
lw $t1, -64($fp)
lw $t2, -68($fp)
add $t2, $t0, $t1
sw $t2, -68($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -72($fp)
move $t0, $v0
sw $t0, -72($fp)
lw $t0, -72($fp)
lw $t1, -68($fp)
sw $t0, 0($t1)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -76($fp)
add $t2, $t0, $t1
sw $t2, -76($fp)
lw $t0, -76($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
j LABEL1
LABEL3:
li $t0, 5
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
LABEL4:
lw $t0, -80($fp)
li $t1, 0
blt $t0, $t1, LABEL6
li $t0, 0
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
lw $t0, -80($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
LABEL7:
lw $t0, -60($fp)
li $t1, 0
bne $t0, $t1, LABEL9
li $t0, 1
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
lw $t0, -56($fp)
li $t1, 2
lw $t2, -84($fp)
mul $t2, $t0, $t1
sw $t2, -84($fp)
lw $t0, -84($fp)
li $t1, 1
lw $t2, -88($fp)
add $t2, $t0, $t1
sw $t2, -88($fp)
lw $t0, -88($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
lw $t0, -56($fp)
li $t1, 2
lw $t2, -96($fp)
mul $t2, $t0, $t1
sw $t2, -96($fp)
lw $t0, -96($fp)
li $t1, 2
lw $t2, -100($fp)
add $t2, $t0, $t1
sw $t2, -100($fp)
lw $t0, -100($fp)
lw $t1, -104($fp)
move $t1, $t0
sw $t1, -104($fp)
lw $t0, -92($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL16
lw $t0, -92($fp)
li $t1, 4
lw $t2, -108($fp)
mul $t2, $t0, $t1
sw $t2, -108($fp)
addi $t0, $fp, -52
lw $t1, -108($fp)
lw $t2, -112($fp)
add $t2, $t0, $t1
sw $t2, -112($fp)
lw $t0, -112($fp)
lw $t0, 0($t0)
lw $t1, -116($fp)
move $t1, $t0
sw $t1, -116($fp)
lw $t0, -104($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL13
lw $t0, -104($fp)
li $t1, 4
lw $t2, -120($fp)
mul $t2, $t0, $t1
sw $t2, -120($fp)
addi $t0, $fp, -52
lw $t1, -120($fp)
lw $t2, -124($fp)
add $t2, $t0, $t1
sw $t2, -124($fp)
lw $t0, -92($fp)
li $t1, 4
lw $t2, -128($fp)
mul $t2, $t0, $t1
sw $t2, -128($fp)
addi $t0, $fp, -52
lw $t1, -128($fp)
lw $t2, -132($fp)
add $t2, $t0, $t1
sw $t2, -132($fp)
lw $t0, -124($fp)
lw $t0, 0($t0)
lw $t1, -132($fp)
lw $t1, 0($t1)
bge $t0, $t1, LABEL13
lw $t0, -104($fp)
li $t1, 4
lw $t2, -136($fp)
mul $t2, $t0, $t1
sw $t2, -136($fp)
addi $t0, $fp, -52
lw $t1, -136($fp)
lw $t2, -140($fp)
add $t2, $t0, $t1
sw $t2, -140($fp)
lw $t0, -140($fp)
lw $t0, 0($t0)
lw $t1, -116($fp)
move $t1, $t0
sw $t1, -116($fp)
lw $t0, -104($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
LABEL13:
lw $t0, -56($fp)
li $t1, 4
lw $t2, -144($fp)
mul $t2, $t0, $t1
sw $t2, -144($fp)
addi $t0, $fp, -52
lw $t1, -144($fp)
lw $t2, -148($fp)
add $t2, $t0, $t1
sw $t2, -148($fp)
lw $t0, -148($fp)
lw $t0, 0($t0)
lw $t1, -116($fp)
ble $t0, $t1, LABEL16
li $t0, 0
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
lw $t0, -92($fp)
li $t1, 4
lw $t2, -152($fp)
mul $t2, $t0, $t1
sw $t2, -152($fp)
addi $t0, $fp, -52
lw $t1, -152($fp)
lw $t2, -156($fp)
add $t2, $t0, $t1
sw $t2, -156($fp)
lw $t0, -56($fp)
li $t1, 4
lw $t2, -160($fp)
mul $t2, $t0, $t1
sw $t2, -160($fp)
addi $t0, $fp, -52
lw $t1, -160($fp)
lw $t2, -164($fp)
add $t2, $t0, $t1
sw $t2, -164($fp)
lw $t0, -164($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
sw $t0, 0($t1)
lw $t0, -56($fp)
li $t1, 4
lw $t2, -168($fp)
mul $t2, $t0, $t1
sw $t2, -168($fp)
addi $t0, $fp, -52
lw $t1, -168($fp)
lw $t2, -172($fp)
add $t2, $t0, $t1
sw $t2, -172($fp)
lw $t0, -116($fp)
lw $t1, -172($fp)
sw $t0, 0($t1)
lw $t0, -92($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
LABEL16:
j LABEL7
LABEL9:
lw $t0, -80($fp)
li $t1, 1
lw $t2, -176($fp)
sub $t2, $t0, $t1
sw $t2, -176($fp)
lw $t0, -176($fp)
lw $t1, -80($fp)
move $t1, $t0
sw $t1, -80($fp)
j LABEL4
LABEL6:
li $t0, 0
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
LABEL17:
lw $t0, -56($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL19
lw $t0, -56($fp)
li $t1, 4
lw $t2, -180($fp)
mul $t2, $t0, $t1
sw $t2, -180($fp)
addi $t0, $fp, -52
lw $t1, -180($fp)
lw $t2, -184($fp)
add $t2, $t0, $t1
sw $t2, -184($fp)
lw $t0, -184($fp)
lw $t0, 0($t0)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -188($fp)
move $t1, $t0
sw $t1, -188($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -192($fp)
add $t2, $t0, $t1
sw $t2, -192($fp)
lw $t0, -192($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
j LABEL17
LABEL19:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
