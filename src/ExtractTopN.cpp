#include <algorithm>
#include "IBlockBuffer.h"
#include "FileArrayReader.h"
#include <vector>

void extractTopElements(std::vector<int> &buffer, std::vector<int> &min_heap, size_t N) {
    std::make_heap(buffer.begin(), buffer.end());
    size_t steps = N;
    if(buffer.size() < N) {
        steps = buffer.size();
    }
    for(size_t i = 0; i <steps; i++ ) {
        std::pop_heap(buffer.begin(), buffer.end());
        min_heap.push_back(buffer.back());
		std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>{});
		buffer.pop_back();
    }
}


std::vector<int> ExtractTopN(std::shared_ptr<IBlockBuffer<std::vector<int>>> data, size_t N, size_t block_size) {
    std::vector <int> buffer;
    std::vector <int> min_heap;

	//data->next(buffer, block_size);
	//extractTopElements(buffer, min_heap, N);

    while(data->next(buffer, block_size)){
        extractTopElements(buffer, min_heap, N);

       // std::make_heap(min_heap.begin(), min_heap.end(),  std::greater<>{});
        size_t steps = min_heap.size() - N;
      /*  if(min_heap.size() < N) {
            steps = N;
        }*/
        for(size_t i = 0; i < steps; i++) {
            std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<int>{});
            min_heap.pop_back();
        }
		buffer.clear();

    }
    return min_heap;
}





