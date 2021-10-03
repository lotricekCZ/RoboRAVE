/*
 * circle.cpp
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

#include "circle.hpp"

#ifndef CIRCLE_CPP
#define CIRCLE_CPP


circle::circle(decimal_n x, decimal_n y, decimal_n r){
	this -> center.x = x;
	this -> center.y = y;
	this -> radius = r;
	}


circle::circle(coordinates c, decimal_n r){
	this -> center = c;
	this -> radius = r;
	}


bool circle::inside(coordinates a){
	return inside(a.x, a.y);
	}

	
bool circle::inside(decimal_n x, decimal_n y){
	return pow(x - center.x, 2) + pow(y - center.y, 2) <= pow(radius, 2);
	}

	
bool circle::is_on(coordinates c){
	return std::abs(pow(c.x - center.x, 2) + pow(c.y - center.y, 2) - pow(radius, 2)) <= 1e-3;
	}

	
std::vector<coordinates> circle::points(){
	return std::vector<coordinates>();
	}


std::vector<coordinates> circle::intersection(line l, circle c) {
	// Set ax + by = c equal to (x - X)^2 + (y - Y)^2 = r^2 and expand:
	// (a^2 + b^2)x^2 + (2abY - 2ac + - 2b^2X)x + b^2X^2 + b^2Y^2 - 2bcY + c^2 - b^2r^2 = 0
	// Then use quadratic formula X = (-b +- sqrt(a^2 - 4ac))/2a to find the
	// roots of the equation (if they exist).
	std::vector<coordinates> ret;
	// Ax^2 + Bx + C = 0;
	decimal_n A = pow(l.a, 2) + pow(l.b, 2);
	decimal_n B = 2.0 * (l.a * l.b * c.center.y - l.a * (-l.c) - pow(l.b, 2) * c.center.x);
	decimal_n C = pow(l.b * c.center.x, 2) + pow(l.b * c.center.y, 2) - 2 * l.b * (-l.c) * c.center.y + pow(l.c, 2) - pow(l.b, 2) * pow(c.radius, 2);

	decimal_n D = pow(B, 2) - 4 * A * C;
	decimal_n x1, y1, x2, y2;
	decimal_n tolerance = 1e-4;
	// Vertical line case :0
	if (std::abs(l.b) < tolerance) {

		// ax + by = c, but b = 0, so x = c/a
		decimal_n vx = (-l.c) / l.a;

		// No intersection
		if (std::abs(c.center.x - vx) > c.radius) {
			return ret;
		}

		// Vertical line is tangent to circle
		if (std::abs((vx - c.radius) - c.center.x) < tolerance || std::abs((vx + c.radius) - c.center.x) < tolerance){
			ret.push_back(coordinates(vx, c.center.y));
			return ret;
		}
	
		decimal_n dx = std::abs(vx - c.center.x);
		decimal_n dy = sqrt(pow(c.radius, 2) - pow(dx, 2));
	
		ret.push_back(coordinates(vx, c.center.y + dy));
		ret.push_back(coordinates(vx, c.center.y - dy));
	
		return ret;

		// Line is tangent to circle
	} else if (std::abs(D) < tolerance) {

		x1 = -B / (2 * A);
		y1 = (-l.c - l.a * x1) / l.b;
		ret.push_back(coordinates(x1, y1));

		// No intersection point
	} else if (D < 0) {
		return ret;
		// Two unique intersection points
	} else {
		D = sqrt(D);
		x1 = (-B + D) / (2 * A);
		y1 = (-l.c - l.a * x1) / l.b;
		x2 = (-B - D) / (2 * A);
		y2 = (-l.c - l.a * x2) / l.b;
		ret.push_back(coordinates(x1, y1));
		ret.push_back(coordinates(x2, y2));
		return ret;
	}
	return ret;
}


std::vector<coordinates> circle::intersection(line l) {
	return intersection(l, *this);
};


std::vector<coordinates> circle::intersection(circle k, circle c) {
	std::vector<coordinates> ret;
    decimal_n dx = c.center.x - k.center.x;
    decimal_n dy = c.center.y - k.center.y;
    decimal_n d = c.center.get_distance(k.center);
		// Circles too far apart
	if (d > k.radius + c.radius) { return ret; }
		
	// One circle completely inside the other
	if (d < std::abs(k.radius - c.radius)) { return ret; }
	dx /= d;
	dy /= d;
	decimal_n a = (pow(k.radius, 2) - pow(c.radius, 2) + pow(d, 2)) / (2 * d);
	decimal_n px = k.center.x + a * dx;
	decimal_n py = k.center.y + a * dy;
	decimal_n h = sqrt(pow(k.radius, 2) - pow(a, 2));
	ret.push_back(coordinates(px + h * dy, py - h * dx));
	if (h != 0) ret.push_back(coordinates(px - h * dy, py + h * dx));
	return ret;
}


std::vector<coordinates> circle::intersection(circle c) {
	return intersection(c, *this);
}


void circle::circle_tangents (coordinates c, decimal_n r1, decimal_n r2, std::vector<line> & ans) {
    decimal_n r = r2 - r1;
    decimal_n z = pow(c.x, 2) + pow(c.y, 2);
    decimal_n d = z - pow(r, 2);
    if (d < -(1e-4))  return;
    d = sqrt (abs (d));
    line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = r1;
    ans.push_back(line((c.x * r + c.y * d) / z, (c.y * r - c.x * d) / z, r1));
}


std::vector<line> circle::circle_tangents(circle a, circle b) {
    std::vector<line> ans;
	for (int i=-1; i<=1; i+=2)
		for (int j=-1; j<=1; j+=2)
			circle_tangents (b.center-a.center, a.radius*i, b.radius*j, ans);
	for (size_t i=0; i<ans.size(); ++i)
		ans[i].c -= ans[i].a * a.center.x + ans[i].b * a.center.y;
	return ans;
}


std::vector<coordinates> circle::tangent_points(circle c, coordinates point){
	decimal_n diff_x = point.x - c.center.x;
	decimal_n diff_y = point.y - c.center.y;
	decimal_n dxr = -diff_y; 
	decimal_n dyr = diff_x;
	decimal_n distance = c.center.get_distance(point);
	std::vector<coordinates> ret;
	if (distance >= c.radius){
		decimal_n rho = c.radius / distance;
		decimal_n ad = pow(rho, 2);
		decimal_n bd = rho * sqrt(1-pow(rho, 2));
		ret.assign({coordinates(c.center.x + ad * diff_x + bd * dxr, c.center.y + ad * diff_y + bd * dyr),
					coordinates(c.center.x + ad * diff_x - bd * dxr, c.center.y + ad * diff_y - bd * dyr)});
		}
	return ret;
}


std::vector<coordinates> circle::tangent_points(coordinates point){
	return circle::tangent_points(*this, point);
}


std::vector<line> circle::tangents(circle c, coordinates point){
	std::vector<line> ret;
	if(c.is_on(point)){
		ret.push_back(line(c.center, point).make_perpendicular(point));
		return ret;
		}
	for(auto i: circle::tangent_points(c, point))
		ret.push_back(line(point, i));
	return ret;
}


std::vector<line> circle::tangents(coordinates point){
	return circle::tangents(*this, point);
}


std::string circle::print(){
	std::string ret = "(x";
	ret += ((center.x > 0)?"":"+");
	ret += std::to_string(-1*center.x);
	ret += ")^2 + (y";
	ret += ((center.y > 0)?"":"+");
	ret += std::to_string(-1*center.y);
	ret += ")^2 =";
	ret += std::to_string(pow(radius, 2));
	
	return ret;
	}


bool circle::on_segment(coordinates start, coordinates end, coordinates point, bool angle){
	if(!is_on(point)){
		return false;
		}
		
	line cut(start, end);
	line perp = cut.make_perpendicular(this -> center);
		
	std::vector<coordinates> intersections = intersection(perp, (*this));
	/// it's sure there are exactly two intersections, both do have exact same distance to start and end
	decimal_n d0 = start.get_distance(intersections[0]);
	decimal_n d1 = start.get_distance(intersections[1]);
	decimal_n max;
	coordinates* p_center;
	if(d0 > d1){ // checks which of them is further -> that one also has bigger angle
		p_center = &intersections[0];
		max = d0;
		}else{
			p_center = &intersections[1];
			max = d1;
			}
	
	// returns true if the point is on bigger segment if bigger angle is set (1)
	// it is checked by a fact that it is actually closer than start/end
	// if that is not the case, it already is on the circle, so it must be on the smaller angle
	return angle == (p_center -> get_distance(point) < max);
	};

std::vector<circle> circle::circles(line a, line b, decimal_n radius){
	std::vector<circle> ret;
	coordinates intersection = a.intersection(b);
	if(intersection.is_invalid()){
		return ret;
	}
	decimal_n angle = a.get_angle(b);
	//~ std::cout << intersection.print() << std::endl;
	ret.push_back(circle(intersection.make_global(coordinates(0, radius / (sin(angle/2))), ((a.get_angle() + b.get_angle())/2)-pi_const), radius));
	ret.push_back(circle(intersection.make_global(coordinates(0, -radius / (sin(angle/2))), ((a.get_angle() + b.get_angle())/2)-pi_const), radius));
	ret.push_back(circle(intersection.make_global(coordinates(radius / (sin(pi_const/2 -angle/2)), 0), ((a.get_angle() + b.get_angle())/2)-pi_const), radius));
	ret.push_back(circle(intersection.make_global(coordinates(-radius / (sin(pi_const/2 -angle/2)), 0), ((a.get_angle() + b.get_angle())/2)-pi_const), radius));
	
	return ret;
	}


decimal_n circle::get_distance(circle ci, coordinates co){ // gets the distance from circumference
	return std::abs(co.get_distance(ci.center) - ci.radius);
	}

	
decimal_n circle::get_distance(coordinates co){ // gets the distance from circumference
	return get_distance((*this), co);
	}

	
decimal_n circle::get_distance(circle ci, line l){ // gets the distance from circumference
	line p = l.make_perpendicular(ci.center);
	decimal_n distance_intersection = ci.center.get_distance(p.intersection(l));
	decimal_n distance_to_circumference = distance_intersection - ci.radius;
	
	return ((distance_to_circumference) < 0)? 0: distance_to_circumference;
	}

	
decimal_n circle::get_distance(line li){ // gets the distance from circumference
	return get_distance((*this), li);
	}


decimal_n circle::get_distance(circle c, coordinates a, coordinates b){
	std::array<decimal_n, 2> distances_ab = {c.center.get_distance(a), c.center.get_distance(b)};
	
	if((c.radius < distances_ab[0]) ^ (c.radius < distances_ab[1])){
		/// fact that one of the coordinates is closer and the other further means that it has on_segment intersection
		return 0; 
		}
		
	line l(a, b);
	std::vector<coordinates> intersections = c.intersection(l);
	if(intersections.size() == 0){ 
		/// means the segment is outside - treat it as a line for some part
		line p = l.make_perpendicular(c.center);
		
		coordinates inter = p.intersection(l);
		std::cout << c.center.print() << std::endl;
		std::cout << p.print() << std::endl;
		std::cout << inter.print() << std::endl;
		return std::abs(((l.on_segment(inter, a, b))? c.center.get_distance(inter): 
									((distances_ab[0] < distances_ab[1])? distances_ab[0]: distances_ab[1])) - c.radius);
		} 
	
	return std::abs((distances_ab[0] > distances_ab[1]? distances_ab[0]: distances_ab[1]) - c.radius);
	}


decimal_n circle::get_distance(coordinates a, coordinates b){
	return get_distance((*this), a, b);
	}


#endif


