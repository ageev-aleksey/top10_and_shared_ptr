#ifndef SHARED_PTR_EXTRACTTOPN_H
#define SHARED_PTR_EXTRACTTOPN_H

#include <memory>

std::vector<int> ExtractTopN(std::shared_ptr<IBlockBuffer<std::vector<int>>> data, size_t N, size_t block_size);

#endif //SHARED_PTR_EXTRACTTOPN_H
