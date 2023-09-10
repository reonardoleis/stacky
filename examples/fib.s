push 10
call fib
hlt
fib:
    jz ret0
    push 1
    sub
    jz ret1_2
    push 1
    sub
    jz ret1_2
    push 2
    add
    push 1
    sub
    dup
    call fib
    pops
    push 1
    sub
    call fib
    restore
    add
    ret
ret0:
    pop
    push 0
    ret
ret1_2:
    pop
    push 1
    ret