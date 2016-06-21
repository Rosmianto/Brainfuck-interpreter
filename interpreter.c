#include <stdio.h>	// for basic I/O operation.
#include <stdlib.h>	// for memory management.

typedef struct stack {
	int value;
	struct stack *next;
} stack_node_t;

typedef struct {
	stack_node_t *top;
} stack_t;

int pop(stack_t *s);
void push(stack_t *s, int i);
char *bracemap(char *program);
void loadBFtoMemory(FILE *handle);
void process(char c);

const int memorySize = 30000;
char *cell;
int currentCell = 0;
int InstructionPointer = 0;
int i, charCount;
FILE *hInput;		// Handle to File object.
char *programArray;	// Cleaned up Brainfuck program.
char *braces;		// Storage of braces pair location.
char *bracesStack;	// temporary array for braces stack.
char _temp;

int main(int argc, char *argv[])
{
	// Make sure file path always be specified.
	if(argc < 2)
		return 0;
	
	cell = calloc(memorySize, sizeof(char));
	
	hInput = fopen(argv[1], "r");
	
	loadBFtoMemory(hInput);
		
	braces = bracemap(programArray);
	
	while(InstructionPointer < charCount)
	{
		process(programArray[InstructionPointer]);
		InstructionPointer++;
	}
	
	// printf("\n");
	
	// for(i = 0; i < 20; i++)
		// printf("%d|", cell[i]);
	
	// printf("\n");
	
	free(programArray);
	fclose(hInput);	
	return 0;
}

char *bracemap(char *program)
{
	int i, start;
	char *temp = calloc(charCount, sizeof(char));	
	stack_t tempStack = {NULL};
	
	for(i = 0; i < charCount; i++)
	{
		if(programArray[i] == '[')
		{
			push(&tempStack, i);
			start = i;
		}			
		else if(programArray[i] == ']')
		{
			int start = pop(&tempStack);
			temp[start] = i;
			temp[i] = start;
		}
	}
	return temp;
}

void process(char c)
{
	switch(c)
	{
		case '+':
			cell[currentCell]++;
			break;
		case '-':
			cell[currentCell]--;
			break;
		case '>':
			currentCell++;
			break;
		case '<':
			currentCell--;
			break;
		case '.':
			printf("%c", cell[currentCell]);
			break;
		case ',':
			cell[currentCell] = (char)getchar();
			break;
		case '[':
			InstructionPointer = (cell[currentCell] == 0) ? braces[InstructionPointer] : (InstructionPointer);
			break;
		case ']':
			InstructionPointer = (cell[currentCell] == 0) ? (InstructionPointer) : braces[InstructionPointer];
			break;
		default:	// Ignore other characters.
			break;	
	}
}

void loadBFtoMemory(FILE *handle){
	char c;
	charCount = 0;
	programArray = (char*) malloc((charCount + 1) * sizeof(char));
	if(programArray == NULL)
		printf("Memory allocation failed.");
	else
	{
		c = fgetc(hInput);	
		while(c != EOF)
		{
			switch(c)
			{
				case '+':
				case '-':
				case '>':
				case '<':
				case '.':
				case ',':
				case '[':
				case ']':					
					programArray[charCount++] = c;
					realloc(programArray, (charCount + 1) * sizeof(char));					
				default:
					break;
			}
			c = (char)fgetc(hInput);
		}
	}
}

int pop(stack_t *s){
	stack_node_t *free_node;
	int c;
	
	free_node = s->top;
	c = free_node->value;
	s->top = free_node->next;
	free(free_node);
	
	return c;
}

void push(stack_t *s, int c){
	stack_node_t *new_node;
	new_node = (stack_node_t *) malloc(sizeof(stack_node_t));
	new_node->value = c;
	new_node->next = s->top;
	
	s->top = new_node;
}