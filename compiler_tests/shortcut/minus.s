.globl f
.ent f
f:
addiu $sp,$sp,-32
sw $fp,28($sp)
move $fp,$sp
sw $4,32($fp)
lw $2,32($fp)
subiu $2,$2,1
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,28($sp)
addiu $sp,$sp,32
jr $31
nop
.end f
