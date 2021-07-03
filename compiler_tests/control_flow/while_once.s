.globl f
.ent f
f:
addiu $sp,$sp,-28
sw $fp,24($sp)
move $fp,$sp
li $2,1
sw $2,12($fp)
_while_start_1:
lw $2,12($fp)
nop
beq $2,$0,_while_end_2
nop

li $2,0
sw $2,12($fp)
b _while_start_1
nop

_while_end_2:
li $2,19937
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,24($sp)
addiu $sp,$sp,28
jr $31
nop
.end f
