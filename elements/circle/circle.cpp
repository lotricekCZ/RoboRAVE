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

#include <cmath> 
//~ #include "include.hpp"
#include "circle.hpp"

#ifndef CIRCLE_CPP
#define CIRCLE_CPP


circle::circle(decimal_n x = 0, decimal_n y = 0, decimal_n r = 0){
	this -> center.x = x;
	this -> center.y = y;
	this -> radius = r;
	}
	
circle::circle(coordinates c, decimal_n r = 0){
	this -> center = c;
	this -> radius = r;
	}

bool circle::inside(coordinates a){
	return inside(a.x, a.y);
	}
	
bool circle::inside(decimal_n x, decimal_n y){
	return pow(x - center.x, 2) + pow(y - center.y, 2) <= pow(radius, 2);
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
	decimal_n tolerance = 1e-5;
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
};

void circle::circle_tangents (coordinates c, decimal_n r1, decimal_n r2, std::vector<line> & ans) {
    decimal_n r = r2 - r1;
    decimal_n z = pow(c.x, 2) + pow(c.y, 2);
    decimal_n d = z - pow(r, 2);
    if (d < -(1e-9))  return;
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

#endif


