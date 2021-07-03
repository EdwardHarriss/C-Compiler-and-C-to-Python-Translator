.globl g
.ent g
g:
.frame $fp,32,$31
addiu $sp,$sp,-32
sw $31,28($sp)
sw $fp,24($sp)
move $fp,$sp
.cprestore 16
lw $2,0($fp)
nop
sw $2,0($fp)
_return_0:
move $sp,$fp
lw $31,28($sp)
lw $fp,24($sp)
addiu $sp,$sp,32
jr $31
nop
.end g
