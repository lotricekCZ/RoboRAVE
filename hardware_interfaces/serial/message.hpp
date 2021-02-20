/*
 * message.hpp
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
 
#ifndef CHAT_HPP
#define CHAT_HPP

class message
{
	public:
		typedef struct content{
			unsigned receiver:3;
			unsigned sender:3;
			unsigned type:1; //typ zpravy (0 - prikaz, 1 - data, potvrzovac) - data jsou posilana pres UΑRΤ, prikazy pres I2C
			unsigned kind:3;
			unsigned long message_number:22; 
			/* druh zpravy, lze spojit s type 
			 * (0 - pohyb motoru, 1 - posli data 0, 2 - posli data 1, 3 - posli data 2 (vic jich snad nebude),
			 *  4 - natoc foukac, 5 - roztoc foukac, 6 - vypni foukac, 7 - rezervovano) 
			 * a (8 - data0, 9 - data1, 10 - data2, 11 - potvrzovac, 12 - rezervovano, 13 - rezervovano, 14 - rezervovano, 15 - rezervovano)*/
			uint8_t message_space[16]; // prinasi 2^128 moznosti vyuziti (10bitova data po osmi - 80b)
		};
		
		bool decode(uint8_t in[22], content &in);
		void encode(content in, uint8_t &buffer[22]);
		message();
		
	private:
		/* add your private declarations */
};

#endif /* CHAT_HPP */ 
