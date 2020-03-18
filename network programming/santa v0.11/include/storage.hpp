#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

/*
 * We create an interface for storage classes to provide a unified access
 * format for different storage types.
 * 
 * This class has a pure virtual destructor.
 *
 * Functions read and write are pure virtual functions that get a unique_ptr to 
 * the DriverData, which passes information through the implemntation.
 * They return std::unique_ptr<DriverData>.
 * 
 * This class is unmovable and uncopyable.
 * 
 * File:   storage.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand
 *
 */

#include <iosfwd> // std::size_t

#include "driver_data.hpp"

namespace ilrd
{

class Storage
{
public:
    Storage() = default;
    virtual ~Storage() = 0;  // have to be pure ?????????????????????????????????????????????

    virtual std::unique_ptr<DriverData> read(std::unique_ptr<DriverData> data)  = 0;
    virtual std::unique_ptr<DriverData> write(std::unique_ptr<DriverData> data) = 0;

    Storage(const Storage& other) = delete;                 
    Storage& operator=(const Storage& other) = delete;      
    Storage(Storage&& other) = delete;                      
    Storage& operator=(Storage&& other) = delete;           

private:
	// No data members
};

inline Storage::~Storage()
{
}

} // namespace ilrd

#endif //__STORAGE_HPP__
