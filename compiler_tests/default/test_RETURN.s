.globl f
.ent f
f:
addiu $sp,$sp,-16
sw $fp,12($sp)
move $fp,$sp
li $2,10
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,12($sp)
addiu $sp,$sp,16
jr $31
nop
.end f
