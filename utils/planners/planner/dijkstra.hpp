#include <iostream>
#include <vector>
#include <limits>
#include "../../../defines/typedefines.h"


//~ using namespace std;

#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

class dijk_node {
	public:
	coordinates *coords;
	dijk_node(unsigned_b id, coordinates &c)
		: id(id), previous(NULL), distance_start(std::numeric_limits<decimal_n>::infinity()), coords(&c) {
	}

		
	public:
	//~ char id;
	unsigned_b id;
	dijk_node* previous;
	decimal_n distance_start;
};

class edge {
	public:
	edge(dijk_node& dijk_node1, dijk_node& dijk_node2, decimal_n distance)
		: dijk_node1(&dijk_node1), dijk_node2(&dijk_node2), distance(distance) {
		
	}
	bool Connects(dijk_node* dijk_node1, dijk_node* dijk_node2) {
		return (
			(dijk_node1 == this -> dijk_node1 &&
			 dijk_node2 == this -> dijk_node2) ||
			(dijk_node1 == this -> dijk_node2 &&
			 dijk_node2 == this -> dijk_node1));
	}

	public:
	dijk_node* dijk_node1;
	dijk_node* dijk_node2;
	decimal_n distance;
};

class dijkstra{
	public:
		dijkstra(map &m){
			this -> m = &m;
			}
			
		map* m;
		std::vector<dijk_node*> nodes;
		std::vector<edge*> edges;
		
		void dijkstras(std::vector<dijk_node*>& nodes, std::vector<edge*>& edges);
		std::vector<dijk_node*> adjacent_remaining_nodes(dijk_node* Node, std::vector<dijk_node*>& dijk_nodes, std::vector<edge*>& edges);
		std::vector<dijk_node*> generate_nodes(std::vector<coordinates>& dijk_nodes, coordinates start);
		std::vector<edge*> generate_edges(std::vector<dijk_node*>& nodes, map& m);
		bool collides(wall w, coordinates start, coordinates end);
		bool collides_nowhere(map &m, coordinates start, coordinates end);
		void print_shortest_route(dijk_node* destination);
		void calculate_edges();
		bool contains(std::vector<dijk_node*>& dijk_nodes, dijk_node* d_node);
		decimal_n distance(dijk_node* node1, dijk_node* node2);
		dijk_node* extract_smallest(std::vector<dijk_node*>& dijk_nodes);
};


#endif
