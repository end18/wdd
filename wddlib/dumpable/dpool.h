// Copyright (c) 2014 ipkn.
// Licensed under the MIT license.

#pragma once

#include <iostream>
#include <vector>
#include <cstddef>
#include <map>

namespace dumpable
{
    class dpool
    {
        public:
            dpool(void* startAddress, dumpable::size_t size)
                : poolSize_(size)
            {
                poolOffsets_.insert(std::make_pair(startAddress, 0));
            }

            void write(std::ostream& os)
            {
                for(auto it = pool_.begin(); it != pool_.end(); ++it)
                {
                    os.write(&(*it)[0], it->size());
                }
            }

            std::pair<void*, dumpable::ptrdiff_t> alloc(void* self, dumpable::size_t size)
            {
                if (!size)
                    return std::make_pair(nullptr, 0);
#ifdef DUMPABLE_ALIGNED_POOL
                size = (size+(sizeof(size_t)-1))/sizeof(size_t)*sizeof(size_t);
#endif
                pool_.push_back(std::vector<char>(size));
                void* allocatedAddress = &pool_.back()[0];
                poolOffsets_.insert(std::make_pair(allocatedAddress, poolSize_));
                poolSize_ += size;
                auto it = poolOffsets_.upper_bound(self);
                --it;
                dumpable::ptrdiff_t diff = (char*)self - (char*)it->first;
                return std::make_pair(allocatedAddress, poolSize_-size-it->second-diff);
            }
        private:
            std::vector<std::vector<char>> pool_;
            dumpable::ptrdiff_t poolSize_;
            std::map<void*, dumpable::ptrdiff_t> poolOffsets_;
    };
}
