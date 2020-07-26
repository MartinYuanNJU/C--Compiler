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

func_process:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -104
li $t0, 3
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 36
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, 0($fp)
li $t1, 321
lw $t2, -16($fp)
mul $t2, $t0, $t1
sw $t2, -16($fp)
lw $t0, -16($fp)
li $t1, 2
lw $t2, -20($fp)
mul $t2, $t0, $t1
sw $t2, -20($fp)
lw $t0, 0($fp)
li $t1, 36
lw $t2, -24($fp)
mul $t2, $t0, $t1
sw $t2, -24($fp)
lw $t0, -20($fp)
lw $t1, -24($fp)
lw $t2, -28($fp)
add $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, -28($fp)
lw $t1, 0($fp)
lw $t2, -32($fp)
sub $t2, $t0, $t1
sw $t2, -32($fp)
li $t0, 36
lw $t1, 0($fp)
lw $t2, -36($fp)
mul $t2, $t0, $t1
sw $t2, -36($fp)
lw $t0, -32($fp)
lw $t1, -36($fp)
lw $t2, -40($fp)
add $t2, $t0, $t1
sw $t2, -40($fp)
lw $t0, -40($fp)
li $t1, 1296
lw $t2, -44($fp)
add $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -44($fp)
lw $t1, 0($fp)
lw $t2, -48($fp)
add $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -48($fp)
lw $t1, 0($fp)
lw $t2, -52($fp)
add $t2, $t0, $t1
sw $t2, -52($fp)
lw $t0, -52($fp)
li $t1, 23
lw $t2, -56($fp)
sub $t2, $t0, $t1
sw $t2, -56($fp)
lw $t0, -56($fp)
li $t1, 45
lw $t2, -60($fp)
add $t2, $t0, $t1
sw $t2, -60($fp)
lw $t0, -60($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -12($fp)
li $t1, 3
lw $t2, -64($fp)
div $t2, $t0, $t1
sw $t2, -64($fp)
lw $t0, -64($fp)
li $t1, 336
lw $t2, -68($fp)
add $t2, $t0, $t1
sw $t2, -68($fp)
lw $t0, 0($fp)
li $t1, 12
lw $t2, -72($fp)
mul $t2, $t0, $t1
sw $t2, -72($fp)
lw $t0, -72($fp)
li $t1, 4
lw $t2, -76($fp)
div $t2, $t0, $t1
sw $t2, -76($fp)
lw $t0, -68($fp)
lw $t1, -76($fp)
lw $t2, -80($fp)
sub $t2, $t0, $t1
sw $t2, -80($fp)
lw $t0, -80($fp)
li $t1, 60
lw $t2, -84($fp)
sub $t2, $t0, $t1
sw $t2, -84($fp)
lw $t0, -12($fp)
li $t1, 12
lw $t2, -88($fp)
div $t2, $t0, $t1
sw $t2, -88($fp)
lw $t0, -88($fp)
li $t1, 24
lw $t2, -92($fp)
mul $t2, $t0, $t1
sw $t2, -92($fp)
lw $t0, -84($fp)
lw $t1, -92($fp)
lw $t2, -96($fp)
add $t2, $t0, $t1
sw $t2, -96($fp)
lw $t0, -96($fp)
li $t1, 36
lw $t2, -100($fp)
add $t2, $t0, $t1
sw $t2, -100($fp)
lw $t0, -100($fp)
li $t1, 1
lw $t2, -104($fp)
add $t2, $t0, $t1
sw $t2, -104($fp)
lw $t0, -104($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, 0($fp)
li $t1, 24
lw $t2, -108($fp)
add $t2, $t0, $t1
sw $t2, -108($fp)
lw $t0, -108($fp)
li $t1, 1
lw $t2, -112($fp)
add $t2, $t0, $t1
sw $t2, -112($fp)
lw $t0, -112($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
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
addi $sp, $sp, -220
li $t0, 13
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 20
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
li $t0, 15
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
li $t0, 48
lw $t1, -24($fp)
move $t1, $t0
sw $t1, -24($fp)
li $t0, 267
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
li $t0, -22
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
li $t0, 42
lw $t1, -36($fp)
move $t1, $t0
sw $t1, -36($fp)
li $t0, 0
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
li $t0, 2070
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL1:
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -44($fp)
add $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -44($fp)
lw $t1, -32($fp)
bge $t0, $t1, LABEL3
lw $t0, -40($fp)
li $t1, 12
lw $t2, -48($fp)
mul $t2, $t0, $t1
sw $t2, -48($fp)
lw $t0, -36($fp)
lw $t1, -48($fp)
lw $t2, -52($fp)
add $t2, $t0, $t1
sw $t2, -52($fp)
lw $t0, -52($fp)
li $t1, 4
lw $t2, -56($fp)
add $t2, $t0, $t1
sw $t2, -56($fp)
lw $t0, -56($fp)
li $t1, 5
lw $t2, -60($fp)
add $t2, $t0, $t1
sw $t2, -60($fp)
lw $t0, -60($fp)
li $t1, 2
lw $t2, -64($fp)
add $t2, $t0, $t1
sw $t2, -64($fp)
lw $t0, -64($fp)
lw $t1, -36($fp)
move $t1, $t0
sw $t1, -36($fp)
addi $sp, $sp, -4
lw $t0, -32($fp)
sw $t0, 0($sp)
jal func_process
lw $t0, -68($fp)
move $t0, $v0
sw $t0, -68($fp)
addi $sp, $sp, 4
li $t0, 2
lw $t1, -12($fp)
lw $t2, -72($fp)
mul $t2, $t0, $t1
sw $t2, -72($fp)
lw $t0, -68($fp)
lw $t1, -72($fp)
lw $t2, -76($fp)
add $t2, $t0, $t1
sw $t2, -76($fp)
lw $t0, -76($fp)
lw $t1, -32($fp)
lw $t2, -80($fp)
sub $t2, $t0, $t1
sw $t2, -80($fp)
lw $t0, -20($fp)
lw $t1, -24($fp)
lw $t2, -84($fp)
mul $t2, $t0, $t1
sw $t2, -84($fp)
lw $t0, -80($fp)
lw $t1, -84($fp)
lw $t2, -88($fp)
add $t2, $t0, $t1
sw $t2, -88($fp)
lw $t0, -88($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
lw $t0, -40($fp)
lw $t1, -40($fp)
lw $t2, -96($fp)
add $t2, $t0, $t1
sw $t2, -96($fp)
lw $t0, -96($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -40($fp)
lw $t1, -40($fp)
lw $t2, -100($fp)
add $t2, $t0, $t1
sw $t2, -100($fp)
lw $t0, -100($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -40($fp)
lw $t1, -40($fp)
lw $t2, -104($fp)
add $t2, $t0, $t1
sw $t2, -104($fp)
lw $t0, -104($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -40($fp)
lw $t1, -40($fp)
lw $t2, -108($fp)
add $t2, $t0, $t1
sw $t2, -108($fp)
lw $t0, -108($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -40($fp)
lw $t1, -40($fp)
lw $t2, -112($fp)
add $t2, $t0, $t1
sw $t2, -112($fp)
lw $t0, -112($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -40($fp)
li $t1, 3
lw $t2, -116($fp)
add $t2, $t0, $t1
sw $t2, -116($fp)
lw $t0, -116($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
lw $t0, -120($fp)
li $t1, 1
lw $t2, -124($fp)
sub $t2, $t0, $t1
sw $t2, -124($fp)
lw $t0, -124($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
lw $t0, -120($fp)
li $t1, 3
lw $t2, -128($fp)
add $t2, $t0, $t1
sw $t2, -128($fp)
lw $t0, -128($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
lw $t0, -120($fp)
li $t1, 6
lw $t2, -132($fp)
sub $t2, $t0, $t1
sw $t2, -132($fp)
lw $t0, -132($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
addi $sp, $sp, -4
lw $t0, -12($fp)
sw $t0, 0($sp)
jal func_process
lw $t0, -136($fp)
move $t0, $v0
sw $t0, -136($fp)
addi $sp, $sp, 4
lw $t0, -12($fp)
li $t1, 3
lw $t2, -140($fp)
add $t2, $t0, $t1
sw $t2, -140($fp)
lw $t0, -140($fp)
li $t1, 2
lw $t2, -144($fp)
sub $t2, $t0, $t1
sw $t2, -144($fp)
lw $t0, -144($fp)
li $t1, 1
lw $t2, -148($fp)
sub $t2, $t0, $t1
sw $t2, -148($fp)
addi $sp, $sp, -4
lw $t0, -148($fp)
sw $t0, 0($sp)
jal func_process
lw $t0, -152($fp)
move $t0, $v0
sw $t0, -152($fp)
addi $sp, $sp, 4
lw $t0, -136($fp)
lw $t1, -152($fp)
bne $t0, $t1, LABEL5
lw $t0, -32($fp)
li $t1, 2
lw $t2, -156($fp)
sub $t2, $t0, $t1
sw $t2, -156($fp)
lw $t0, -156($fp)
li $t1, 1
lw $t2, -160($fp)
add $t2, $t0, $t1
sw $t2, -160($fp)
lw $t0, -160($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
LABEL5:
lw $t0, -12($fp)
li $t1, 2
lw $t2, -164($fp)
add $t2, $t0, $t1
sw $t2, -164($fp)
lw $t0, -164($fp)
li $t1, 1
lw $t2, -168($fp)
add $t2, $t0, $t1
sw $t2, -168($fp)
lw $t0, -168($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
j LABEL1
LABEL3:
lw $t0, -36($fp)
li $t1, 12
lw $t2, -172($fp)
sub $t2, $t0, $t1
sw $t2, -172($fp)
lw $t0, -172($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
LABEL6:
lw $t0, -120($fp)
lw $t1, -36($fp)
bge $t0, $t1, LABEL8
li $t0, 58
lw $t1, -12($fp)
lw $t2, -176($fp)
add $t2, $t0, $t1
sw $t2, -176($fp)
lw $t0, -176($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
lw $t0, -36($fp)
li $t1, 12
lw $t2, -180($fp)
sub $t2, $t0, $t1
sw $t2, -180($fp)
lw $t0, -180($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
lw $t0, -120($fp)
li $t1, 1
lw $t2, -184($fp)
add $t2, $t0, $t1
sw $t2, -184($fp)
lw $t0, -184($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
lw $t0, -36($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -188($fp)
add $t2, $t0, $t1
sw $t2, -188($fp)
lw $t0, -188($fp)
lw $t1, -40($fp)
move $t1, $t0
sw $t1, -40($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -192($fp)
add $t2, $t0, $t1
sw $t2, -192($fp)
lw $t0, -192($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
j LABEL6
LABEL8:
lw $t0, -32($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -196($fp)
move $t1, $t0
sw $t1, -196($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -200($fp)
add $t2, $t0, $t1
sw $t2, -200($fp)
lw $t0, -200($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -204($fp)
add $t2, $t0, $t1
sw $t2, -204($fp)
lw $t0, -204($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -208($fp)
add $t2, $t0, $t1
sw $t2, -208($fp)
lw $t0, -208($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -212($fp)
add $t2, $t0, $t1
sw $t2, -212($fp)
lw $t0, -212($fp)
lw $t1, -32($fp)
move $t1, $t0
sw $t1, -32($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
lw $t2, -216($fp)
add $t2, $t0, $t1
sw $t2, -216($fp)
lw $t0, -216($fp)
lw $t1, -92($fp)
move $t1, $t0
sw $t1, -92($fp)
lw $t0, -20($fp)
lw $t1, -32($fp)
lw $t2, -220($fp)
add $t2, $t0, $t1
sw $t2, -220($fp)
lw $t0, -220($fp)
lw $t1, -92($fp)
lw $t2, -224($fp)
add $t2, $t0, $t1
sw $t2, -224($fp)
lw $t0, -224($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -228($fp)
move $t1, $t0
sw $t1, -228($fp)
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
