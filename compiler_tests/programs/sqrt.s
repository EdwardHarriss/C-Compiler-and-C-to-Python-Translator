.globl bsqrt
.ent bsqrt
bsqrt:
addiu $sp,$sp,-32
sw $fp,28($sp)
move $fp,$sp
sw $4,32($fp)
sw $5,36($fp)
sw $6,40($fp)
_while_start_1:
lw $3,32($fp)
li $2,1
nop
addu $2,$2,$3
lw $2,36($fp)
nop
slt $2,$3,$2
beq $2,$0,_while_end_2
nop
lw $3,0($fp)
lw $2,0($fp)
nop
mult $3,$2
mflo $2
sw $2,16($fp)
lw $3,16($fp)
lw $2,40($fp)
nop
slt $2,$3,$2
beq $2,$0,_if_not_3
nop
lw $2,0($fp)
nop
sw $2,32($fp)
_if_not_3:
lw $2,0($fp)
nop
sw $2,36($fp)
b _while_start_1
nop

_while_end_2:
lw $3,32($fp)
lw $2,32($fp)
nop
mult $3, $2
mflo $2
lw $2,40($fp)
nop
slt $2,$3,$2
beq $2,$0,_if_not_4
nop
lw $2,36($fp)
b _return_0
nop
_if_not_4:
lw $2,32($fp)
b _return_0
nop
_return_0:
move $sp,$fp
lw $fp,28($sp)
addiu $sp,$sp,32
jr $31
nop
.end bsqrt
