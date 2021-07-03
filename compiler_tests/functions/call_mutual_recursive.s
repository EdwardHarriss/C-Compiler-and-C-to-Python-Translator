.globl r1
.ent r1
r1:
.frame $fp,48,$31
addiu $sp,$sp,-48
sw $31,44($sp)
sw $fp,40($sp)
move $fp,$sp
.cprestore 32
sw $4,48($fp)
lw $3,48($fp)
li $2,0
nop
subu $2,$2,$3
bne $2,$0,_if_not_1
nop
li $2,1
b _return_0
nop
_if_not_1:
lw $3,48($fp)
li $2,1
nop
subu $2,$3,$2
move $4,$2
jal r2
nop
lw $3,48($fp)
li $2,1
nop
subu $2,$3,$2
move $4,$2
jal r2
nop
nop
addu $2,$3,$2
b _return_0
nop
_return_0:
move $sp,$fp
lw $31,44($sp)
lw $fp,40($sp)
addiu $sp,$sp,48
jr $31
nop
.end r1
