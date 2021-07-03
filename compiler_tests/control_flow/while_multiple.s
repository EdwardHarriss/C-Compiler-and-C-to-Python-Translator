.globl f
.ent f
f:
addiu $sp,$sp,-28
sw $fp,24($sp)
move $fp,$sp
li $2,20
sw $2,12($fp)
_while_start_1:
lw $3,12($fp)
li $2,10
nop
slt $2,$2,$3
beq $2,$0,_while_end_2
nop
lw $3,12($fp)
li $2,1
nop
subu $2,$3,$2
sw $2,12($fp)
b _while_start_1
nop

_while_end_2:
lw $2,12($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,24($sp)
addiu $sp,$sp,28
jr $31
nop
.end f
