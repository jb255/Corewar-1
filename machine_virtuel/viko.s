.name "viko"
.comment "I'M ALIIIIVE"

test:
	ld %0, r4
	live %-1
	fork %:test
	zjmp %:test
