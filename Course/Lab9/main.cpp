#include <iostream>
#include <vector>
#include <cmath>

#define GOLDEN_RATIO ((sqrt(5)+1)/2)

class VectorOfInts {
private:
    size_t m_size;
    size_t m_capacity;
    int * m_data;
public:
    VectorOfInts() : m_size{0}, m_capacity{0}, m_data{nullptr} {}
    ~VectorOfInts() {delete [] m_data;}
    using index_t = size_t;
    void push_back(int);
    void pop_back();
    int back() const;
    size_t size() const;
    size_t capacity() const;
    int &operator[](index_t);
};

void VectorOfInts::push_back(int i)
{
    if (!m_data)
    {
        m_data = new int;
        m_capacity = 1;
    }

    else
    {
        if(m_size == m_capacity)
        {
            size_t newCapacity = static_cast<size_t>(ceil(GOLDEN_RATIO*m_capacity));
            int * newData = new int[newCapacity];
            size_t i;

            for (i = 0; i < m_size; i++)
                newData[i] = m_data[i];

            delete [] m_data;
            m_data = newData;
            m_capacity = newCapacity;
        }
    }
    m_data[m_size++] = i;

}

int VectorOfInts::back() const
{
    return m_data[m_size-1];
}

void VectorOfInts::pop_back()
{
    if (m_size == 0)
    {
        std::cout << "No elements to pop!" << std::endl;
    }
    m_size--;
}

size_t VectorOfInts::size() const
{
    return m_size;
}

size_t VectorOfInts::capacity() const
{
    return m_capacity;
}

int &VectorOfInts::operator[](index_t i)
{
    return m_data[i];
}

int main()
{
    VectorOfInts v1;
    int i;

    for (i = 0; i < 1000; i++)
    {
        v1.push_back(i);
        std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    }

    return 0;
}
