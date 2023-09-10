push 10
call fat
hlt
fat:
    jz fat_ret
    dup
    push 1
    sub
    call fat
    mul
    ret
fat_ret:
    pop
    push 1
    ret