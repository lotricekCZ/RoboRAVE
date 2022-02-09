/*
 * chat.cpp
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

#include "chat.hpp"


chat::chat(){
	
	}



bool chat::run(steady now){
	//~ while(){}
	for(unsigned_b i = 0; i < input_queue.size(); i++)
		for(auto &q: output_queue)
			if(answers_query(input_queue.at(i), q)){
				q.answer(input_queue.at(i));
				input_queue.erase(input_queue.begin() + i--);
				}
	
	}



bool chat::answers_query(message m, message_pair mp){
	return true;
	}
