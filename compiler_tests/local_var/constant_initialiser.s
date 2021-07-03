.globl f
.ent f
f:
addiu $sp,$sp,-20
sw $fp,16($sp)
move $fp,$sp
li $2,12345
sw $2,4($fp)
lw $2,4($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,16($sp)
addiu $sp,$sp,20
jr $31
nop
.end f
