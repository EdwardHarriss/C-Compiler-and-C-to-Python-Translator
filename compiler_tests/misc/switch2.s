.globl g
.ent g
g:
addiu $sp,$sp,-24
sw $fp,20($sp)
move $fp,$sp
sw $4,24($fp)
li $2,0
sw $2,8($fp)
lw $2,24($fp)
li $3,0
beq $2,$3,_case_1
nop
li $3,2
beq $2,$3,_case_2
nop
li $3,1
beq $2,$3,_case_3
nop
b _default_4
nop
b _return_0
nop
_case_1:
li $2,1
sw $2,8($fp)
b _return_0
nop
_case_2:
li $2,2
sw $2,8($fp)
_case_3:
lw $3,8($fp)
li $2,1
nop
addu $2,$2,$3
sw $2,8($fp)
b _return_0
nop
_default_4:
lw $3,24($fp)
li $2,1
nop
addu $2,$2,$3
sw $2,8($fp)
lw $2,8($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,20($sp)
addiu $sp,$sp,24
jr $31
nop
.end g
