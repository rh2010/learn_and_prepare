#include "graph.h"

int
main(int argc, char **argv)
{
	int choice;
	int val;
	int x, y;
	graph_t graph;

	graph_init(&graph, FALSE);

	while(TRUE) {
		printf("\n1) Add Vertice\n2) Add Edge \n3) Display Graph\n4) BFS\n"
			   "5) DFS \n6)Exit\nChoice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Enter Vertice: ");
				scanf("%d", &val);
				graph_add_vertice(&graph, val);
				break;
			case 2:
				printf("Enter Edge: ");
				scanf("%d", &x);
				scanf("%d", &y);
				graph_add_edge(&graph, x, y, 0); // weight is 0 for now.
				break;
			case 3:
				graph_print(&graph);
				break;
			case 4: // bfs
				graph_traverse_bfs(&graph);
				graph_clear_visited(&graph);
				break;
			case 5: // dfs
				graph_traverse_dfs(&graph);
				graph_clear_visited(&graph);
				break;
			case 6:
				graph_uninit(&graph);
				printf("Done, exiting ...\n");
				exit(0);
			default:
				printf("Wrong choice\n");
				break;
		}
	}
	return (0);
}
