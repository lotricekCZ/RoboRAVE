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
		: id(id), previous(nullptr), distance_start(std::numeric_limits<decimal_n>::infinity()), coords(&c) {
	}

		
	public:
	//~ char id;
	bool is_first = false;
	unsigned_b id;
	dijk_node* previous;
	decimal_n distance_start;
};

class edge {
	public:
	edge(dijk_node* dijk_node1, dijk_node* dijk_node2, decimal_n distance)
		: dijk_node1(dijk_node1), dijk_node2(dijk_node2), distance(distance) {
		
	}
	bool connects(dijk_node* dijk_node1, dijk_node* dijk_node2) {
		return (
			(dijk_node1 == this -> dijk_node1 &&
			 dijk_node2 == this -> dijk_node2) ||
			(dijk_node1 == this -> dijk_node2 &&
			 dijk_node2 == this -> dijk_node1));
	}
	
	bool has(dijk_node* dijk_node1) { /// Checks if such node is being connected via this route
		return (dijk_node1 == this -> dijk_node1 || dijk_node1 == this -> dijk_node2);
	}
	
	dijk_node* other(dijk_node* dijk_node1) { /// Checks if such node is being connected via this route
		return ((dijk_node1 == this -> dijk_node1)? this -> dijk_node2: (dijk_node1 == this -> dijk_node2)? \
				this -> dijk_node1 : nullptr /* god be with us if that happen*/);
	}

	public:
	dijk_node* dijk_node1;
	dijk_node* dijk_node2;
	decimal_n distance;
};

class dijkstra {
	public:
		dijkstra(map &m){
			this -> m = &m;
			}
			
		map* m;
		std::vector<dijk_node> nodes;
		std::vector<dijk_node*> p_nodes;
		std::vector<edge> edges;
		std::vector<edge*> p_edges;
		
		std::vector<dijk_node> generate_nodes(std::vector<coordinates>& coords, coordinates start);
		std::vector<dijk_node*> generate_node_pointers(std::vector<dijk_node>& dijk_nodes);
		std::vector<edge> generate_edges(std::vector<dijk_node>& nodes, map& m);
		std::vector<edge*> generate_edge_pointers(std::vector<edge>& nodes);
		std::vector<edge> connected_edges(dijk_node* d_node, std::vector<edge*> edges);
		
		dijk_node* extract_smallest(std::vector<dijk_node*>& dijk_nodes, unsigned_b* position = nullptr, bool erase = false);
		dijk_node* add_smallest(dijk_node* smallest, std::vector<dijk_node>& dijk_nodes);
		
		std::vector<dijk_node> dijkstras(std::vector<dijk_node*>& p_nodes, std::vector<edge*>& p_edges);
		
		bool collides(wall w, coordinates start, coordinates end);
		bool collides_nowhere(map &m, coordinates start, coordinates end);
		std::vector<coordinates> print_shortest_route(dijk_node* destination);
};


#endif
