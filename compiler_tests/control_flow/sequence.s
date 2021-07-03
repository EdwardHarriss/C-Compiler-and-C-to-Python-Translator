.globl f
.ent f
f:
addiu $sp,$sp,-28
sw $fp,24($sp)
move $fp,$sp
li $2,1
sw $2,12($fp)
lw $3,12($fp)
lw $2,12($fp)
nop
addu $2,$2,$3
sw $2,12($fp)
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
