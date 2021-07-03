.globl f
.ent f
f:
addiu $sp,$sp,-36
sw $fp,32($sp)
move $fp,$sp
li $2,0
sw $2,20($fp)
lw $2,20($fp)
nop
addiu $2,$2,1
sw $2,20($fp)
lw $2,20($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,32($sp)
addiu $sp,$sp,36
jr $31
nop
.end f
