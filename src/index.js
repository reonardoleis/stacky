class Tuple {
	constructor(a, b) {
  this.first = a;
  this.second= b;
  }
}

class Stack {
   constructor() {
		this.stack = [];
	}
  
  popN(n) {
  	let popped = [];
    for (let i = 0; i < n; i++) {
    	popped.push(this.stack.pop());
    }
    
    return popped;
  }
  
  push(item) {
  	this.stack.push(item);
  }
 
}

const PUSH = 0;
const SUB = 1;
const JZ  = 2;
const JMP = 3;
const HLT = 5;
const POPS = 7;
const RESTORE = 8;
const ADD = 9;
const CALL = 10;
const RET = 11;
const DUP = 12;
const MUL = 13;

const translation = [];
translation['push'] = PUSH;
translation['sub']  = SUB;
translation['jz'] = JZ;
translation['jmp'] = JMP;
translation['hlt'] = HLT;
translation['pops'] = POPS;
translation['restore'] = RESTORE;
translation['add'] = ADD;
translation['call'] = CALL;
translation['ret'] = RET;
translation['dup'] = DUP;
translation['mul'] = MUL;


const codeToText = [];
codeToText[PUSH] = 'push';
codeToText[SUB] = 'sub';
codeToText[JZ] = 'jz';
codeToText[JMP] = 'jmp';
codeToText[HLT] = 'hlt';
codeToText[POPS] = 'pops';
codeToText[RESTORE] = 'restore';
codeToText[ADD] = 'add';
codeToText[CALL] = 'call';
codeToText[RET] = 'ret';
codeToText[DUP] = 'dup';
codeToText[MUL] = 'mul';

class StackMachine {
	constructor(tupleList) {
  	this.stack = new Stack();
    this.popStack = new Stack();
    this.returnStack = new Stack();
    this.program = tupleList;
    this.pc = 0;
  }
  
  run() {
  	for (this.pc = 0; this.pc < this.program.length; this.pc++) {
    	switch (this.program[this.pc][0]) {
      	case PUSH:
        	this.stack.push(this.program[this.pc][1]);
        break;
        
        case SUB:
        	const [ op1, op2 ] = this.stack.popN(2);
          this.stack.push(op2 - op1);
        break;
      	
        case JZ:
        let [ stackTop ] = this.stack.popN(1);
          if (stackTop == 0) {
          	this.pc = this.program[this.pc][1] - 1;
          } else {
            this.stack.push(stackTop);
          }
          
        break;
        
        case JMP:
        	this.pc = this.program[this.pc][1] - 1;
          break;

        case HLT:
        	this.pc = this.program.length + 1;
        break;

        case POPS:
        {
          let [ stackTop ] = this.stack.popN(1);
          this.popStack.push(stackTop);
        }
        break;

        case RESTORE:
        {
          let [ popStackTop ] = this.popStack.popN(1);
          this.stack.push(popStackTop);
        }
        break;

        case ADD:
        {
          let [ op1, op2 ] = this.stack.popN(2);
          this.stack.push(op1 + op2);
        }
        break;
        
        case CALL:
        {
          this.returnStack.push(this.pc);
          this.pc = this.program[this.pc][1] - 1;
        }
        break;
        case RET:
        {
          let [ retStackTop ] = this.returnStack.popN(1);
          this.pc = retStackTop;
        }
        break;

        case DUP:
        {
          let [ stackTop ] = this.stack.popN(1);
          this.stack.push(stackTop);
          this.stack.push(stackTop);
        }
        break;
        case MUL:
        {
          let [ op1, op2 ] = this.stack.popN(2);
          this.stack.push(op1 * op2);
        }
        break;
      }
    }
    
      
  }
  

}

const isJump = instr => ['jmp', 'jz', 'call'].includes(instr);
const isLabel = line => line.indexOf(':') != -1;

function compile(asm) {
  const labels = [];
  const instructions = asm.split('\n').filter(line => line.length !== 0).map(line => line.replace(/\s\s+/g, ' '));
  const program = [];

  let line = 0;
  for (instruction of instructions) {
    if (isLabel(instruction)) {
      labels[instruction.replace('\n', '').replace('\r', '').replace(':', '').trim()] = line;
      continue;
    } else {
      line++;
    }

  }

  for (instruction of instructions) {
    if (isLabel(instruction)) continue;
    let [ mnemonic, operand ] = instruction.trim().split(' ');
    
    if (isJump(mnemonic)) {
      operand = labels[operand];
    }

    program.push([translation[mnemonic], !isNaN(Number(operand)) ? Number(operand) : operand]);
  }

  return program;
}



const fileName = process.argv[2];
if (!fileName) {
  console.log('Please provide a file name');
  process.exit(1);
}

const program = compile(require('fs').readFileSync(fileName, 'utf-8'));
const stackMachine = new StackMachine(program);
stackMachine.run();
console.log(stackMachine.stack);
