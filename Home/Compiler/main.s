	.file	"main.c"
	.text
	.globl	MAX_SIZE
	.section .rdata,"dr"
	.align 4
MAX_SIZE:
	.long	100
	.text
	.globl	foo
	.def	foo;	.scl	2;	.type	32;	.endef
	.seh_proc	foo
foo:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$3, 16(%rbp)
	je	.L2
	cmpl	$3, 16(%rbp)
	jg	.L3
	cmpl	$2, 16(%rbp)
	je	.L4
	cmpl	$2, 16(%rbp)
	jg	.L3
	cmpl	$0, 16(%rbp)
	je	.L5
	cmpl	$1, 16(%rbp)
	je	.L6
	jmp	.L3
.L5:
	movl	$10, %eax
	jmp	.L7
.L6:
	movl	$20, %eax
	jmp	.L7
.L4:
	movl	$30, %eax
	jmp	.L7
.L2:
	movl	$40, %eax
	jmp	.L7
.L3:
	movl	$-1, %eax
.L7:
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "PI is %.2f\12\0"
.LC1:
	.ascii "Sum is %d\12\0"
.LC2:
	.ascii "Not Defined AGE\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movabsq	$4614253070214989087, %rax
	movq	%rax, %rdx
	movq	%rdx, %xmm0
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	call	func1
	movl	$5, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$3, %ecx
	call	foo
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev3, Built by MSYS2 project) 13.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	func1;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
