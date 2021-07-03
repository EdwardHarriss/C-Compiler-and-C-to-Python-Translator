.globl f
.ent f
f:
addiu $sp,$sp,-32
sw $fp,28($sp)
move $fp,$sp
li $2,3
sw $2,16($fp)
li $2,2
sw $2,12($fp)
li $2,1
sw $2,8($fp)
lw $3,16($fp)
lw $2,12($fp)
nop
addu $2,$2,$3
move $3,$2
lw $2,8($fp)
nop
addu $2,$2,$3
move $3,$2
li $2,4
nop
addu $2,$2,$3
sw $2,4($fp)
lw $2,4($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,28($sp)
addiu $sp,$sp,32
jr $31
nop
.end f
