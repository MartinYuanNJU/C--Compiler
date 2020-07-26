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

func_isPrime:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -24
lw $t0, 0($fp)
li $t1, 4
lw $t2, -12($fp)
div $t2, $t0, $t1
sw $t2, -12($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
li $t0, 2
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
LABEL1:
lw $t0, -20($fp)
lw $t1, -16($fp)
bge $t0, $t1, LABEL3
lw $t0, 0($fp)
lw $t1, -20($fp)
lw $t2, -24($fp)
div $t2, $t0, $t1
sw $t2, -24($fp)
lw $t0, -24($fp)
lw $t1, -20($fp)
lw $t2, -28($fp)
mul $t2, $t0, $t1
sw $t2, -28($fp)
lw $t0, 0($fp)
lw $t1, -28($fp)
bne $t0, $t1, LABEL5
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL5:
lw $t0, -20($fp)
li $t1, 1
lw $t2, -32($fp)
add $t2, $t0, $t1
sw $t2, -32($fp)
lw $t0, -32($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
j LABEL1
LABEL3:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 1
lw $fp, -8($fp)
move $v0, $t0
jr $ra

func_isRever:
addi $sp, $sp, -4
sw $ra, 0($sp)
addi $sp, $sp, -4
sw $fp, 0($sp)
move $fp, $sp
addi $fp, $fp, 8
addi $sp, $sp, -108
lw $t0, 0($fp)
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
LABEL6:
lw $t0, -12($fp)
li $t1, 0
beq $t0, $t1, LABEL8
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
lw $t0, -12($fp)
li $t1, 10
lw $t2, -72($fp)
div $t2, $t0, $t1
sw $t2, -72($fp)
lw $t0, -72($fp)
li $t1, 10
lw $t2, -76($fp)
mul $t2, $t0, $t1
sw $t2, -76($fp)
lw $t0, -12($fp)
lw $t1, -76($fp)
lw $t2, -80($fp)
sub $t2, $t0, $t1
sw $t2, -80($fp)
lw $t0, -80($fp)
lw $t1, -68($fp)
sw $t0, 0($t1)
lw $t0, -12($fp)
li $t1, 10
lw $t2, -84($fp)
div $t2, $t0, $t1
sw $t2, -84($fp)
lw $t0, -84($fp)
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -88($fp)
add $t2, $t0, $t1
sw $t2, -88($fp)
lw $t0, -88($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
j LABEL6
LABEL8:
lw $t0, -56($fp)
li $t1, 1
lw $t2, -92($fp)
sub $t2, $t0, $t1
sw $t2, -92($fp)
lw $t0, -92($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
LABEL9:
lw $t0, -60($fp)
lw $t1, -56($fp)
beq $t0, $t1, LABEL11
lw $t0, -60($fp)
li $t1, 4
lw $t2, -96($fp)
mul $t2, $t0, $t1
sw $t2, -96($fp)
addi $t0, $fp, -52
lw $t1, -96($fp)
lw $t2, -100($fp)
add $t2, $t0, $t1
sw $t2, -100($fp)
lw $t0, -56($fp)
li $t1, 4
lw $t2, -104($fp)
mul $t2, $t0, $t1
sw $t2, -104($fp)
addi $t0, $fp, -52
lw $t1, -104($fp)
lw $t2, -108($fp)
add $t2, $t0, $t1
sw $t2, -108($fp)
lw $t0, -100($fp)
lw $t0, 0($t0)
lw $t1, -108($fp)
lw $t1, 0($t1)
beq $t0, $t1, LABEL13
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
LABEL13:
lw $t0, -60($fp)
li $t1, 1
lw $t2, -112($fp)
add $t2, $t0, $t1
sw $t2, -112($fp)
lw $t0, -112($fp)
lw $t1, -60($fp)
move $t1, $t0
sw $t1, -60($fp)
lw $t0, -56($fp)
li $t1, 1
lw $t2, -116($fp)
sub $t2, $t0, $t1
sw $t2, -116($fp)
lw $t0, -116($fp)
lw $t1, -56($fp)
move $t1, $t0
sw $t1, -56($fp)
j LABEL9
LABEL11:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 1
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
addi $sp, $sp, -36
li $t0, 100
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 110
lw $t1, -16($fp)
move $t1, $t0
sw $t1, -16($fp)
li $t0, 100
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
LABEL14:
lw $t0, -20($fp)
lw $t1, -16($fp)
bge $t0, $t1, LABEL16
addi $sp, $sp, -4
lw $t0, -20($fp)
sw $t0, 0($sp)
jal func_isPrime
lw $t0, -24($fp)
move $t0, $v0
sw $t0, -24($fp)
addi $sp, $sp, 4
lw $t0, -24($fp)
li $t1, 1
bne $t0, $t1, LABEL18
lw $t0, -20($fp)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -28($fp)
move $t1, $t0
sw $t1, -28($fp)
LABEL18:
addi $sp, $sp, -4
lw $t0, -20($fp)
sw $t0, 0($sp)
jal func_isRever
lw $t0, -32($fp)
move $t0, $v0
sw $t0, -32($fp)
addi $sp, $sp, 4
lw $t0, -32($fp)
li $t1, 1
bne $t0, $t1, LABEL20
li $t0, 0
lw $t1, -20($fp)
lw $t2, -36($fp)
sub $t2, $t0, $t1
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
LABEL20:
lw $t0, -20($fp)
li $t1, 1
lw $t2, -44($fp)
add $t2, $t0, $t1
sw $t2, -44($fp)
lw $t0, -44($fp)
lw $t1, -20($fp)
move $t1, $t0
sw $t1, -20($fp)
j LABEL14
LABEL16:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
