/*
 * dijkstra.cpp
 * 
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP
#include "dijkstra.hpp"


void dijkstra::dijkstras(std::vector<dijk_node*>& nodes, std::vector<edge*>& edges) {
	while (nodes.size() > 0) {
		dijk_node* smallest = extract_smallest(nodes);
		std::vector<dijk_node*> adjacent_nodes = adjacent_remaining_nodes(smallest, nodes, edges);

		const int size = adjacent_nodes.size();
		for (unsigned_b i = 0; i < size; ++i) {
			dijk_node* adjacent = adjacent_nodes.at(i);
			decimal_n dist = distance(smallest, adjacent) +
							 smallest -> distance_start;

			if (dist < adjacent -> distance_start) {
				adjacent -> distance_start = dist;
				adjacent -> previous = smallest;
			}
		}
	}
}

std::vector<dijk_node*> dijkstra::generate_nodes(std::vector<coordinates>& coords, coordinates start){
	unsigned_b size = coords.size();
	std::vector<dijk_node*> nodes;
	dijk_node *node1 = NULL;
	for(unsigned_b i = 0; i < size; i++){
		node1 = new dijk_node(i, coords[i]);
		nodes.push_back(node1);
		if(coords[i] == start){
			nodes[i] -> distance_start = 0;
			}
		}
	return nodes;
	}

bool dijkstra::collides_nowhere(map &m, coordinates start, coordinates end){
	line lin(start, end);
	for(auto w: m._map_walls){
		if(collides(w, start, end))
			return false;
		}
	return true;
}	

bool dijkstra::collides(wall w, coordinates start, coordinates end){
	line lin(start, end);
	for(auto l: w.properties.walls){
		coordinates inters = lin.intersection(l, lin);
		if((lin.on_segment(inters, start, end) && w.inside(inters)) || w.inside(start) || w.inside(end)){
			return true;
		}
	}
	return false;
}

std::vector<edge*> dijkstra::generate_edges(std::vector<dijk_node*>& nodes, map& m){
	std::vector<edge*> edges;
	edge* edge1;
	unsigned_b size = nodes.size();
	for(unsigned_b i = 0; i < size; i++){
		for(unsigned_b o = i+1 ; o < size; o++){
			if(collides_nowhere(m, *nodes[i] -> coords, *nodes[o] -> coords)){
				edge1 = new edge(*nodes[i], *nodes[o], nodes[i] -> coords -> get_distance(*nodes[o] -> coords));
				edges.push_back(edge1);
				
				}
			}
		}
	return edges;
	}

void dijkstra::calculate_edges(){
	edges.clear();
	for(auto i: nodes){
		
		}
	}


std::vector<dijk_node*> dijkstra::adjacent_remaining_nodes(dijk_node* Node, std::vector<dijk_node*>& dijk_nodes, std::vector<edge*>& edges) {
	std::vector<dijk_node*> adjacent_nodes;
	const unsigned_b size = edges.size();
	for (unsigned_b i = 0; i < size; ++i) {
		edge* edge = edges.at(i);
		dijk_node* adjacent = NULL;
		if (edge -> dijk_node1 == Node) {
			adjacent = edge -> dijk_node2;
		} else if (edge -> dijk_node2 == Node) {
			adjacent = edge -> dijk_node1;
		}
		if (adjacent && contains(dijk_nodes, adjacent)) {
			adjacent_nodes.push_back(adjacent);
		}
	}
	return adjacent_nodes;
}


void dijkstra::print_shortest_route(dijk_node* destination) {
	dijk_node* previous = destination;
	std::cout << "distance from start: "
		 << destination -> distance_start << std::endl;
	while (previous) {
		std::cout << previous -> id << " ";
		previous = previous -> previous;
	}
	std::cout << std::endl;
}


bool dijkstra::contains(std::vector<dijk_node*>& dijk_nodes, dijk_node* d_node) {
	const unsigned_b size = dijk_nodes.size();
	for (unsigned_b i = 0; i < size; ++i) {
		if (d_node == dijk_nodes.at(i)) {
			return true;
		}
	}
	return false;
}


decimal_n dijkstra::distance(dijk_node* node1, dijk_node* node2) {
	const unsigned_b size = edges.size();
	for (unsigned_b i = 0; i < size; ++i) {
		edge* edge_o = edges.at(i);
		if (edge_o -> Connects(node1, node2)) {
			return edge_o -> distance;
		}
	}
	return -1;	// should never happen
}


dijk_node* dijkstra::extract_smallest(std::vector<dijk_node*>& dijk_nodes) {
	unsigned_b size = dijk_nodes.size();
	if (size == 0) return NULL;
	decimal_n smallest_position = 0;
	dijk_node* smallest = dijk_nodes.at(0);
	for (unsigned_b i = 1; i < size; ++i) {
		dijk_node* current = dijk_nodes.at(i);
		if (current -> distance_start <
			smallest -> distance_start) {
			smallest = current;
			smallest_position = i;
		}
	}
	dijk_nodes.erase(dijk_nodes.begin() + smallest_position);
	return smallest;
}



#endif // DIJKSTRA_CPP
