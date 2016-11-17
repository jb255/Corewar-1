.name "zork"
.comment "I'M ALIIIIVE"

entry:
		ld %255, r2
		st r2, 256
		st r2, 511
		st r2, 513
l2:		
		sti r1, %:live, %1
		and r1, %1, r1

live:	
		live %1
