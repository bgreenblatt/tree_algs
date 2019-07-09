#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int val;
	int visited;
	struct node *left;
	struct node *right;
};

struct stack_node {
	void *val;
	struct stack_node *next;
};

int should_print = 0;

int insert_tree(struct node **root, int val) {
	struct node *temp = NULL;
	struct node *traverser = NULL;
	struct node *parent = NULL;

	temp = calloc(1, sizeof(struct node));
	if (temp == NULL) {
		printf("malloc failed\n");
		return -1;
	}
	printf("inserting %d\n", val);
	temp->val = val;
	if (*root == NULL) {
		*root = temp;
		return 0;
	}
	traverser = *root;
	while (traverser) {
		parent = traverser;
		if (val > traverser->val) {
			traverser = traverser->right;
		} else {
			traverser = traverser->left;
		}
	}
	if (val > parent->val) {
		parent->right = temp;
	} else {
		parent->left = temp;
	}
	return 0;
}

void postorder(struct node *temp) {
   if (temp != NULL) {
      postorder(temp->left);
      postorder(temp->right);
      printf("%d\n", temp->val);
   }
}

void preorder(struct node *temp) {
   if (temp != NULL) {
      printf("%d\n", temp->val);
      preorder(temp->left);
      preorder(temp->right);
   }
}

void* pop(struct stack_node **st);
void* peek(struct stack_node *st);
int push(struct stack_node **st, void *n);

int insert_queue(struct stack_node **front, struct stack_node **rear, void *n);
void* remove_queue(struct stack_node **front, struct stack_node **rear);
void* peek_queue(struct stack_node *front);

void visit_nodes_post(struct node *root) {
	struct stack_node *st = NULL;
	struct stack_node *vnode = NULL;
	struct node *tnode = NULL;
	if (NULL == root) {
		return;
	}
	push(&st, root);
	while (st != NULL) {
		vnode = peek(st);
		tnode = vnode->val;
		if (1 == tnode->visited) {
			pop(&st);
			printf("%d\n", tnode->val);
		} else {
			vnode = peek(st);
			tnode = vnode->val;
			if (tnode->right != NULL) {
				push(&st, tnode->right);
			}
			if (tnode->left != NULL) {
				push(&st, tnode->left);
			}
			tnode->visited = 1;
		}
	}
}

void visit_nodes_pre(struct node *root) {
	struct stack_node *st = NULL;
	struct stack_node *vnode = NULL;
	struct node *tnode = NULL;
	if (NULL == root) {
		return;
	}
	push(&st, root);
	while (st != NULL) {
		vnode = pop(&st);
		tnode = vnode->val;
		printf("%d\n", tnode->val);
		if (tnode->right != NULL) {
			push(&st, tnode->right);
		}
		if (tnode->left != NULL) {
			push(&st, tnode->left);
		}
	}
}

void visit_nodes_bfs(struct node *root) {
	struct stack_node *front = NULL;
	struct stack_node *rear = NULL;
	struct stack_node *vnode = NULL;
	struct node *tnode = NULL;
	if (NULL == root) {
		return;
	}
	insert_queue(&front, &rear, root);
	while (front != NULL) {
		vnode = remove_queue(&front, &rear);
		tnode = vnode->val;
		printf("%d\n", tnode->val);
		if (tnode->left != NULL) {
			insert_queue(&front, &rear, tnode->left);
		}
		if (tnode->right != NULL) {
			insert_queue(&front, &rear, tnode->right);
		}
	}
}

void visit_nodes(struct node *root) {
	struct stack_node *st = NULL;
	struct stack_node *vnode = NULL;
	struct node *pnode = root;
	struct node *tnode = NULL;

	while (true) {
		if (pnode) {
			push(&st, pnode);
			pnode = pnode->left;
		} else {
			if (st) {
				vnode = pop(&st);
				tnode = vnode->val;
				pnode = tnode->right;
			        printf("%d\n", tnode->val);
				free(vnode);
			} else {
				break;
			}
		}
	}
}

int push(struct stack_node **st, void *n) {
	struct stack_node *temp = NULL;
	struct node *t_out = NULL;

	temp = malloc(sizeof(struct stack_node));
	if (temp == NULL) {
		printf("malloc failed\n");
		return -1;
	}
	t_out = n;
	if (should_print) {
		printf("inserting %d\n", t_out->val);
	}
	temp->val = n;
	temp->next = *st;
	*st = temp;
	return 0;
}

void* pop(struct stack_node **st) {
	void *temp;
	if (NULL == *st) {
		printf("stack empty\n");
		return NULL;
	}
	temp = *st;
	*st = (*st)->next;
	return temp;
}

void* peek(struct stack_node *st) {
	if (NULL == st) {
		printf("stack empty\n");
		return NULL;
	}
	return st;
}

int insert_queue(struct stack_node **front, struct stack_node **rear, void *n) {
	struct stack_node *temp = NULL;
	struct node *t_out = NULL;

	temp = malloc(sizeof(struct stack_node));
	if (temp == NULL) {
		printf("malloc failed\n");
		return -1;
	}
	t_out = n;
	if (should_print) {
		printf("inserting %d\n", t_out->val);
	}
	temp->val = n;
	temp->next = NULL;
	if (NULL == *rear) {
		*rear = temp;
		*front = temp;
	} else {
		(*rear)->next = temp;
		*rear = temp;
	}
	return 0;
}

void* remove_queue(struct stack_node **front, struct stack_node **rear) {
	struct stack_node *temp = NULL;

	if (NULL == front) {
		printf("queue empty\n");
		return NULL;
	}
	temp = *front;
	if (NULL != *front) {
		*front = temp->next;
	}
	if ((NULL != temp) && (NULL == temp->next)) {
		*rear = NULL;
	}
	return temp;
}

void* peek_queue(struct stack_node *front) {
	if (NULL == front) {
		printf("queue empty\n");
		return NULL;
	}
	return front;
}

int main(int argc, char* argv[]) {
	struct node t1 = {0, 0, NULL, NULL};
	struct node t2 = {2, 0, NULL, NULL};
	struct node t3 = {1, 0, NULL, NULL};
	struct node t4 = {5, 0, NULL, NULL};
	struct node t5 = {9, 0, NULL, NULL};
	struct stack_node *st = NULL;
	struct stack_node *front = NULL;
	struct stack_node *rear = NULL;
	struct stack_node *st_out = NULL;
	struct node *t_out = NULL;
	struct node *root = NULL;

	printf("stack test\n");
	should_print = 1;
	
	push(&st, &t1);
	push(&st, &t2);
	push(&st, &t3);
	push(&st, &t4);
	push(&st, &t5);

	while (1) {
		st_out = pop(&st);
		if (st_out) {
			t_out = st_out->val;
			printf("popped val is %d\n", t_out->val);
		} else {
			break;
		}
	}
	should_print = 0;
	printf("tree test\n");
	for (int i =  0; i < 16; i += 3) {
		insert_tree(&root, i % 7);
	}
	insert_tree(&root, 7);
	insert_tree(&root, -7);
	printf("inorder iterative start\n");
	visit_nodes(root);
	printf("inorder iterative end\n\n");
	printf("postorder recursive start\n");
	postorder(root);
	printf("postorder recursive end\n\n");
	printf("postorder iterative start\n");
	visit_nodes_post(root);
	printf("postorder iterative end\n\n");
	printf("preorder recursive start\n");
	preorder(root);
	printf("preorder recursive end\n\n");
	printf("preorder iterative start\n");
	visit_nodes_pre(root);
	printf("preorder iterative end\n\n");

	printf("queue test\n");
	
	should_print = 1;
	insert_queue(&front, &rear, &t1);
	insert_queue(&front, &rear, &t2);
	insert_queue(&front, &rear, &t3);
	insert_queue(&front, &rear, &t4);
	insert_queue(&front, &rear, &t5);

	while (1) {
		st_out = remove_queue(&front, &rear);
		if (st_out) {
			t_out = st_out->val;
			printf("de-queued val is %d\n", t_out->val);
		} else {
			break;
		}
	}
	should_print = 0;

	printf("bfs iterative start\n");
	visit_nodes_bfs(root);
	printf("bfs iterative end\n\n");
}
