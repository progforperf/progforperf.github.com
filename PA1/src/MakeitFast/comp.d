
comp.o:     file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <register_functions>:
   0:	be 00 00 00 00       	mov    $0x0,%esi
   5:	bf 00 00 00 00       	mov    $0x0,%edi
   a:	e9 00 00 00 00       	jmpq   f <register_functions+0xf>
   f:	90                   	nop    

0000000000000010 <f>:
  10:	01 fe                	add    %edi,%esi
  12:	48 83 ec 08          	sub    $0x8,%rsp
  16:	83 e6 01             	and    $0x1,%esi
  19:	f2 0f 11 04 24       	movsd  %xmm0,(%rsp)
  1e:	74 32                	je     52 <f+0x42>
  20:	8d 47 01             	lea    0x1(%rdi),%eax
  23:	f2 0f 10 05 00 00 00 	movsd  0(%rip),%xmm0        # 2b <f+0x1b>
  2a:	00 
  2b:	f2 0f 2a c8          	cvtsi2sd %eax,%xmm1
  2f:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
  33:	e8 00 00 00 00       	callq  38 <f+0x28>
  38:	f2 0f 58 05 00 00 00 	addsd  0(%rip),%xmm0        # 40 <f+0x30>
  3f:	00 
  40:	f2 0f 10 0c 24       	movsd  (%rsp),%xmm1
  45:	48 83 c4 08          	add    $0x8,%rsp
  49:	f2 0f 5e c8          	divsd  %xmm0,%xmm1
  4d:	66 0f 28 c1          	movapd %xmm1,%xmm0
  51:	c3                   	retq   
  52:	8d 47 01             	lea    0x1(%rdi),%eax
  55:	f2 0f 10 05 00 00 00 	movsd  0(%rip),%xmm0        # 5d <f+0x4d>
  5c:	00 
  5d:	f2 0f 2a c8          	cvtsi2sd %eax,%xmm1
  61:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
  65:	e8 00 00 00 00       	callq  6a <f+0x5a>
  6a:	f2 0f 59 04 24       	mulsd  (%rsp),%xmm0
  6f:	48 83 c4 08          	add    $0x8,%rsp
  73:	c3                   	retq   
  74:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  7a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000000080 <superslow>:
  80:	41 56                	push   %r14
  82:	41 55                	push   %r13
  84:	41 54                	push   %r12
  86:	55                   	push   %rbp
  87:	48 89 fd             	mov    %rdi,%rbp
  8a:	53                   	push   %rbx
  8b:	48 83 ec 10          	sub    $0x10,%rsp
  8f:	8b 47 08             	mov    0x8(%rdi),%eax
  92:	85 c0                	test   %eax,%eax
  94:	0f 8e c7 00 00 00    	jle    161 <superslow+0xe1>
  9a:	45 31 ed             	xor    %r13d,%r13d
  9d:	45 8d 75 01          	lea    0x1(%r13),%r14d
  a1:	45 89 ec             	mov    %r13d,%r12d
  a4:	31 db                	xor    %ebx,%ebx
  a6:	eb 5c                	jmp    104 <superslow+0x84>
  a8:	f2 41 0f 2a c6       	cvtsi2sd %r14d,%xmm0
  ad:	f2 0f 10 0d 00 00 00 	movsd  0(%rip),%xmm1        # b5 <superslow+0x35>
  b4:	00 
  b5:	f2 0f 5e c8          	divsd  %xmm0,%xmm1
  b9:	66 0f 28 c1          	movapd %xmm1,%xmm0
  bd:	e8 00 00 00 00       	callq  c2 <superslow+0x42>
  c2:	f2 0f 58 05 00 00 00 	addsd  0(%rip),%xmm0        # ca <superslow+0x4a>
  c9:	00 
  ca:	f2 0f 10 4c 24 08    	movsd  0x8(%rsp),%xmm1
  d0:	f2 0f 5e c8          	divsd  %xmm0,%xmm1
  d4:	f2 0f 11 0c 24       	movsd  %xmm1,(%rsp)
  d9:	89 da                	mov    %ebx,%edx
  db:	44 89 ee             	mov    %r13d,%esi
  de:	48 89 ef             	mov    %rbp,%rdi
  e1:	e8 00 00 00 00       	callq  e6 <superslow+0x66>
  e6:	f2 0f 59 04 24       	mulsd  (%rsp),%xmm0
  eb:	89 da                	mov    %ebx,%edx
  ed:	44 89 ee             	mov    %r13d,%esi
  f0:	48 89 ef             	mov    %rbp,%rdi
  f3:	83 c3 01             	add    $0x1,%ebx
  f6:	41 83 c4 01          	add    $0x1,%r12d
  fa:	e8 00 00 00 00       	callq  ff <superslow+0x7f>
  ff:	39 5d 08             	cmp    %ebx,0x8(%rbp)
 102:	7e 40                	jle    144 <superslow+0xc4>
 104:	89 da                	mov    %ebx,%edx
 106:	44 89 ee             	mov    %r13d,%esi
 109:	48 89 ef             	mov    %rbp,%rdi
 10c:	e8 00 00 00 00       	callq  111 <superslow+0x91>
 111:	41 f6 c4 01          	test   $0x1,%r12b
 115:	f2 0f 11 44 24 08    	movsd  %xmm0,0x8(%rsp)
 11b:	75 8b                	jne    a8 <superslow+0x28>
 11d:	f2 41 0f 2a c6       	cvtsi2sd %r14d,%xmm0
 122:	f2 0f 10 0d 00 00 00 	movsd  0(%rip),%xmm1        # 12a <superslow+0xaa>
 129:	00 
 12a:	f2 0f 5e c8          	divsd  %xmm0,%xmm1
 12e:	66 0f 28 c1          	movapd %xmm1,%xmm0
 132:	e8 00 00 00 00       	callq  137 <superslow+0xb7>
 137:	f2 0f 59 44 24 08    	mulsd  0x8(%rsp),%xmm0
 13d:	f2 0f 11 04 24       	movsd  %xmm0,(%rsp)
 142:	eb 95                	jmp    d9 <superslow+0x59>
 144:	8b 45 08             	mov    0x8(%rbp),%eax
 147:	41 83 c5 01          	add    $0x1,%r13d
 14b:	44 39 e8             	cmp    %r13d,%eax
 14e:	7e 11                	jle    161 <superslow+0xe1>
 150:	85 c0                	test   %eax,%eax
 152:	0f 8f 45 ff ff ff    	jg     9d <superslow+0x1d>
 158:	41 83 c5 01          	add    $0x1,%r13d
 15c:	44 39 e8             	cmp    %r13d,%eax
 15f:	7f ef                	jg     150 <superslow+0xd0>
 161:	48 83 c4 10          	add    $0x10,%rsp
 165:	5b                   	pop    %rbx
 166:	5d                   	pop    %rbp
 167:	41 5c                	pop    %r12
 169:	41 5d                	pop    %r13
 16b:	41 5e                	pop    %r14
 16d:	c3                   	retq   
