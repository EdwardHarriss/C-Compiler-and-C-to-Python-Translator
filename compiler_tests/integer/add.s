.globl f
.ent f
f:
addiu $sp,$sp,-16
sw $fp,12($sp)
move $fp,$sp
sw $4,16($fp)
sw $5,20($fp)
lw $3,16($fp)
lw $2,20($fp)
nop
addu $2,$3,$2
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,12($sp)
addiu $sp,$sp,16
jr $31
nop
.end f
