.globl g
.ent g
g:
addiu $sp,$sp,-16
sw $fp,12($sp)
move $fp,$sp
li $3,0
li $2,1
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
.end g
