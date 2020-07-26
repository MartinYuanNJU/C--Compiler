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
addi $sp, $sp, -136
li $t0, 0
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL1:
lw $t0, -32($fp)
li $t1, 5
bge $t0, $t1, LABEL3
lw $t0, -32($fp)
li $t1, 4
lw $t2, -36($fp)
mul $t2, $t0, $t1
sw $t2, -36($fp)
addi $t0, $fp, -28
lw $t1, -36($fp)
lw $t2, -40($fp)
add $t2, $t0, $t1
sw $t2, -40($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -44($fp)
move $t0, $v0
sw $t0, -44($fp)
lw $t0, -44($fp)
lw $t1, -40($fp)
sw $t0, 0($t1)
lw $t0, -32($fp)
li $t1, 1
lw $t2, -48($fp)
add $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -48($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
j LABEL1
LABEL3:
li $t0, 1
lw $t1, -52($fp)
move $t1, $t0
sw $t1, -52($fp)
LABEL4:
lw $t0, -52($fp)
li $t1, 1
bne $t0, $t1, LABEL6
li $t0, 0
lw $t1, -52($fp)
move $t1, $t0
sw $t1, -52($fp)
li $t0, 1
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL7:
lw $t0, -32($fp)
li $t1, 5
bge $t0, $t1, LABEL9
lw $t0, -32($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
LABEL10:
lw $t0, -56($fp)
li $t1, 0
ble $t0, $t1, LABEL12
lw $t0, -56($fp)
li $t1, 4
lw $t2, -60($fp)
mul $t2, $t0, $t1
sw $t2, -60($fp)
addi $t0, $fp, -28
lw $t1, -60($fp)
lw $t2, -64($fp)
add $t2, $t0, $t1
sw $t2, -64($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -68($fp)
sub $t2, $t0, $t1
sw $t2, -68($fp)
lw $t0, -68($fp)
li $t1, 4
lw $t2, -72($fp)
mul $t2, $t0, $t1
sw $t2, -72($fp)
addi $t0, $fp, -28
lw $t1, -72($fp)
lw $t2, -76($fp)
add $t2, $t0, $t1
sw $t2, -76($fp)
lw $t0, -64($fp)
lw $t0, 0($t0)
lw $t1, -76($fp)
lw $t1, 0($t1)
bge $t0, $t1, LABEL12
lw $t0, -56($fp)
li $t1, 4
lw $t2, -80($fp)
mul $t2, $t0, $t1
sw $t2, -80($fp)
addi $t0, $fp, -28
lw $t1, -80($fp)
lw $t2, -84($fp)
add $t2, $t0, $t1
sw $t2, -84($fp)
lw $t0, -84($fp)
lw $t0, 0($t0)
lw $t1, -88($fp)
move $t1, $t0
sw $t1, -88($fp)
lw $t0, -56($fp)
li $t1, 4
lw $t2, -92($fp)
mul $t2, $t0, $t1
sw $t2, -92($fp)
addi $t0, $fp, -28
lw $t1, -92($fp)
lw $t2, -96($fp)
add $t2, $t0, $t1
sw $t2, -96($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -100($fp)
sub $t2, $t0, $t1
sw $t2, -100($fp)
lw $t0, -100($fp)
li $t1, 4
lw $t2, -104($fp)
mul $t2, $t0, $t1
sw $t2, -104($fp)
addi $t0, $fp, -28
lw $t1, -104($fp)
lw $t2, -108($fp)
add $t2, $t0, $t1
sw $t2, -108($fp)
lw $t0, -108($fp)
lw $t0, 0($t0)
lw $t1, -96($fp)
sw $t0, 0($t1)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -112($fp)
sub $t2, $t0, $t1
sw $t2, -112($fp)
lw $t0, -112($fp)
li $t1, 4
lw $t2, -116($fp)
mul $t2, $t0, $t1
sw $t2, -116($fp)
addi $t0, $fp, -28
lw $t1, -116($fp)
lw $t2, -120($fp)
add $t2, $t0, $t1
sw $t2, -120($fp)
lw $t0, -88($fp)
lw $t1, -120($fp)
sw $t0, 0($t1)
li $t0, 1
lw $t1, -52($fp)
move $t1, $t0
sw $t1, -52($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -124($fp)
sub $t2, $t0, $t1
sw $t2, -124($fp)
lw $t0, -124($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
j LABEL10
LABEL12:
lw $t0, -32($fp)
li $t1, 1
lw $t2, -128($fp)
add $t2, $t0, $t1
sw $t2, -128($fp)
lw $t0, -128($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
j LABEL7
LABEL9:
j LABEL4
LABEL6:
li $t0, 0
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL14:
lw $t0, -32($fp)
li $t1, 5
bge $t0, $t1, LABEL16
lw $t0, -32($fp)
li $t1, 4
lw $t2, -132($fp)
mul $t2, $t0, $t1
sw $t2, -132($fp)
addi $t0, $fp, -28
lw $t1, -132($fp)
lw $t2, -136($fp)
add $t2, $t0, $t1
sw $t2, -136($fp)
lw $t0, -136($fp)
lw $t0, 0($t0)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -140($fp)
move $t1, $t0
sw $t1, -140($fp)
lw $t0, -32($fp)
li $t1, 1
lw $t2, -144($fp)
add $t2, $t0, $t1
sw $t2, -144($fp)
lw $t0, -144($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
j LABEL14
LABEL16:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
