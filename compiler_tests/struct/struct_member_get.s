.globl f
.ent f
f:
addiu $sp,$sp,-24
sw $fp,20($sp)
move $fp,$sp
li $2,13
sw $2,8($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,20($sp)
addiu $sp,$sp,24
jr $31
nop
.end f
