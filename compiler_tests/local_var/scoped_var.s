.globl f
.ent f
f:
addiu $sp,$sp,-32
sw $fp,28($sp)
move $fp,$sp
li $2,5678
sw $2,16($fp)
lw $2,16($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,28($sp)
addiu $sp,$sp,32
jr $31
nop
.end f
