#include "graph.h"

int
main(int argc, char **argv)
{
	int choice;
	int val;
	int x, y;
	graph_t graph;
	bool directed;
	int option;

	option = 0; // by default graph is undirected.

	if (argc > 2) {
		printf("Bad Parameters \n");
		printf("./a.out <1 or 0>\n");
		exit(-1);
	} else if (argc == 2) {
		option = atoi(argv[1]);
	}
	directed = (option) ? TRUE : FALSE;

	printf("Initializing a %s graph\n", (directed) ? "Directed" : "Undirected");
	graph_init(&graph, directed);

	while(TRUE) {
		printf("\n1) Add Vertice\n2) Add Edge \n3) Display Graph\n4) BFS\n"
			   "5) DFS \n6) Topological Sort\n7) Exit\n   Choice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Enter Vertice: ");
				scanf("%d", &val);
				graph_add_vertice(&graph, val);
				break;
			case 2:
				printf("Enter Edge: ");
				scanf("%d %d", &x, &y);
				graph_add_edge(&graph, x, y, 0); // weight is 0 for now.
				break;
			case 3:
				graph_print(&graph);
				break;
			case 4: // bfs
				printf("Enter Staring Vertice: ");
				scanf("%d", &val);
				graph_traverse_bfs(&graph, val);
				graph_clear_visited(&graph);
				break;
			case 5: // dfs
				printf("Enter Starting Vertice: ");
				scanf("%d", &val);
				graph_traverse_dfs(&graph, val);
				graph_clear_visited(&graph);
				break;
			case 6:
				graph_clear_visited(&graph);
				graph_topologicalSort(&graph);
				graph_clear_visited(&graph);
				break;
			case 7:
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
