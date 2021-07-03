.globl f
.ent f
f:
addiu $sp,$sp,-88
sw $fp,84($sp)
move $fp,$sp
li $2,8
sw $2,72($fp)
_for_start_1:
lw $3,72($fp)
li $2,16
nop
slt $2,$3,$2
beq $2,$0,_for_end_2
nop
lw $3,72($fp)
li $2,8
nop
subu $2,$3,$2
sw $2,68($fp)
lw $2,72($fp)
nop
sw $2,64($fp)
lw $2,72($fp)
nop
addiu $2,$2,1
sw $2,72($fp)
b _for_start_1
nop
_for_end_2:
lw $2,0($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,84($sp)
addiu $sp,$sp,88
jr $31
nop
.end f
