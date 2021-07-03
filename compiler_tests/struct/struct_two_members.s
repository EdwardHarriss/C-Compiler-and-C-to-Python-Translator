.globl f
.ent f
f:
addiu $sp,$sp,-28
sw $fp,24($sp)
move $fp,$sp
li $2,17
sw $2,12($fp)
li $2,13
sw $2,12($fp)
nop
addu $2,$3,$2
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,24($sp)
addiu $sp,$sp,28
jr $31
nop
.end f
