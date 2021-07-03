.globl f
.ent f
f:
addiu $sp,$sp,-112
sw $fp,108($sp)
move $fp,$sp
li $2,8
sw $2,96($fp)
_for_start_1:
lw $3,96($fp)
li $2,16
nop
slt $2,$3,$2
beq $2,$0,_for_end_2
nop
lw $3,96($fp)
li $2,8
nop
subu $2,$3,$2
sw $2,92($fp)
lw $2,96($fp)
nop
sw $2,88($fp)
lw $2,96($fp)
nop
addiu $2,$2,1
sw $2,96($fp)
b _for_start_1
nop
_for_end_2:
li $2,0
sw $2,84($fp)
li $2,0
sw $2,96($fp)
_for_start_4:
lw $3,96($fp)
li $2,8
nop
slt $2,$3,$2
beq $2,$0,_for_end_5
nop
lw $3,96($fp)
li $2,0
nop
addu $2,$2,$3
sw $2,80($fp)
lw $2,0($fp)
lw $3,84($fp)
nop
addu $2,$2,$3
sw $2,84($fp)
lw $2,96($fp)
nop
addiu $2,$2,1
sw $2,96($fp)
b _for_start_4
nop
_for_end_5:
lw $2,84($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,108($sp)
addiu $sp,$sp,112
jr $31
nop
.end f
