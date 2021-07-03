.globl g
.ent g
g:
addiu $sp,$sp,-16
sw $fp,12($sp)
move $fp,$sp
sw $4,16($fp)
lw $2,16($fp)
li $3,1
beq $2,$3,_case_1
nop
li $3,2
beq $2,$3,_case_2
nop
b _return_0
nop
_case_1:
li $2,10
b _return_0
nop
_case_2:
li $2,11
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,12($sp)
addiu $sp,$sp,16
jr $31
nop
.end g
