.name "lol"
.comment "lol"

start:
	ld %0, r9
	st r1, 6
	live %0
	zjmp %:start
