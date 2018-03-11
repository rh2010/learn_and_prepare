//   @author Aleksandr Muravskii
//   Coursera week 4, assignment 3
//   Update your Homework 2 graph class to
//   add two more methods.
//   Add a constructor that can read in a graph from a file.
//   The file format will be an initial integer that is
//   the node size of the graph and the further values
//   will be integer triples: (i, j, cost).
//   Implement either the Prim or Kruskal Minimum Spanning Tree Algorithm.

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <queue>
#include <utility>
#include <set>
#include <stack>
#include <tuple>
#include <map>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace std;
namespace Prim {using Tuple=tuple <unsigned int, unsigned int, double>;}

// Constructs graph with given number of nodes and 0 edges
// provides methods for making graph structure by adding edges
// allows to construct graph of any density and complexity
// can be used for both directed and undirected graphs.

class Graph
{

    public:

    Graph(unsigned int nodesNumber):EdgeMatrix{nodesNumber,vector <double>(nodesNumber,numeric_limits<double>::quiet_NaN()) }{};

    unsigned int getNodesNumber() const
    {
        return EdgeMatrix.size();
    }

    unsigned int getEdgesNumber() const
    {
        return edgesNumber;
    }

    float getDensity() const
    {
        int nodesNumber = EdgeMatrix.size();
        return static_cast<float>(edgesNumber)/(nodesNumber*(nodesNumber-1)) ;
    }


    bool isAdjacent(const int x, const int y) const
    {
        return (! isnan(EdgeMatrix.at(x).at(y)));

    }

    vector <unsigned int> getNeighbors (const int x) const
    {
        vector <unsigned int> neighbors{};
        unsigned int nodesNumber = EdgeMatrix.size();

        for (unsigned int i=0;i<nodesNumber;i++)
        {
            if (! isnan(EdgeMatrix.at(x).at(i)) ) neighbors.push_back(i);
        }

        return neighbors;
    }


    double getEdgeValue (const int x, const int y) const
    {
        return EdgeMatrix.at(x).at(y);
    }

    double setEdgeValue (const int x, const int y, const double distance)
    {

        if ( isnan(EdgeMatrix.at(x).at(y)) )
        {
            EdgeMatrix.at(x).at(y) = distance;

            edgesNumber++;
        }
        else EdgeMatrix.at(x).at(y) = distance;
        return distance;
    }

    void deleteEdge(const int x, const int y)
    {
        if (! isnan (EdgeMatrix.at(x).at(y)) )
        {
           EdgeMatrix.at(x).at(y) = numeric_limits<double>::quiet_NaN();
           edgesNumber--;
        }


    }

    private:
    vector < vector <double> > EdgeMatrix;
    unsigned int edgesNumber = 0;

};

// provides factory method for making graph by reading
// node pairs and costs values from a file


class GraphMaker
{
    public:
    GraphMaker() = delete;

    static Graph readFromFile(const string pathName)
    {

        ifstream mstDataFile (pathName);
        if ( mstDataFile.fail() )
        {
            cout<<"Error opening "<<pathName<<endl;
            terminate();
        }

        string currentLine;


        getline(mstDataFile,currentLine);
        Graph graph(stoi(currentLine));


        while (getline(mstDataFile,currentLine))
        {
              unsigned int node1,node2;
              double distance;

              istringstream tis(currentLine);
              tis>>node1>>node2>>distance;

              if ( ! isnan (graph.getEdgeValue(node1,node2) ) || node1 == node2 ) continue;

              graph.setEdgeValue(node1,node2,distance);

        }

        return graph;

    }


};

// overloaded "<<" operator for graph structure output
// prints out graph parameters and matrix of edges

ostream& operator<<(ostream& os, const Graph &graph)
{
 unsigned int nodesNumber = graph.getNodesNumber();

   unsigned int temposp=os.precision();
   os.precision(3);

   os<<"nodes "<<nodesNumber<<endl
     <<"density "<<graph.getDensity()<<endl
     <<"edges "<<graph.getEdgesNumber()<<endl;



    for (unsigned int i=0;i<nodesNumber;i++)
        {
            os<<i<<"|";

            for (unsigned int k=0;k<nodesNumber;k++)
            {


                if ( isnan(graph.getEdgeValue(i,k)) ) continue;
                os <<graph.getEdgeValue(i,k) <<"("<<k<<") ";

            }
            os<<endl;
        }

    os.precision(temposp);
    return os;

}


class MST
{

    public:
    MST (const Graph & graph):graph(graph)
    {

    }


    pair <set<Prim::Tuple>,double> computeMST()
    {
        const unsigned int parentIndex=0;
        const unsigned int childIndex =1;
        const unsigned int costIndex  =2;

        struct CompareOperator
        {
            bool operator () (const tuple <unsigned int, unsigned int, double> &t1,
                              const tuple <unsigned int, unsigned int, double> &t2) const
            {
                return  get<costIndex>(t1) > get<costIndex>(t2);
            }

        };

        priority_queue <tuple <unsigned int, unsigned int, double>,
                        vector <tuple <unsigned int, unsigned int, double> >,CompareOperator> priorityQueue;


        Prim::Tuple queueTuple;
        set   <unsigned int> visitedNodes;
        set   <Prim::Tuple> mst;
        pair  <set<Prim::Tuple>,double> result;

        unsigned int currentNode=0;
        unsigned int nodesCount=graph.getNodesNumber();
        double mstCost=0.0;

        mst.clear();
        visitedNodes.clear();

        do
        {

            if ( visitedNodes.insert(currentNode).second )
            {
                if (currentNode !=0)
                   {
                        mst.insert(queueTuple);
                        mstCost+=get<costIndex>(queueTuple);
                   }

                vector <unsigned int> neighborNodes;

                neighborNodes=graph.getNeighbors(currentNode);

                for (unsigned int i=0;i<neighborNodes.size();i++)
                {
                    unsigned int currentNeighbor = neighborNodes.at(i);
                    if (! visitedNodes.count(currentNeighbor) )
                    {
                       priorityQueue.push(
                       make_tuple(currentNode,currentNeighbor,
                                  graph.getEdgeValue(currentNode,currentNeighbor))
                       );
                    }
                }

             }


            queueTuple=priorityQueue.top();
            priorityQueue.pop();

            currentNode = get<childIndex>(queueTuple);


        } while ( (visitedNodes.size()!=nodesCount) && (priorityQueue.size()) );


        if (visitedNodes.size()==nodesCount)
        {
            result=make_pair(mst,mstCost);
        }
        else
        {
            result=make_pair(mst,numeric_limits<double>::quiet_NaN());
        }

        return result;
    }

    private:

    Graph graph;

};


// some tests for future refactoring

void runTest()
{
cout<<"Making test graph"<<endl;
cout<<"\n\t  Test graph"
"\n"
"       (1)-----6----(4)\n"
"      /   \\         / \\\n"
"     /     \\       /   \\\n"
"    3       4     3     1 \n"
"   /         \\   /       \\\n"
"  /           \\ /         \\\n"
" (0)----7---- (3)----1----(5)\n"
"  \\           /           /\n"
"   \\         /           /\n"
"    2       6           1\n"
"     \\     /           /\n"
"      \\   /           /\n"
"       (2)          (6)\n"<<endl;


/*        Test graph

       (1)-----6----(4)
      /   \         / \
     /     \       /   \
    3       4     3     1
   /         \   /       \
  /           \ /         \
 (0)----7---- (3)----1----(5)
  \           /           /
   \         /           /
    2       6           1
     \     /           /
      \   /           /
       (2)          (6)
*/
    const int nodes = 7;
    double averageCost=0.0;
    double currentCost=0.0;
    unsigned int costItemsCount=0;



    Graph testV(nodes);
    testV.setEdgeValue(0,1,3.0);
    testV.setEdgeValue(1,0,3.0);

    testV.setEdgeValue(0,2,2.0);
    testV.setEdgeValue(2,0,2.0);

    testV.setEdgeValue(0,3,7.0);
    testV.setEdgeValue(3,0,7.0);

    testV.setEdgeValue(1,4,6.0);
    testV.setEdgeValue(4,1,6.0);

    testV.setEdgeValue(1,3,4.0);
    testV.setEdgeValue(3,1,4.0);


    testV.setEdgeValue(2,3,6.0);
    testV.setEdgeValue(3,2,6.0);

    testV.setEdgeValue(3,4,3.0);
    testV.setEdgeValue(4,3,3.0);

    testV.setEdgeValue(3,5,1.0);
    testV.setEdgeValue(5,3,1.0);

    testV.setEdgeValue(4,5,1.0);
    testV.setEdgeValue(5,4,1.0);

    testV.setEdgeValue(5,6,1.0);
    testV.setEdgeValue(6,5,1.0);

    cout<<testV<<endl;


    MST mst(testV);

    pair <set<Prim::Tuple>,double> mstResult;

    mstResult=mst.computeMST();
    double testCost=mstResult.second;

    assert (testCost==12);

    cout<<"MST cost"<<" "<<testCost<<endl;

    cout<<"MST tree"<<endl;

    cout<<"node\tnode\tcost"<<endl;
    for (auto i:mstResult.first)
            {
                unsigned int node1;
                unsigned int node2;
                double cost;

                tie(node1,node2,cost)=i;

                cout<<node1<<"\t";
                cout<<node2<<"\t";
                cout<<cost<<" "<<endl;

            }


    cout<<"===all tests OK==="<<endl;


}

int main()
{

    runTest();

    pair <set<Prim::Tuple>,double> mstResult;

    cout<<"\nreading graph from file"<<endl;
    Graph mstv=GraphMaker::readFromFile("mst_data.txt");
    cout<<mstv;

    MST mst(mstv);
    mstResult=mst.computeMST();

    cout<<"MST cost"<<" "<<mstResult.second<<endl;
    cout<<"MST tree"<<endl;

    cout<<"node\tnode\tcost"<<endl;
    for (auto i:mstResult.first)
            {
                unsigned int node1;
                unsigned int node2;
                double cost;

                tie(node1,node2,cost)=i;

                cout<<node1<<"\t";
                cout<<node2<<"\t";
                cout<<cost<<" "<<endl;

            }

    return 0;


}
