.globl multiply
.ent multiply
multiply:
.frame $fp,40,$31
addiu $sp,$sp,-40
sw $31,36($sp)
sw $fp,32($sp)
move $fp,$sp
.cprestore 24
sw $4,40($fp)
sw $5,44($fp)
li $2,0
sw $2,24($fp)
lw $3,40($fp)
li $2,0
nop
slt $2,$3,$2
beq $2,$0,_if_not_1
nop
lw $2,40
nop
subu $2,$0,$2
move $4,$2
lw $5,44($fp)
jal multiply
nop
subu $2,$0,$2
b _return_0
nop
_if_not_1:
nop
_while_start_2:
lw $3,40($fp)
li $2,0
nop
slt $2,$2,$3
beq $2,$0,_while_end_3
nop
lw $2,24($fp)
lw $3,44($fp)
nop
addu $2,$3,$2
sw $2,24($fp)
lw $2,40($fp)
nop
addiu $2,$2,-1
sw $2,40($fp)
b _while_start_2
nop

_while_end_3:
lw $2,24($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $31,36($sp)
lw $fp,32($sp)
addiu $sp,$sp,40
jr $31
nop
.end multiply
