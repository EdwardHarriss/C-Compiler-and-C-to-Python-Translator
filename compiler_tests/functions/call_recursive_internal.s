.globl f
.ent f
f:
.frame $fp,32,$31
addiu $sp,$sp,-32
sw $31,28($sp)
sw $fp,24($sp)
move $fp,$sp
.cprestore 16
sw $4,32($fp)
lw $3,32($fp)
li $2,0
nop
subu $2,$2,$3
bne $2,$0,_if_not_1
nop
li $2,0
b _return_0
nop
_if_not_1:
nop
lw $3,32($fp)
li $2,1
nop
subu $2,$3,$2
move $4,$2
jal f
nop
lw $3,32($fp)
nop
addu $2,$3,$2
b _return_0
nop
_return_0:
move $sp,$fp
lw $31,28($sp)
lw $fp,24($sp)
addiu $sp,$sp,32
jr $31
nop
.end f
