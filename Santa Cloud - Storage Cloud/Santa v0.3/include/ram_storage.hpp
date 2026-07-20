#ifndef __RAM_STORAGE_HPP__
#define __RAM_STORAGE_HPP__

/*
 * We create an a derived class for the storage classe to provide an
 * implementation for RAM storage.
 * 
 * This class implements the functions read and write to read from and write to 
 * RAM storage. 
 * They get a unique_ptr to the DriverData, which passes information through 
 * the implemntation.
 * They return std::unique_ptr<DriverData>.
 * 
 * This class is unmovable and uncopyable.
 * 
 * File:   ram_storage.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand
 *
 */

#include <vector> // std::vector
#include <iosfwd> //cout 
#include <memory> // unique_ptr
#include <mutex>//std::mutex

#include "storage.hpp"
#include "lock_guard.hpp"

namespace ilrd
{

class RAMStorage : public Storage
{
public:
    RAMStorage(size_t storage_size);
    virtual ~RAMStorage();

    std::unique_ptr<DriverData> read(std::unique_ptr<DriverData> data)  override;
    std::unique_ptr<DriverData> write(std::unique_ptr<DriverData> data) override;

    RAMStorage(const RAMStorage& other) = delete;                 
    RAMStorage& operator=(const RAMStorage& other) = delete;      
    RAMStorage(RAMStorage&& other) = delete;                      
    RAMStorage& operator=(RAMStorage&& other) = delete;           

private:
    std::vector<char> m_buffer; 
    std::mutex m_write_mutex;
};

} // namespace ilrd

#endif //RAM_STORAGE_HPP__
