.globl f
.ent f
f:
addiu $sp,$sp,-20
sw $fp,16($sp)
move $fp,$sp
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,16($sp)
addiu $sp,$sp,20
jr $31
nop
.end f
