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
addi $sp, $sp, -344
li $t0, 10
lw $t1, -12($fp)
move $t1, $t0
sw $t1, -12($fp)
li $t0, 0
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
li $t0, 0
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
LABEL1:
lw $t0, -96($fp)
li $t1, 10
bge $t0, $t1, LABEL3
lw $t0, -96($fp)
li $t1, 4
lw $t2, -104($fp)
mul $t2, $t0, $t1
sw $t2, -104($fp)
addi $t0, $fp, -52
lw $t1, -104($fp)
lw $t2, -108($fp)
add $t2, $t0, $t1
sw $t2, -108($fp)
addi $sp, $sp, -4
sw $ra, 0($sp)
jal read
lw $ra, 0($sp)
addi $sp, $sp, 4
lw $t0, -112($fp)
move $t0, $v0
sw $t0, -112($fp)
lw $t0, -112($fp)
lw $t1, -108($fp)
sw $t0, 0($t1)
lw $t0, -96($fp)
li $t1, 1
lw $t2, -116($fp)
add $t2, $t0, $t1
sw $t2, -116($fp)
lw $t0, -116($fp)
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
j LABEL1
LABEL3:
li $t0, 5
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
LABEL4:
lw $t0, -120($fp)
li $t1, 0
blt $t0, $t1, LABEL6
li $t0, 0
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
lw $t0, -120($fp)
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
LABEL7:
lw $t0, -100($fp)
li $t1, 0
bne $t0, $t1, LABEL9
li $t0, 1
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
lw $t0, -96($fp)
li $t1, 2
lw $t2, -124($fp)
mul $t2, $t0, $t1
sw $t2, -124($fp)
lw $t0, -124($fp)
li $t1, 1
lw $t2, -128($fp)
add $t2, $t0, $t1
sw $t2, -128($fp)
lw $t0, -128($fp)
lw $t1, -132($fp)
move $t1, $t0
sw $t1, -132($fp)
lw $t0, -96($fp)
li $t1, 2
lw $t2, -136($fp)
mul $t2, $t0, $t1
sw $t2, -136($fp)
lw $t0, -136($fp)
li $t1, 2
lw $t2, -140($fp)
add $t2, $t0, $t1
sw $t2, -140($fp)
lw $t0, -140($fp)
lw $t1, -144($fp)
move $t1, $t0
sw $t1, -144($fp)
lw $t0, -132($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL16
lw $t0, -132($fp)
li $t1, 4
lw $t2, -148($fp)
mul $t2, $t0, $t1
sw $t2, -148($fp)
addi $t0, $fp, -52
lw $t1, -148($fp)
lw $t2, -152($fp)
add $t2, $t0, $t1
sw $t2, -152($fp)
lw $t0, -152($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
move $t1, $t0
sw $t1, -156($fp)
lw $t0, -144($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL13
lw $t0, -144($fp)
li $t1, 4
lw $t2, -160($fp)
mul $t2, $t0, $t1
sw $t2, -160($fp)
addi $t0, $fp, -52
lw $t1, -160($fp)
lw $t2, -164($fp)
add $t2, $t0, $t1
sw $t2, -164($fp)
lw $t0, -132($fp)
li $t1, 4
lw $t2, -168($fp)
mul $t2, $t0, $t1
sw $t2, -168($fp)
addi $t0, $fp, -52
lw $t1, -168($fp)
lw $t2, -172($fp)
add $t2, $t0, $t1
sw $t2, -172($fp)
lw $t0, -164($fp)
lw $t0, 0($t0)
lw $t1, -172($fp)
lw $t1, 0($t1)
bge $t0, $t1, LABEL13
lw $t0, -144($fp)
li $t1, 4
lw $t2, -176($fp)
mul $t2, $t0, $t1
sw $t2, -176($fp)
addi $t0, $fp, -52
lw $t1, -176($fp)
lw $t2, -180($fp)
add $t2, $t0, $t1
sw $t2, -180($fp)
lw $t0, -180($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
move $t1, $t0
sw $t1, -156($fp)
lw $t0, -144($fp)
lw $t1, -132($fp)
move $t1, $t0
sw $t1, -132($fp)
LABEL13:
lw $t0, -96($fp)
li $t1, 4
lw $t2, -184($fp)
mul $t2, $t0, $t1
sw $t2, -184($fp)
addi $t0, $fp, -52
lw $t1, -184($fp)
lw $t2, -188($fp)
add $t2, $t0, $t1
sw $t2, -188($fp)
lw $t0, -188($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
ble $t0, $t1, LABEL16
li $t0, 0
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
lw $t0, -132($fp)
li $t1, 4
lw $t2, -192($fp)
mul $t2, $t0, $t1
sw $t2, -192($fp)
addi $t0, $fp, -52
lw $t1, -192($fp)
lw $t2, -196($fp)
add $t2, $t0, $t1
sw $t2, -196($fp)
lw $t0, -96($fp)
li $t1, 4
lw $t2, -200($fp)
mul $t2, $t0, $t1
sw $t2, -200($fp)
addi $t0, $fp, -52
lw $t1, -200($fp)
lw $t2, -204($fp)
add $t2, $t0, $t1
sw $t2, -204($fp)
lw $t0, -204($fp)
lw $t0, 0($t0)
lw $t1, -196($fp)
sw $t0, 0($t1)
lw $t0, -96($fp)
li $t1, 4
lw $t2, -208($fp)
mul $t2, $t0, $t1
sw $t2, -208($fp)
addi $t0, $fp, -52
lw $t1, -208($fp)
lw $t2, -212($fp)
add $t2, $t0, $t1
sw $t2, -212($fp)
lw $t0, -156($fp)
lw $t1, -212($fp)
sw $t0, 0($t1)
lw $t0, -132($fp)
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
LABEL16:
j LABEL7
LABEL9:
lw $t0, -120($fp)
li $t1, 1
lw $t2, -216($fp)
sub $t2, $t0, $t1
sw $t2, -216($fp)
lw $t0, -216($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
j LABEL4
LABEL6:
li $t0, 10
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
li $t0, 0
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
LABEL17:
lw $t0, -96($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL19
lw $t0, -96($fp)
li $t1, 4
lw $t2, -220($fp)
mul $t2, $t0, $t1
sw $t2, -220($fp)
addi $t0, $fp, -92
lw $t1, -220($fp)
lw $t2, -224($fp)
add $t2, $t0, $t1
sw $t2, -224($fp)
addi $t0, $fp, -52
li $t1, 0
lw $t2, -228($fp)
add $t2, $t0, $t1
sw $t2, -228($fp)
lw $t0, -228($fp)
lw $t0, 0($t0)
lw $t1, -224($fp)
sw $t0, 0($t1)
lw $t0, -96($fp)
li $t1, 1
lw $t2, -232($fp)
add $t2, $t0, $t1
sw $t2, -232($fp)
lw $t0, -232($fp)
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
addi $t0, $fp, -52
li $t1, 0
lw $t2, -236($fp)
add $t2, $t0, $t1
sw $t2, -236($fp)
lw $t0, -120($fp)
li $t1, 1
lw $t2, -240($fp)
sub $t2, $t0, $t1
sw $t2, -240($fp)
lw $t0, -240($fp)
li $t1, 4
lw $t2, -244($fp)
mul $t2, $t0, $t1
sw $t2, -244($fp)
addi $t0, $fp, -52
lw $t1, -244($fp)
lw $t2, -248($fp)
add $t2, $t0, $t1
sw $t2, -248($fp)
lw $t0, -248($fp)
lw $t0, 0($t0)
lw $t1, -236($fp)
sw $t0, 0($t1)
li $t0, 0
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
lw $t0, -120($fp)
li $t1, 1
lw $t2, -252($fp)
sub $t2, $t0, $t1
sw $t2, -252($fp)
lw $t0, -252($fp)
lw $t1, -120($fp)
move $t1, $t0
sw $t1, -120($fp)
li $t0, 0
lw $t1, -256($fp)
move $t1, $t0
sw $t1, -256($fp)
LABEL20:
lw $t0, -100($fp)
li $t1, 0
bne $t0, $t1, LABEL22
li $t0, 1
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
lw $t0, -256($fp)
li $t1, 2
lw $t2, -260($fp)
mul $t2, $t0, $t1
sw $t2, -260($fp)
lw $t0, -260($fp)
li $t1, 1
lw $t2, -264($fp)
add $t2, $t0, $t1
sw $t2, -264($fp)
lw $t0, -264($fp)
lw $t1, -132($fp)
move $t1, $t0
sw $t1, -132($fp)
lw $t0, -256($fp)
li $t1, 2
lw $t2, -268($fp)
mul $t2, $t0, $t1
sw $t2, -268($fp)
lw $t0, -268($fp)
li $t1, 2
lw $t2, -272($fp)
add $t2, $t0, $t1
sw $t2, -272($fp)
lw $t0, -272($fp)
lw $t1, -144($fp)
move $t1, $t0
sw $t1, -144($fp)
lw $t0, -132($fp)
lw $t1, -120($fp)
bge $t0, $t1, LABEL29
lw $t0, -132($fp)
li $t1, 4
lw $t2, -276($fp)
mul $t2, $t0, $t1
sw $t2, -276($fp)
addi $t0, $fp, -52
lw $t1, -276($fp)
lw $t2, -280($fp)
add $t2, $t0, $t1
sw $t2, -280($fp)
lw $t0, -280($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
move $t1, $t0
sw $t1, -156($fp)
lw $t0, -144($fp)
lw $t1, -120($fp)
bge $t0, $t1, LABEL26
lw $t0, -144($fp)
li $t1, 4
lw $t2, -284($fp)
mul $t2, $t0, $t1
sw $t2, -284($fp)
addi $t0, $fp, -52
lw $t1, -284($fp)
lw $t2, -288($fp)
add $t2, $t0, $t1
sw $t2, -288($fp)
lw $t0, -132($fp)
li $t1, 4
lw $t2, -292($fp)
mul $t2, $t0, $t1
sw $t2, -292($fp)
addi $t0, $fp, -52
lw $t1, -292($fp)
lw $t2, -296($fp)
add $t2, $t0, $t1
sw $t2, -296($fp)
lw $t0, -288($fp)
lw $t0, 0($t0)
lw $t1, -296($fp)
lw $t1, 0($t1)
bge $t0, $t1, LABEL26
lw $t0, -144($fp)
li $t1, 4
lw $t2, -300($fp)
mul $t2, $t0, $t1
sw $t2, -300($fp)
addi $t0, $fp, -52
lw $t1, -300($fp)
lw $t2, -304($fp)
add $t2, $t0, $t1
sw $t2, -304($fp)
lw $t0, -304($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
move $t1, $t0
sw $t1, -156($fp)
lw $t0, -144($fp)
lw $t1, -132($fp)
move $t1, $t0
sw $t1, -132($fp)
LABEL26:
lw $t0, -256($fp)
li $t1, 4
lw $t2, -308($fp)
mul $t2, $t0, $t1
sw $t2, -308($fp)
addi $t0, $fp, -52
lw $t1, -308($fp)
lw $t2, -312($fp)
add $t2, $t0, $t1
sw $t2, -312($fp)
lw $t0, -312($fp)
lw $t0, 0($t0)
lw $t1, -156($fp)
ble $t0, $t1, LABEL29
li $t0, 0
lw $t1, -100($fp)
move $t1, $t0
sw $t1, -100($fp)
lw $t0, -132($fp)
li $t1, 4
lw $t2, -316($fp)
mul $t2, $t0, $t1
sw $t2, -316($fp)
addi $t0, $fp, -52
lw $t1, -316($fp)
lw $t2, -320($fp)
add $t2, $t0, $t1
sw $t2, -320($fp)
lw $t0, -256($fp)
li $t1, 4
lw $t2, -324($fp)
mul $t2, $t0, $t1
sw $t2, -324($fp)
addi $t0, $fp, -52
lw $t1, -324($fp)
lw $t2, -328($fp)
add $t2, $t0, $t1
sw $t2, -328($fp)
lw $t0, -328($fp)
lw $t0, 0($t0)
lw $t1, -320($fp)
sw $t0, 0($t1)
lw $t0, -256($fp)
li $t1, 4
lw $t2, -332($fp)
mul $t2, $t0, $t1
sw $t2, -332($fp)
addi $t0, $fp, -52
lw $t1, -332($fp)
lw $t2, -336($fp)
add $t2, $t0, $t1
sw $t2, -336($fp)
lw $t0, -156($fp)
lw $t1, -336($fp)
sw $t0, 0($t1)
lw $t0, -132($fp)
lw $t1, -256($fp)
move $t1, $t0
sw $t1, -256($fp)
LABEL29:
j LABEL20
LABEL22:
j LABEL17
LABEL19:
li $t0, 0
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
LABEL30:
lw $t0, -96($fp)
lw $t1, -12($fp)
bge $t0, $t1, LABEL32
lw $t0, -96($fp)
li $t1, 4
lw $t2, -340($fp)
mul $t2, $t0, $t1
sw $t2, -340($fp)
addi $t0, $fp, -92
lw $t1, -340($fp)
lw $t2, -344($fp)
add $t2, $t0, $t1
sw $t2, -344($fp)
lw $t0, -344($fp)
lw $t0, 0($t0)
move $a0, $t0
addi $sp, $sp, -4
sw $ra, 0($sp)
jal write
lw $ra, 0($sp)
addi $sp, $sp, 4
li $t0, 0
lw $t1, -348($fp)
move $t1, $t0
sw $t1, -348($fp)
lw $t0, -96($fp)
li $t1, 1
lw $t2, -352($fp)
add $t2, $t0, $t1
sw $t2, -352($fp)
lw $t0, -352($fp)
lw $t1, -96($fp)
move $t1, $t0
sw $t1, -96($fp)
j LABEL30
LABEL32:
lw $ra, -4($fp)
move $sp, $fp
li $t0, 0
lw $fp, -8($fp)
move $v0, $t0
jr $ra
