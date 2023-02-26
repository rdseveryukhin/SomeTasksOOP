#include <cstddef>
#include <iostream>
#include <new>

using namespace std;

template <typename T>
class Array
{
public:

	explicit Array(size_t size, const T& value = T()) {
		this->size_ = size;
		if (size_ != 0) {
			array_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
			for (size_t i = 0; i < size_; i++) {
				new (array_ + i) T(value);
			}
		}
		else {
			this->array_ = nullptr;
		}
	}

	Array() : size_(0), array_(nullptr) {}

	Array(const Array &other) {
		this->size_ = other.size_;
		if (size_ != 0) {
			array_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
			for (size_t i = 0; i < size_; i++) {
				new (array_ + i) T(other.array_[i]);
			}
		}
		else {
			this->array_ = nullptr;
		}
	}

	~Array() {
		for (size_t i = 0; i < size_; i++) {
			(array_ + i) -> ~T();
		}
		if (size_ != 0) {
			operator delete[](array_);
		}
	}

	Array& operator=(const Array &other) {
		if (this != &other) {
			for (size_t i = 0; i < size_; i++) {
				(array_ + i) -> ~T();
			}
			if (size_ != 0) {
				operator delete[](array_);
			}
			this->size_ = other.size_;
			if (size_ != 0) {
				array_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
				for (size_t i = 0; i < size_; i++) {
					new (array_ + i) T(other.array_[i]);
				}
			}
			else {
				this->array_ = nullptr;
			}
		}
		return *this;
	}

	size_t size() const {
		return size_;
	}

	T& operator[](size_t i) {
		return *(array_ + i);
	}

	const T& operator[](size_t i) const {
		return *(array_ + i);
	}

private:
	size_t size_;
	T* array_;
};


struct TstObj {
	TstObj() : i(0) {
		cout << "\t new obj     addr=" << this << endl;
	}
	~TstObj() {
		cout << "\t del obj     addr=" << this << endl;
	}
	TstObj(const TstObj & a) : i(a.i) {
		cout << "\t new copy obj     addr=" << this << endl;
	}
	int i;
};


template <typename T1, typename Comp>
T1 minimum(Array <T1> &a, Comp b) {
	T1 temp = a[0];
	for (int i = 1; i < a.size(); i++) {
		if (b(a[i], temp)) {
			temp = a[i];
		}
	}
	return temp;
}


template <typename T>
void flatten(const Array<T>& array, std::ostream& out) {
	for (int i = 0; i < array.size(); i++) {
		out << array[i] << ' ';
	}
}

template <typename T>
void flatten(const Array<Array<T> >& array, std::ostream& out) { 
	for (int i = 0; i < array.size(); i++) {
		flatten(array[i], out);
	}
}


bool Less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };


int main() {
	
	Array<TstObj> arr1(3);

	Array<int> ints1(3);
	ints1[0] = 10;
	ints1[1] = 2;
	ints1[2] = 15;
	int min = minimum(ints1, Less); // min 2
	int max = minimum(ints1, Greater()); // max 15
	

	Array<int> ints(2, 0);
	ints[0] = 10;
	ints[1] = 20;
	flatten(ints, std::cout); // "10 20"

	Array< Array<int> > array_of_ints(2, ints);
	flatten(array_of_ints, std::cout); // "10 20 10 20"

	Array<double> doubles(10, 0.0);
	flatten(doubles, std::cout);
}