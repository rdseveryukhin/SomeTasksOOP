#include <vector>
#include <list>
#include <iterator>

template<class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;
    ListT data_;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const&) = default;
    VectorList(VectorList&&) = default;

    VectorList& operator=(VectorList&&) = default;
    VectorList& operator=(VectorList const&) = default;

    template<class It>
    void append(It p, It q) {
        if (p != q) {
            data_.push_back(VectT(p, q));
        }
    }

    bool empty() const { return size() == 0; }

    size_t size() const
    {
        size_t ans = 0;
        for (auto& v : data_)
        {
            ans += v.size();
        }
        return ans;
    }

    struct const_iterator : std::iterator<std::bidirectional_iterator_tag, const T>
    {
        typename ListT::const_iterator ItL;
        typename VectT::const_iterator ItV;
        const ListT* ptr;

        const_iterator() = default;
        ~const_iterator() = default;
        const_iterator(const const_iterator& It) = default;
        const_iterator& operator=(const const_iterator&) = default;
        const_iterator(const ListT* ptr_) :
            ItL(ptr_->cbegin()), ItV(ItL->cbegin()), ptr(ptr_) {};

        const_iterator& in_end()
        {
            ItL = --(ptr->cend());
            ItV = ItL->cend();
            return *this;
        }

        const T& operator*() const { return *ItV; };

        const_iterator& operator++()
        {
            if (ItV == std::prev((*ItL).cend()))
            {
                ++ItL;
                if (ItL != ptr->cend()) {
                    ItV = ItL->cbegin();
                }
                else { ++ItV; --ItL; }
            }
            else
            {
                ++ItV;
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator& operator--()
        {
            if (ItV == (*ItL).cbegin())
            {
                if (ItL != ptr->cbegin())
                {
                    --ItL;
                    ItV = std::prev((*ItL).cend());
                }
            }
            else
            {
                --ItV;
            }
            return *this;
        }

        const_iterator operator--(int)
        {
            auto tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator== (const const_iterator& right) const
        {
            return (ItL == right.ItL && ItV == right.ItV);
        }

        bool operator!= (const const_iterator& right) const
        {
            return !(ItL == right.ItL && ItV == right.ItV);
        }

        const T* operator->() const { return &(*ItV); }

    };

    const_iterator begin() const
    {
        return !data_.empty() ? const_iterator(&data_) : const_iterator();
    }
    const_iterator end() const
    {
        return !data_.empty() ? const_iterator(&data_).in_end() : const_iterator();
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_reverse_iterator rbegin() const
    {
        return !data_.empty() ? const_reverse_iterator(end()) : const_reverse_iterator();
    }
    const_reverse_iterator rend()   const
    {
        return !data_.empty() ? const_reverse_iterator(begin()) : const_reverse_iterator();
    }
};


