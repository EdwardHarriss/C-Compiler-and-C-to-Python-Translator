.globl f
.ent f
f:
addiu $sp,$sp,-24
sw $fp,20($sp)
move $fp,$sp
sw $4,24($fp)
sw $5,28($fp)
lw $3,24($fp)
lw $2,28($fp)
nop
slt $2,$2,$3
xori $2,$2,0x1
andi $2,$2,0x00ff
sw $2,8($fp)
lw $2,8($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,20($sp)
addiu $sp,$sp,24
jr $31
nop
.end f
