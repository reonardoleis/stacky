push 10
call fat
hlt

fat:
    jz fat_ret

    push 1
    sub
    dup
    call fat
    pops
    push 1
    add
    restore
    mul
    ret


fat_ret:
    push 1
    ret