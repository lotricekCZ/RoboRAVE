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


std::vector<dijk_node> dijkstra::dijkstras(std::vector<dijk_node*>& p_nodes, std::vector<edge*>& p_edges) {
	std::vector<dijk_node> out;
	dijk_node* smallest = nullptr;
	dijk_node* smallest_out = nullptr;
	unsigned_b smallest_index = 0;
	do{
		smallest = extract_smallest(p_nodes, &smallest_index);
		//~ std::cout << " velikost: "  << p_nodes.size() << std::endl;
		smallest_out = add_smallest(smallest, out);
		std::vector<edge> edges_connected = connected_edges(smallest, p_edges);
		//~ std::cout << "pocet v setu: " << edges_connected.size() << std::endl;
		for(edge e: edges_connected){
			//~ std::cout << "tato edge spojuje " << e.dijk_node1 -> id << " s " << e.dijk_node2 -> id << std::endl;
			dijk_node* other = e.other(smallest);
			//~ std::cout << other -> distance_start << " > "  << e.distance << " + " << smallest -> distance_start << std::endl;
			if(other -> distance_start > (e.distance + smallest -> distance_start)){
				//~ std::cout << " dojde ke změně! "  << e.distance << " + " << smallest -> distance_start << " = " <<  e.distance + smallest -> distance_start << std::endl;
				/// sets the other ones start distance
				other -> distance_start = e.distance + smallest -> distance_start;
				/// sets to smallest_out since it's a pointer that will be soon no longer valid
				other -> previous = smallest_out; 
				}
			}
		//~ std::cout << "konec pro spoje z " << smallest -> id << std::endl << std::endl;
		p_nodes.erase(p_nodes.begin() + smallest_index);
		} while(p_nodes.size() != 0 /*&& p_edges.size() != 0*/);
	return out;
	}



std::vector<dijk_node> dijkstra::generate_nodes(std::vector<coordinates>& coords, coordinates start){
	unsigned_b size = coords.size();
	std::vector<dijk_node> nodes;
	for(unsigned_b i = 0; i < size; i++){
		nodes.push_back(dijk_node(i, coords[i]));
		if(coords[i] == start){
			//~ std::cout << "start " << nodes[i].id << nodes[i].coords -> print() << std::endl;
			nodes[i].distance_start = 0;
			nodes[i].is_first = true;
			}
		}
	return nodes;
	}

std::vector<dijk_node*> dijkstra::generate_node_pointers(std::vector<dijk_node>& dijk_nodes){
	std::vector<dijk_node*> pointers;
	for(auto &a: dijk_nodes){
		pointers.push_back(&a);
		}
	return pointers;
	}

std::vector<edge> dijkstra::generate_edges(std::vector<dijk_node>& nodes, map& m){
	std::vector<edge> edges;
	unsigned_b size = nodes.size();
	for(unsigned_b i = 0; i < size; i++){
		for(unsigned_b o = i ; o < size; o++){
			if(collides_nowhere(m, *nodes[i].coords, *nodes[o].coords) && (nodes[o].id != nodes[i].id) ){
				//~ std::cout << "Edge z " << nodes[i].coords -> print() << " do " << nodes[o].coords -> print() << "\tVZNIKA, delka\t" << nodes[o].coords -> get_distance(*nodes[i].coords) << std::endl;
				edges.push_back(edge(&nodes[i], &nodes[o], nodes[i].coords -> get_distance(*nodes[o].coords)));
				}
				//~ else{
					//~ std::cout << "Edge z " << nodes[i].coords -> print() << " do " << nodes[o].coords -> print() << "\tNEVZNIKA" << std::endl;					
					//~ }
			}
		}
	std::cout << "Pocet hran: " << edges.size() << std::endl;
	return edges;
	}

std::vector<edge*> dijkstra::generate_edge_pointers(std::vector<edge>& edges){
	std::vector<edge*> pointers;
	for(auto &a: edges){
		pointers.push_back(&a);
		}
	return pointers;
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

//~ #define DEBUG_DIJK

std::vector<coordinates> dijkstra::print_shortest_route(dijk_node* destination) {
	std::vector<coordinates> coords;
	dijk_node* previous = destination;
	//~ std::cout << "distance from start: " << destination -> distance_start << std::endl;
	do {
		coords.push_back(*previous -> coords);
		#ifdef DEBUG_DIJK
			std::cout << previous -> id << " " << previous -> coords -> print() << std::endl;
		#endif 
		previous = previous -> previous;
	} while (!(previous -> is_first));
	
	std::cout << std::endl;
	return coords;
}


dijk_node* dijkstra::add_smallest(dijk_node* smallest, std::vector<dijk_node>& dijk_nodes){
	dijk_nodes.push_back(*smallest);
	return &dijk_nodes[dijk_nodes.size() -1];
	}

dijk_node* dijkstra::extract_smallest(std::vector<dijk_node*>& p_dijk_nodes, unsigned_b* position, bool erase) {
	unsigned_b size = p_dijk_nodes.size();
	if (size == 0) return nullptr;
	unsigned_b smallest_position = 0;
	dijk_node* smallest = p_dijk_nodes.at(0);
	for (unsigned_b i = 1; i < size; ++i) {
		dijk_node* current = p_dijk_nodes.at(i);
		if (current -> distance_start <
			smallest -> distance_start) {
			smallest = current;
			smallest_position = i;
		}
	}
	if(position != nullptr){ /// in case I wanted to erase it directly from loop, not using this function
		*position = smallest_position; 
		}
	if(erase){
		p_dijk_nodes.erase(p_dijk_nodes.begin() + smallest_position);
	}
	return smallest;
}

std::vector<edge> dijkstra::connected_edges(dijk_node* d_node, std::vector<edge*> edges){
	std::vector<edge> connected;
	for(unsigned_b e = 0; e < edges.size(); e++){
		if(edges[e] -> has(d_node)){
			connected.push_back(*edges[e]);
			edges.erase(edges.begin() + e--);
			}		
		}
	return connected;
	}


#endif // DIJKSTRA_CPP
