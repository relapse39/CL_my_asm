.name "roller"
.comment "ololo"

start:
	sti r2, %:live, %1

live:
    live %0

preend:
	xor %1, %1, r16
	zjmp %:start

end:
