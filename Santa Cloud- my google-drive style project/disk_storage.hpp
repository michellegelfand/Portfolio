#ifndef __DISK_STORAGE_HPP__
#define __DISK_STORAGE_HPP__

/**
    File:   disk_storage.hpp
    Date:   08.11.19
    Author: Michelle Gelfand
 
 * We create an a derived class for the storage classe to provide an
   implementation for RAM storage.
 
 * This class implements the functions read and write to read from and write to 
   RAM storage.
 * They get a unique_ptr to the DriverData, which passes information through 
   the implemntation.
 * They return std::unique_ptr<DriverData>.
 
 * This class is unmovable and uncopyable.

**/

#include <vector> // std::vector
#include <iosfwd> // size_t
#include <mutex>  //std::mutex

#include "storage.hpp"

namespace ilrd
{

class DiskStorage : public Storage
{
public:
    DiskStorage(const std::string& path, size_t f_size);
    ~DiskStorage() override;

    std::unique_ptr<DriverData> read(std::unique_ptr<DriverData> data) override;
    std::unique_ptr<DriverData> write(std::unique_ptr<DriverData> data) override;

    DiskStorage(const DiskStorage& other) = delete;                 
    DiskStorage& operator=(const DiskStorage& other) = delete;      
    DiskStorage(DiskStorage&& other) = delete;                      
    DiskStorage& operator=(DiskStorage&& other) = delete;           

private:
    int m_fd;
};

} // namespace ilrd

#endif //__DISK_STORAGE_HPP__

