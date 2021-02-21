#include <iostream>
#include <vector>
#include <limits>
#include "../../../defines/typedefines.h"

//~ using namespace std; 
typedef struct edge {
	unsigned_b src = 0; 
	unsigned_b dest = 0; 
	decimal_n wt = 0; 
} edge; 


std::vector<unsigned_b> bellman_ford(unsigned_b number_vertice, 
									std::vector<edge> e, unsigned_b src_graph, 
									unsigned_b number_edge, unsigned_b end){
	unsigned_b u,v,weight,i,j = 0; 
	std::vector<decimal_n> dis (number_vertice); 
	std::vector<unsigned_b> nods; 
	std::cout << "no? " << src_graph << " " << end  << std::endl;
	/* initializing array 'dis' with infinite distance */
	for(i = 1; i <= number_vertice; i++){
		dis[i] = std::numeric_limits<decimal_n>::infinity(); //ffffff; 
	}
	
	//~ for(auto a: e){
		//~ std::cout << a.src << ", "<< a.dest << std::endl;
		//~ }
	/* distance of source vertex from source vertex is 0 */
	dis[src_graph] = 0; 
	/* relaxing all the edges number_vertice - 1 times */
	for(i = 0; i < number_vertice + 1; i++){
		for(j = 0; j < number_edge; j++){
			u = e[j].src; 
			v = e[j].dest; 
			weight = e[j].wt; 
			//~ std::cout << "What? " << weight << " " << u << " " << v << std::endl;
		
			if(dis[u] != std::numeric_limits<decimal_n>::infinity() && (dis[u] + weight) < dis[v]){
				dis[v] = dis[u] + weight;
				
			}	
		}
	}
	
	/*
	 * checking if negative cycle is present
	for(j = 0; j < number_edge; j++){
		u = e[j].src; 
		v = e[j].dest; 
		weight = e[j].wt; 
		if(dis[u] + weight < dis[v]){
			//~ std::cout << "\n\nNEGATIVE CYCLE PRESENT..!!\n"; 
			return std::vector<unsigned_b>(); 
		}	
	}
	*/
	std::cout << "\nvertex" << "	Distance from source"; 
	for(i = 1; i <= number_vertice; i++){
		std::cout << "\n" << i << "\t" << dis[i]; 
	}
	//~ nods.push_front(end);
	int end_val = end;// dis[end];
	uint32_t index = end;

	nods.push_back(index);
	while(end_val != 0){
		for(j = 0; j < number_edge; j++){
			u = e[j].src; 
			v = e[j].dest; 
			weight = e[j].wt;
			if(v == index &&  std::abs(weight + dis[u] - dis[v]) <= 1e-3 ){
				end_val = dis[u];
				index = u;
				nods.push_back(index);
			}
		}
	}
	
	//~ std::cout << "\nvertex" << "   Distance from source"; 
	//~ for(i = 1; i <= number_vertice; i++){
		//~ std::cout << "\n" << i << "\t" << dis[i]; 
	//~ }
	//~ for(auto i: nods)
		//~ std::cout << i <<"\t";
	//~ std::cout << "nudz" <<"\t";
	
	for(i = 0; i < (nods.size()/2); i++){
		unsigned_b tmp = nods[i];
		nods[i] = nods[nods.size()-i-1];
		nods[nods.size()-i-1] = tmp;
	}
	
	return nods;
}


//~ int main(){
	//~ int number_vertice,number_edge,src_graph; 
	//~ std::vector<edge> e; 
	
	//~ cout << "Enter the number of vertices: "; 
	//~ cin >> number_vertice; 	
	
	//~ /* if you enter no of vertices: 5 then vertices will be 1,2,3,4,5. so while giving input enter source and destination vertex accordingly */
	//~ printf("Enter the source vertex of the graph: "); 
	//~ cin >> src_graph; 	
	
	//~ cout << "\nEnter no. of edges: "; 
	//~ cin >> number_edge; 
	
	//~ for(int i = 0; i < number_edge; i++){
		//~ e.push_back(edge());
		//~ cout << "\nFor edge " << i+1 << " = >"; 
		//~ cout << "\nEnter source vertex :"; 
		//~ cin >> e[i].src; 
		//~ cout << "Enter destination vertex :"; 
		//~ cin >> e[i].dest; 
		//~ cout << "Enter weight :"; 
		//~ cin >> e[i].wt; 	
	//~ }
	
	//~ for(auto i: bellman_ford(number_vertice, e, src_graph, number_edge, number_vertice))
		//~ std::cout << i <<"\t";
	//~ std::cout << "\n";
	
	//~ return 0; 
//~ }
//~ 
