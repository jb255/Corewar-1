.name "viko"
.comment "I'M ALIIIIVE"

test:
	# ld %11, r2
	# ld %12, r3
	# sti r1, %:save, %1
	# st r1, 500
	and 12, %11, r4
	st r4, 500
	xor 12, %11, r5
	st r5, 500
	or 12, %11, r6
	st r6, 500
# save:
		# live %1
	# zjmp %:test
