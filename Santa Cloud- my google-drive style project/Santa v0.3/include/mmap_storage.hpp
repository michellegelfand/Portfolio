
#ifndef __MMAP_STORAGE_HPP__ 
#define __MMAP_STORAGE_HPP__ 


#include <vector>   // std::vector
#include <mutex>    // std::mutex
#include <iosfwd>   // std::size_t

#include "storage.hpp"
#include "driver_data.hpp"

namespace ilrd
{

class MmapStorage : public Storage
{
public:
    MmapStorage(size_t size, const std::string& path);
    ~MmapStorage() override;

    std::unique_ptr<DriverData> read(std::unique_ptr<DriverData> data)  override;
    std::unique_ptr<DriverData> write(std::unique_ptr<DriverData> data) override;

    MmapStorage(const MmapStorage& other)            = delete;
    MmapStorage& operator=(const MmapStorage& other) = delete;
    MmapStorage(MmapStorage&& other)                 = delete;
    MmapStorage& operator=(MmapStorage&& other)      = delete;

private:
    int m_fd;
    size_t m_length;
    char* m_memory; //points to memroy
    std::mutex m_mutex;
};

}// namespace ilrd

#endif //__MMAP_STORAGE_HPP__ 

