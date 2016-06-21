#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	char value;
	struct stack *next;
} stack_node_t;

typedef struct {
	stack_node_t *top;
} stack_t;

char pop(stack_t *s);
void push(stack_t *s, char c);

int main(void)
{
	stack_t s = {NULL};
	
	push(&s, 'A');
	push(&s, 'B');
	push(&s, 'C');
	
	while(s.top != NULL) {
		printf("%c\n", pop(&s));
	}
	
	// Push and pop accordingly.
	return 0;
}

char pop(stack_t *s)
{
	stack_node_t *free_node;
	char c;
	
	free_node = s->top;
	c = free_node->value;
	s->top = free_node->next;
	free(free_node);
	
	return c;
}

void push(stack_t *s, char c)
{
	stack_node_t *new_node;
	new_node = (stack_node_t *) malloc(sizeof(stack_node_t));
	new_node->value = c;
	new_node->next = s->top;
	
	s->top = new_node;
}