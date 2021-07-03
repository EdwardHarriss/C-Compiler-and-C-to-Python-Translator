.globl f
.ent f
f:
addiu $sp,$sp,-24
sw $fp,20($sp)
move $fp,$sp
li $2,3
sw $2,8($fp)
li $2,5
sw $2,4($fp)
lw $3,8($fp)
lw $2,4($fp)
nop
mult $3, $2
mflo $2
move $3,$2
li $2,5
nop
div $3,$2
mflo $2
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,20($sp)
addiu $sp,$sp,24
jr $31
nop
.end f
