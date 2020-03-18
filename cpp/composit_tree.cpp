
#include <sys/types.h>//opendir
#include <dirent.h>//opendir
#include <string>//string
#include <algorithm> //for_each

#include "test_tools.h"//DEBUG ONLY
#include "composit_tree.hpp"


namespace ilrd
{

class Dir_Handler
{
public:
    explicit Dir_Handler(const std::string &path)
    {
        m_dir = opendir(path.c_str());
    }
    ~Dir_Handler()
    {
        closedir(m_dir);
    }
    DIR *dir_get()
    {
        return m_dir;
    }

    struct dirent* ReadDir() noexcept
    {
        return readdir(m_dir);
    }

    Dir_Handler(const Dir_Handler& other) = delete;
    Dir_Handler& operator=(const Dir_Handler& other) = delete;

private:
    DIR *m_dir;
};

class Entry_Handler
{
public:
    Entry_Handler() 
        : m_entry(nullptr){}
    
    Entry_Handler(const Entry_Handler& entry) = default;
    
    ~Entry_Handler(){}

    bool operator!=(struct dirent* other)
    {
        return !(m_entry == other);
    }
    Entry_Handler& LoadEntry(Dir_Handler& dir)
    {
       m_entry = dir.ReadDir();

       return *this;
    }
    Entry_Handler& operator=(struct dirent* other)
    {
        m_entry = other;
        return *this;
    }

    struct dirent* m_entry;
};



File::File(const std::string& name)
    :m_name(name)
{
}

void File::display(std::ostream& os,
                        size_t depth) const
{
    os << "|";
    
    for(size_t i=0; i <depth; ++i)
    {
        os << "-";
    }
    os << m_name << std::endl;
}

std::shared_ptr<const File> File::find(const std::string& name) const noexcept 
{
    if(m_name == name)
    {
        return shared_from_this();
    }

    return nullptr;
}    

/******** directory **************************************************/

Directory::Directory(const std::string& name)
    :File(name)
{
}

std::shared_ptr<Directory> Directory::create(const std::string& path)
{
    Dir_Handler dir(path);
                                        
    Entry_Handler ent;

    if(!dir.dir_get())
    {
        return nullptr;
    }

    std::shared_ptr<Directory>root = std::make_shared<Directory>(path);

    while ((ent.LoadEntry(dir)) != nullptr) 
    {
        std::string  to_cmp_name(ent.m_entry->d_name);
        std::string cur_path = path + '/' + ent.m_entry->d_name;

        if (ent.m_entry-> d_type == DT_REG) 
        {
            std::shared_ptr< File> curr_file (new File(ent.m_entry->d_name));
            root->add(curr_file);
        }
        else if(ent.m_entry->d_type == DT_DIR && to_cmp_name != "." &&
                                         to_cmp_name != "..")
        {
            std::shared_ptr<Directory> current_dir(Directory::create(cur_path));
            root->add(current_dir);
        }
    }
    return root;
}


void Directory::add(std::shared_ptr<const File> entry)
{
    m_files.push_back(entry);
}



std::shared_ptr<const File> Directory::find(const std::string& name) const noexcept 
{
    std::shared_ptr<const File> this_file;

    if(this_file = File::find(name))
    {
        return shared_from_this();
    }

    for (auto const& itr : m_files)
    {
        auto result = itr->find(name);

        if (nullptr != result)
        {
            return (result);
        }
    }

    return nullptr;
} 

void Directory::display(std::ostream& os,
                                size_t depth) const
{
    size_t size = m_files.size();
    File::display(os, depth);

    for(size_t i =0; i < size; ++i)
    {
        m_files[i]->display(os, depth+1);
    }
}

}//namespace ilrd