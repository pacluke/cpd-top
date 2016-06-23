#ifndef TRACK_SORTER_HPP
#define TRACK_SORTER_HPP
#include "tracks.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

namespace tsort{
	struct greaterpop{
		bool operator()(const ramtrack& a,const ramtrack& b){
			return a.popularity > b.popularity;
		}
	};
	struct minorpop{
		bool operator()(const ramtrack& a,const ramtrack& b){
			return a.popularity < b.popularity;
		}
	};
	void heap(std::vector<ramtrack> * tracklist, char order){
		if(order=='d'){
			std::make_heap((*tracklist).begin(), (*tracklist).end(), greaterpop());
			std::sort_heap((*tracklist).begin(), (*tracklist).end(), greaterpop());
		}
		else if(order=='c'){
			std::make_heap((*tracklist).begin(), (*tracklist).end(), minorpop());
			std::sort_heap((*tracklist).begin(), (*tracklist).end(), minorpop());
		}
		else{
			cout << "Invalid sort order." << endl;
		}
	}
}

#endif //TRACK_SORTER_HPP