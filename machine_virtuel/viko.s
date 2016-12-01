.name "viko"
.comment "I'M ALIIIIVE"

# 2 IND, 2 DIR
#ldi %4,%2,r1

# 2 DIR
#ldi %4,r10,r1

# 2 IND, 2 DIR
ldi 124,%2,r1

# 2 IND
ldi 344,r1,r1

#
ldi r1,r2,r3

# 2 DIR
ldi r1,%1,r3


# ld 34, r4

#and r1, r2, r4
#and %1, 4, r4
#and 4, %3, r2
#and %:t, %:t, r5
# sub r1, r2, r3
# live %-1
#ld %0, r2
# xor r1, %15, r19
# ld %0, r1
# ld 4, r5
# ld %:t, r10
# live %-1
# st r1, 11115
# st r1, 11115
# st r1, 11115
# st r1, 411115
# st r1, 11115
# st r1, 11115
# st r1, 11115
# st r1, 11115
# st r1, 11115
# st r1, 11115

# t:
#	live %255
