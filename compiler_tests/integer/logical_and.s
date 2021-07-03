.globl f
.ent f
f:
addiu $sp,$sp,-16
sw $fp,12($sp)
move $fp,$sp
sw $4,16($fp)
sw $5,20($fp)
lw $2,16($fp)
nop
beq $2,$0,_and_1
nop

lw $2,20($fp)
nop
beq $2,$0,_and_1
nop

li $2,1
b _and_2
nop

_and_1:
move $2,$0

_and_2:
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,12($sp)
addiu $sp,$sp,16
jr $31
nop
.end f
