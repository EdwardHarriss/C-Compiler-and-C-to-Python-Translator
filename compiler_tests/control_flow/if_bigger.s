.globl f
.ent f
f:
addiu $sp,$sp,-20
sw $fp,16($sp)
move $fp,$sp
li $2,3
sw $2,4($fp)
lw $3,4($fp)
li $2,3
nop
addu $2,$2,$3
li $2,10
nop
slt $2,$3,$2
beq $2,$0,_if_not_1
nop
li $2,0
b _return_0
nop
_if_not_1:
nop
li $2,1
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,16($sp)
addiu $sp,$sp,20
jr $31
nop
.end f
