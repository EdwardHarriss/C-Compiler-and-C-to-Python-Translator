.globl g
.ent g
g:
addiu $sp,$sp,-16
sw $fp,12($sp)
move $fp,$sp
sw $4,16($fp)
lw $2,16($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,12($sp)
addiu $sp,$sp,16
jr $31
nop
.end g
.globl f
.ent f
f:
.frame $fp,32,$31
addiu $sp,$sp,-32
sw $31,28($sp)
sw $fp,24($sp)
move $fp,$sp
.cprestore 16
.cprestore 16
li $4,10
jal g
nop
b _return_1
nop
_return_1:
move $sp,$fp
lw $31,28($sp)
lw $fp,24($sp)
addiu $sp,$sp,32
jr $31
nop
.end f
