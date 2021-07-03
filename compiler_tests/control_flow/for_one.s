.globl f
.ent f
f:
addiu $sp,$sp,-28
sw $fp,24($sp)
move $fp,$sp
li $2,0
sw $2,12($fp)
_for_start_1:
lw $3,12($fp)
li $2,1
nop
slt $2,$3,$2
beq $2,$0,_for_end_2
nop
lw $3,12($fp)
li $2,1
nop
addu $2,$2,$3
sw $2,12($fp)
b _for_start_1
nop
_for_end_2:
lw $3,12($fp)
li $2,19937
nop
addu $2,$3,$2
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,24($sp)
addiu $sp,$sp,28
jr $31
nop
.end f
