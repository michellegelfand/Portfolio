// File name:   composite_tree.hpp
// Developer:   Michelle Gelfand
// Date Created: 28/10/2019 20:52
// Last Modified: 28/10/2019 20:52
// Description: Tree files directories container using composite pattern.

#ifndef __ILRD_COMPOSITE_TREE_HPP__
#define __ILRD_COMPOSITE_TREE_HPP__

#include <string>   //string
#include <vector>   //vector
#include <memory>   //shared_ptr

namespace ilrd
{

//TODO read about https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
class File: public std::enable_shared_from_this<File>
{
public:
    explicit File(const std::string& name);
    virtual ~File() = default;

    File(const File& other) = default;
    File& operator=(const File& other) = default;

    virtual std::shared_ptr<const File> find(const std::string& name) const noexcept;  

    //maybe the better way would be to have a display func that calls a virtual display_impl ??? (as we did in shapes with draw, draw_impl)
    virtual void display(std::ostream& os, size_t depth) const; //possibly need to be edited
private:
    std::string m_name;
};

class Directory : public File
{
public:
    static std::shared_ptr<Directory> create(const std::string& path);

    std::shared_ptr<const File> find(const std::string& name) const noexcept override; 
    void display(std::ostream& os, size_t depth) const override; //possibly need to be edited

    explicit Directory(const std::string& name); //made public to enable 
    //make_shared, cant use when private ctor
private:
    std::vector<std::shared_ptr<const File>> m_files;
    void add(std::shared_ptr<const File> entry);

/*     friend std::shared_ptr<Directory> std::make_shared<Directory>(const std::__cxx11::string &__args); */
    // Do we want to implement a remove function also?
    // void remove(std::shared_ptr<File> entry);
};

}   //namespace ilrd

#endif //__ILRD_COMPOSITE_TREE_HPP__

