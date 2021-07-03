.globl f
.ent f
f:
addiu $sp,$sp,-40
sw $fp,36($sp)
move $fp,$sp
li $2,0
sw $2,24($fp)
li $2,0
sw $2,20($fp)
_for_start_1:
lw $3,20($fp)
li $2,10
nop
slt $2,$3,$2
beq $2,$0,_for_end_2
nop
lw $3,24($fp)
li $2,1
nop
subu $2,$3,$2
sw $2,24($fp)
lw $3,20($fp)
li $2,1
nop
addu $2,$2,$3
sw $2,20($fp)
b _for_start_1
nop
_for_end_2:
lw $2,24($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,36($sp)
addiu $sp,$sp,40
jr $31
nop
.end f
