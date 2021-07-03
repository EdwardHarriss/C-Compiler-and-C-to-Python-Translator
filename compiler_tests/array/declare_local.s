.globl f
.ent f
f:
addiu $sp,$sp,-60
sw $fp,56($sp)
move $fp,$sp
li $2,13
sw $2,44($fp)
lw $2,44($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,56($sp)
addiu $sp,$sp,60
jr $31
nop
.end f
