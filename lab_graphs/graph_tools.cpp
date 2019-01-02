/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
using namespace std;
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector <Edge> point = graph.getEdges();
    int min = 1000;

    int a = 0;
    for(size_t i=0; i<point.size(); i++){
	if(point[i].weight < min){
		min = point[i].weight;
		a = i;
	}
    }
    graph.setEdgeLabel(point[a].source, point[a].dest, "MIN");
    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */


int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	vector<Vertex> point = graph.getVertices();

	for (size_t i=0; i < point.size(); i++){
		graph.setVertexLabel(point[i], "UNEXPLORED");
	}

	int shortestPath = 0;

	queue<Vertex> q;
	q.push(start);
	graph.setVertexLabel(start, "VISITED");

	while(!q.empty()){
		Vertex v = q.front();
		q.pop();
		vector<Vertex> points_near = graph.getAdjacent(v);

		for(size_t i=0; i<points_near.size(); i++){
			if(graph.getVertexLabel(points_near[i])=="UNEXPLORED"){
				graph.setEdgeLabel(v, points_near[i], "DISCOVERY");				
				graph.setVertexLabel(points_near[i], "VISITED");
				point[points_near[i]] = v;
				q.push(points_near[i]);
			}
			else if(graph.getEdgeLabel(v, points_near[i])=="UNEXPLORED"){
				graph.setEdgeLabel(v, points_near[i], "CROSS");
			}
		}
	}
	while(end != start){
		graph.setEdgeLabel(end, point[end], "MINPATH");
		end = point[end];
		shortestPath++;
	}
	return shortestPath;
}



/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
	vector< Vertex > point = graph.getVertices();
	int point_number = point.size();
	DisjointSets s;
	s.addelements(point_number);

	int a = 0;

	vector< Edge > edges = graph.getEdges();
	int num_points = edges.size();
	sort(edges.begin(), edges.end(), in_order);

	for(int i = 0; i < num_points && a < point_number - 1; i++)
	{
		Vertex u = edges[i].source;
		Vertex v = edges[i].dest;
		if(s.find(u) != s.find(v))
		{
			s.setunion(u, v);
			graph.setEdgeLabel(u, v, "MST");
			a++;
		}
	}
}

bool GraphTools::in_order (Edge u, Edge v) {
    return (u.weight < v.weight);
}

