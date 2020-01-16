#ifndef __BITSET_H__
#define __BITSET_H__

#include <iostream>     // std::cout, std::size_t
#include <vector>       // std::vector
#include <algorithm> //foreach
#include <string> //string
#include <stdexcept>//throw out of range
#include <array>//array LUT
    // functors
   /*  struct BitwiseAnd;
    struct BitwiseOr;
    struct CountSetBits;
    struct ShiftLeft;
    struct ShiftRight; */

namespace ilrd
{

const std::size_t BITS_IN_BYTE = 8;
const std::size_t BITS_IN_SIZET = sizeof(size_t) * BITS_IN_BYTE;

template<const std::size_t SIZE>
class Bitset
{ 
public:
    class BitProxy
    {
    public:
        BitProxy(Bitset<SIZE>& bitset, std::size_t index);

        BitProxy& operator=(const BitProxy& other);

        BitProxy& operator=(const bool val);
        
        operator bool() const;
        
        bool operator!();

    private:
        Bitset<SIZE>& m_bitset;    
        std::size_t m_index;
    };

    Bitset();

    void SetAll(bool val);
    void Flip(std::size_t index);
    void FlipAll();
    std::size_t CountBitsOn() const;
    std::string ToString() const;

    bool operator==(const Bitset<SIZE>& other) const;
    bool operator!=(const Bitset<SIZE>& other) const;
    Bitset& operator|=(const Bitset<SIZE>& other);
    Bitset& operator&=(const Bitset<SIZE>& other);
    Bitset operator>>(std::size_t num) const;
    Bitset operator<<(std::size_t num) const;

    bool operator[](std::size_t index) const; 
    BitProxy operator[](std::size_t index); // trowing exceptions version of operator []

    void AssertInRange(std::size_t index) const;
    size_t DirtyBits(std::size_t index);
    void SetBit(std::size_t index, bool val);
    bool GetBit(std::size_t index);

    std::size_t CountBitsOn(); 
    void FillCountLUT();
    void CleanDirtyBits();

private:
    const std::size_t m_array_size = SIZE / BITS_IN_SIZET + ((SIZE % BITS_IN_SIZET) > 0);
    //std::size_t m_bitarray[array_size]; --> prev. version
    std::vector<size_t> m_bitarray; // --> suggested version
    std::array<size_t, 256> m_LUT;

};

/***************************************************************/
template<std::size_t SIZE>
Bitset<SIZE>::BitProxy::BitProxy(Bitset& bitset, std::size_t index)
            :m_bitset(bitset), m_index(index)
{
}

template<std::size_t SIZE>
typename Bitset<SIZE>::BitProxy& Bitset<SIZE>::BitProxy::operator=(const BitProxy& other)
{
    m_bitset.SetBit(m_index, other.m_bitset.GetBit(other.m_index));
    return *this;
}

template<std::size_t SIZE>
typename Bitset<SIZE>::BitProxy& Bitset<SIZE>::BitProxy::operator=(const bool val)
{
    m_bitset.SetBit(m_index, val);
    return *this;
}

template<std::size_t SIZE>
Bitset<SIZE>::BitProxy::operator bool() const
{
    return m_bitset.GetBit(m_index);
}

template<std::size_t SIZE>
bool Bitset<SIZE>::BitProxy::operator!()
{
    return !(bool)*this;
}


size_t BitsForGivenNum(std::size_t num)
{
    num = ( (num & 0x5555555555555555) +
               ( (num >> 1) & 0x5555555555555555));

    num= ( (num  & 0x3333333333333333) +
              ( (num >> 2) & 0x3333333333333333));

    num = ( (num  & 0x0F0F0F0F0F0F0F0F) + 
               ( (num >> 4) & 0x0F0F0F0F0F0F0F0F));

    num = ( (num  & 0x00FF00FF00FF00FF) + 
               ( (num >> 8) & 0x00FF00FF00FF00FF));

    num = ( (num   & 0x0000FFFF0000FFFF) + 
               ( (num >> 16) & 0x0000FFFF0000FFFF));

    num = ( (num & 0x00000000ffffffff) + 
               ( (num >>32) & 0x00000000ffffffff));

    return num;
}

template<std::size_t SIZE>
void Bitset<SIZE>::FillCountLUT() 
{   
    for(size_t i = 0; i < 256; ++i)
    {
        //256 possible numbers, in each slot in LUT, number of set bits
        //for that num. e.g LUT for num 3- will return 2
        m_LUT[i] = BitsForGivenNum(i);
    }
}

template<std::size_t SIZE>
std::size_t Bitset<SIZE>::CountBitsOn() 
{
    size_t summed_bits = 0;
    size_t byte = 0;
    size_t mask = 0xFF;

    if( !m_LUT[1]) //check if inited
    {
        FillCountLUT();
    }

    for(size_t i = 0; i < m_array_size ; ++i)
    {
        for(size_t j = 0; j < 8; ++j)
        {
            byte = m_bitarray[i] & (mask << j*8);
            byte >>= (j*8);
            summed_bits += m_LUT[byte];
        }
    }

    return summed_bits;
}

template<const std::size_t SIZE>
Bitset<SIZE>::Bitset()
{
    m_bitarray.resize(m_array_size);
    std::fill(m_bitarray.begin(), m_bitarray.end(), 0);
    std::fill(m_LUT.begin(), m_LUT.end(), 0);
}


template<const std::size_t SIZE>
bool Bitset<SIZE>::GetBit(std::size_t index)
{
    AssertInRange(index);

    std::size_t mask = 1UL << DirtyBits(index);
    std::size_t array_of_bit = index / BITS_IN_SIZET;

    return ((m_bitarray[array_of_bit] & mask) != 0);
}

template<const std::size_t SIZE>
void Bitset<SIZE>::AssertInRange(std::size_t index) const
{
    if(index >= SIZE)
    {
       throw std::out_of_range("error"); 
    }
}

template<const std::size_t SIZE>
std::size_t Bitset<SIZE>::DirtyBits(std::size_t index)
{
    return BITS_IN_SIZET - (index % BITS_IN_SIZET);
}

template<const std::size_t SIZE>
void Bitset<SIZE>::SetBit(std::size_t index, bool val)
{
    AssertInRange(index);

    if( val != GetBit(index))
    {
      Flip(index);
    }
}

template<const std::size_t SIZE>
void Bitset<SIZE>::CleanDirtyBits()
{
    m_bitarray[m_array_size-1] <<= DirtyBits(SIZE); 
    m_bitarray[m_array_size-1] >>= DirtyBits(SIZE);
}

template<const std::size_t SIZE>
void Bitset<SIZE>::SetAll(bool val)
{
    std::fill(m_bitarray.begin(), m_bitarray.end(), val ? ~0 : 0);

    CleanDirtyBits();
}



struct BitArrayToStr    
{
    void operator()(size_t bitarray)
    {
        size_t mask = 1UL;

        for(size_t i =0; i< BITS_IN_SIZET; ++i)
        {
            char temp = (bitarray & mask ? '1' : '0');
            string.push_back(temp); 
            mask <<= 1;
        }  
    }
    
    std::string string;
};


template<const std::size_t SIZE>
std::string Bitset<SIZE>::ToString() const
{
    BitArrayToStr batstr = std::for_each(m_bitarray.begin(), m_bitarray.end(), BitArrayToStr());

    size_t remainder = (BITS_IN_SIZET - (SIZE % BITS_IN_SIZET));

    batstr.string.erase(m_array_size * BITS_IN_SIZET - remainder ,remainder);

    return batstr.string;
}

template<const std::size_t SIZE>
void Bitset<SIZE>::Flip(std::size_t index)
{
    AssertInRange(index);

    std::size_t mask = 1UL << index;
    
    m_bitarray[index / BITS_IN_SIZET] ^= mask;
}

template<const std::size_t SIZE>
void Bitset<SIZE>::FlipAll()
{
    std::for_each(m_bitarray.begin(), m_bitarray.end(), 
    [](std::size_t& bitarray){ bitarray = ~bitarray; });
    CleanDirtyBits();
}


template<const std::size_t SIZE>
bool Bitset<SIZE>::operator==(const Bitset<SIZE>& other) const
{
    return (m_bitarray == other.m_bitarray);
}


template<const std::size_t SIZE>
bool Bitset<SIZE>::operator!=(const Bitset<SIZE>& other) const
{
    return !(*this==other);
}

struct BitArrayOr
{
    size_t operator()(size_t ours, size_t other)
    {
        return ours | other;
    }
};

template<const std::size_t SIZE>
Bitset<SIZE>& Bitset<SIZE>::operator|=(const Bitset<SIZE>& other) 
{
    transform(m_bitarray.begin(), m_bitarray.end(), 
        other.m_bitarray.begin(), m_bitarray.begin(), BitArrayOr());
              
    return *this;
}

struct BitArrayAnd
{
    size_t operator()(size_t ours, size_t other)
    {
        return ours & other;
    }
};

template<const std::size_t SIZE>
Bitset<SIZE>& Bitset<SIZE>::operator&=(const Bitset<SIZE>& other) 
{
    transform(m_bitarray.begin(), m_bitarray.end(), 
        other.m_bitarray.begin(), m_bitarray.begin(), BitArrayAnd());
              
    return *this;
}

template<const std::size_t SIZE>
bool Bitset<SIZE>::operator[](std::size_t index) const
{
    return GetBit(index);
}

template<const std::size_t SIZE>
typename Bitset<SIZE>::BitProxy Bitset<SIZE>::operator[](std::size_t index)
{
    AssertInRange(index);
    return BitProxy(*this, index);
}

/* class ShiftBitsRight
{
    
public:
    ShiftBitsRight(size_t shift_bits) 
    : m_shift_bits(shift_bits), m_save_for_next_shift(0)
    {}

    size_t operator () (size_t element)
    { 
        size_t result = m_save_for_next_shift | (element << m_shift_bits);
        m_save_for_next_shift = element >> (BITS_IN_SIZET - m_shift_bits);

        return result;
    }

private:
    size_t m_shift_bits;
    size_t m_save_for_next_shift;

};

struct ShiftElementsRight
{
    size_t operator () (size_t prev, size_t next) 
    { 
        return next;
    }

};

template<const std::size_t SIZE>
Bitset<SIZE> Bitset<SIZE>::operator>>(std::size_t num) const
{   
    Bitset<SIZE> shifted_array;
    size_t elements_to_shift = num / BITS_IN_SIZET;
    size_t bits_to_shift = num % BITS_IN_SIZET;


    std::transform(shifted_array.m_bitarray + elements_to_shift, shifted_array.m_bitarray + m_array_size, m_bitarray, 
    shifted_array.m_bitarray + elements_to_shift, ShiftElementsRight());

    std::transform(shifted_array.m_bitarray, shifted_array.m_bitarray + m_array_size, shifted_array.m_bitarray, ShiftBitsRight(bits_to_shift));

    return shifted_array;
} */

}//namespace ilrd

#endif  //__BITSET_H__


