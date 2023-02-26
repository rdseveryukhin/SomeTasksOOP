struct ICloneable;

template <typename T>
struct ValueHolder;

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder : public ICloneable {
	ValueHolder(const T& data) : data_(data) {}

	ICloneable* clone() const override {
		return new ValueHolder(data_);
	}

	T data_;
};

class Any
{
public:
	Any() : ptr(0) {}

	template <typename T>
	Any(T data) {
		ptr = new ValueHolder<T>(data);
	}

	~Any() {
		delete ptr;
	}

	Any(const Any& other) {
		if (other.ptr != 0) {
			ptr = other.ptr->clone();
		}
		else {
			ptr = nullptr;
		}
	}

	Any& operator=(const Any& other) {
		if (this != &other) {
			if (ptr != nullptr) {
				delete ptr;
			}
			if (other.ptr != 0) {
				ptr = other.ptr->clone();
			}
			else {
				ptr = nullptr;
			}
		}
		return *this;
	}

	template <typename U>
	U* cast() {
		ValueHolder<U>* temp = dynamic_cast<ValueHolder<U>*>(ptr);
		if (temp != nullptr) {
			return &(temp->data_);
		}
		return nullptr;
	}

	ICloneable* ptr;
};

int main() {
	Any empty;
	Any i(10);
}
