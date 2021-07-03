.globl f
.ent f
f:
addiu $sp,$sp,-44
sw $fp,40($sp)
move $fp,$sp
sw $4,44($fp)
sw $5,48($fp)
li $2,0
sw $2,28($fp)
_while_start_1:
lw $3,28($fp)
lw $2,48($fp)
nop
slt $2,$3,$2
beq $2,$0,_while_end_2
nop
lw $2,28($fp)
nop
addiu $2,$2,1
sw $2,28($fp)
lw $3,0($fp)
lw $2,44($fp)
nop
mult $3,$2
mflo $2
sw $2,24($fp)
b _while_start_1
nop

_while_end_2:
lw $2,24($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,40($sp)
addiu $sp,$sp,44
jr $31
nop
.end f
