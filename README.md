# Stacky: A Virtual Stack Machine in C++

Stacky is a simple virtual stack machine implemented in C++. It provides a set of instructions for stack-based computation.

## Usage

Build the project using either of the following commands:

```bash
make build
```

or

```bash
g++ -o stacky main.cpp
```

Run the executable with the following command:

```bash
./stacky <assemble | run | rund> <input_file_path>
```

- `assemble`: Assemble the input file and generate a .bin file.
- `run`: Run the input .bin file and display the output (the top of the stack).
- `rund`: Run the input .bin file in debug mode.

## Available instructions

- `push N`: Pushes the value N onto the stack.
- `pops`: Pops the top of the stack and pushes it onto the pop stack.
- `restore`: Pops the top of the pop stack and pushes it back onto the stack.
- `add`: Pops the two top elements of the stack, adds them, and pushes the result onto the stack.
- `sub`: Pops the two top elements of the stack, subtracts them (top2 - top1), and pushes the result onto the stack.
- `mul`: Pops the two top elements of the stack, multiplies them, and pushes the result onto the stack.
- `div`: Pops the two top elements of the stack, divides them (top2 / top1), and pushes the result onto the stack.
- `jz LABEL`: Jumps to the specified LABEL if the top of the stack is equal to 0.
- `jmp LABEL`: Unconditionally jumps to the specified LABEL.
- `call LABEL`: Calls LABEL as a function, pushing the return point onto the call stack.
- `ret`: Pops the top element of the call stack and sets the program counter (PC) to this value, returning from a function to the saved point.
- `hlt`: Ends the program.
- `pop`: Pops the top element of the stack

## Example
An example program could look like this:

```assembly
push 5
push 3
add
hlt
```

This program pushes the values 5 and 3 onto the stack, adds them, and then ends the program. More examples can be found ![here](https://github.com/reonardoleis/stacky/tree/main/examples).
