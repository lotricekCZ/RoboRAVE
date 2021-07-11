/*
 * travel_node.hpp
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

#ifndef TRAVEL_NODE_HPP
#define TRAVEL_NODE_HPP

class travel_node {
	public:
		coordinates coords;
		unsigned_b id = 0;
		//~ decimal_n pheromones = 0;
		
		travel_node(unsigned_b, coordinates);

		std::vector<std::pair<decimal_n, travel_node*>> connected;
		static std::vector<travel_node> convert(std::vector<coordinates>&);
		bool operator == (const travel_node & rhs){
			return this -> id == rhs.id || this -> coords == rhs.coords;
			}
			
		bool operator != (const travel_node & rhs){
			return (this -> id != rhs.id) && !(this -> coords == rhs.coords);
			}
			
		std::pair<decimal_n, travel_node*> operator [] (const unsigned_b in){
			for(auto i: connected)
				if(i.second -> id == in)
					return i;
			return std::make_pair(-1, nullptr);
			}
			
		bool is_connected(unsigned_b id){
			for(auto a: connected){
				if(a.second -> id == id)
					return true;
				}
			return false;
			}
			
		void connect(travel_node *conn){connected.push_back(std::make_pair(conn-> coords.get_distance(this -> coords), conn));}
};

#endif
