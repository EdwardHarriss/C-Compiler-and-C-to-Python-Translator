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
xor $2,$3,$2
sltu $2,$2,1
andi $2,$2,0x00ff
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,12($sp)
addiu $sp,$sp,16
jr $31
nop
.end f
