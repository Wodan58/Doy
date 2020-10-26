;
;   module  : setebp.s
;   version : 1.2
;   date    : 10/26/20
;
section	.text
;
global setebp
setebp:
	mov	rbp,rdi
	ret
