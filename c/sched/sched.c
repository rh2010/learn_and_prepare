/*
 * User space implementation of a branch and bound algorithm
 * (c) Dr. Brian Dean
 *
 *
 * usage:
 *  ./a.out < input_file
 *
 */
#include <stdio.h>

#define UP 0
#define DOWN 1
char *movetype[] = { "Up", "Down" };

#define MAX 100 // maximum value
#define MIN(a,b) ((a)<(b)?(a):(b)) 

// TODO : Make these dynamic
//
int uplist[MAX], upsize;
int downlist[MAX], downsize;
int sol_so_far[MAX*2], sol_len=0;

// print solution
void dump_sol(void)
{
    int i;
    printf ("Solution:\n");
    for (i=0; i<sol_len; i++) printf ("%s\n", movetype[sol_so_far[i]]);
}

// solve for the optimal solution
int solve(int uplen, int downlen, int totalcost, int wherehead, int bestsofar, int curmove)
{
    int sol1, sol2;
    
    printf ("%d %d %d\n", uplen, downlen, totalcost);
    
    if (totalcost >= bestsofar) {
      printf ("Prune!\n");
      return 2000000000;
    }
    
    if (uplen == 0 && downlen == 0) {
        if (curmove != -1)
            sol_so_far[sol_len++] = curmove;
        printf ("Found solution of cost %d\n", totalcost);
        if (totalcost == 180)
            dump_sol();

        if (curmove != -1)
            sol_len--;

        return totalcost;
    }

    if (curmove != -1) {
        sol_so_far[sol_len++] = curmove;
    }

    if (uplen == 0 || (downlen > 0 && uplen > 0 && 
      	     wherehead - downlist[downlen-1] < uplist[uplen-1] - wherehead )) {
        sol1 = solve(uplen, downlen-1, 
      	             totalcost + (wherehead - downlist[downlen-1]) * (uplen+downlen), 
      	             downlist[downlen-1], bestsofar, DOWN);

        bestsofar = MIN(bestsofar, sol1);

        if (uplen > 0) {
            sol2 = solve(uplen-1, downlen, 
                         totalcost + (uplist[uplen-1] - wherehead) * (uplen+downlen), 
                         uplist[uplen-1], bestsofar, UP);
            bestsofar = MIN(bestsofar, sol2);
        }
    } else {
        sol1 = solve(uplen-1, downlen, 
                     totalcost + (uplist[uplen-1] - wherehead) * (uplen+downlen), 
                     uplist[uplen-1], bestsofar, UP);
        bestsofar = MIN(bestsofar, sol1);
        if (downlen > 0) {
            sol2 = solve(uplen, downlen-1, 
                         totalcost + (wherehead - downlist[downlen-1]) * (uplen+downlen), 
                         downlist[downlen-1], bestsofar, DOWN);
            bestsofar = MIN(bestsofar, sol2);
        }
    }
    if (curmove != -1) {
        sol_len--;
    }
    return bestsofar;
}

int main(void)
{
  int i, j, starthead;

  scanf ("%d", &upsize);

  for (i=upsize-1; i>=0; i--) scanf ("%d", &uplist[i]);
  scanf ("%d", &downsize);
  for (i=0; i<downsize; i++) scanf ("%d", &downlist[i]);
  scanf ("%d", &starthead);
  printf ("The optimal solution is: %d\n", 
	  solve(upsize, downsize, 0, 50, 2000000000, -1));
}
