.globl f
.ent f
f:
addiu $sp,$sp,-72
sw $fp,68($sp)
move $fp,$sp
li $2,23
sw $2,8($fp)
lw $2,8($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,68($sp)
addiu $sp,$sp,72
jr $31
nop
.end f
