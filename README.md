# A stack machine implemented in JavaScript!

## Usage:
Run `node src/index.js <input_file_path>`

## Available instructions:

- `push N`: pushes N into the stack
- `pops`: pops the top of the stack and pushes it into the pop stack
- `restore`: pops the top of the pop stack and pushes it back into the stack
- `add`: pops the 2 top elements of the stack and pushes their sum into the stack
- `sub`: pops the 2 top elements of the stack and pushes their subtraction into the stack (top2 - top1)
- `mul`: pops the 2 top elements of the stack and pushes their multipliaction into the stack
- `jz LABEL`: jumps to LABEL if stack's top is equal to 0
- `jmp LABEL`: unconditionally jumps to LABEL
- `call LABEL`: call LABEL as a function, pushing the return point into the callStack
- `ret`: pops the top element of the callStack and sets the PC to this value, return from a function to the saved point
- `hlt`: ends the program
