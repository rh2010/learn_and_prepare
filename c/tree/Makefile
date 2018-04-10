.PHONY: all clean bst bst2 avl can_be_bst in_post_2_tree splay

all: clean
	gcc -o bst bst.c
	gcc -o avl avl.c
	gcc -o can_be_bst can_be_bst.c
	gcc -o in_post_2_tree in_post_2_tree.c
	gcc -o bst2 binary_search_tree.c
	gcc -o bst bst.c
	gcc -o splay splay_tree.c

splay:
	rm -f splay
	gcc -o splay splay_tree.c

bst:
	rm -f bst
	gcc -o bst bst.c

bst2:
	rm -f bst2
	gcc -o bst2 binary_search_tree.c

avl:
	rm -f avl
	gcc -o avl avl.c

can_be_bst:
	rm -f can_be_bst
	gcc -o can_be_bst can_be_bst.c

in_post_2_tree:
	rm -f in_post_2_tree
	gcc -o in_post_2_tree in_post_2_tree.c

clean:
	rm -f splay
	rm -f bst
	rm -f bst2
	rm -f a.out
	rm -f bst
	rm -f avl
	rm -f can_be_bst
	rm -f in_post_2_tree
