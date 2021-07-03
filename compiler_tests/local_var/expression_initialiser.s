.globl f
.ent f
f:
addiu $sp,$sp,-24
sw $fp,20($sp)
move $fp,$sp
li $2,10
sw $2,8($fp)
li $3,20
lw $2,8($fp)
nop
addu $2,$2,$3
sw $2,4($fp)
lw $2,4($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,20($sp)
addiu $sp,$sp,24
jr $31
nop
.end f
