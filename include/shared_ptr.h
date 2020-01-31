#include <type_traits>
#ifndef _SHARED_PTR_
#define _SHARED_PTR_
#include <memory>

namespace my {
	template <typename T> class shared_ptr;

	template<typename T> bool operator==(const shared_ptr<T> &left, const shared_ptr<T> &right);
	template<typename T> bool operator!= (const shared_ptr<T> &left, const shared_ptr<T> &right);
	template<typename T> bool operator> (const shared_ptr<T> &left, const shared_ptr<T> &right);
	template<typename T> bool operator<(const shared_ptr<T> &left, const shared_ptr<T> &right);
	template<typename T> bool operator<(const shared_ptr<T> &left, const shared_ptr<T> &right);
	template<typename T> bool operator>=(const shared_ptr<T> &left, const shared_ptr<T> &right);
	template<typename T> bool operator<=(const shared_ptr<T> &left, const shared_ptr<T> &right);

	template<typename T> bool operator==(std::nullptr_t, const shared_ptr<T> &right);
	template<typename T> bool operator==(const shared_ptr<T> &, std::nullptr_t);
	template<typename T> bool operator!=(std::nullptr_t left, const shared_ptr<T> &right);
	template<typename T> bool operator!=(const shared_ptr<T> &left, std::nullptr_t right);
	template<typename T> bool operator>(std::nullptr_t left, const shared_ptr<T> &right);
	template<typename T> bool operator>(const shared_ptr<T> &left, std::nullptr_t right);
	template<typename T> bool operator<(std::nullptr_t left, const shared_ptr<T> &right);
	template<typename T> bool operator<(const shared_ptr<T> &left, std::nullptr_t right);
	template<typename T> bool operator>=(std::nullptr_t left, const shared_ptr<T> &right);
	template<typename T> bool operator>=(const shared_ptr<T> &left, std::nullptr_t right);
	template<typename T> bool operator<=(std::nullptr_t left, const shared_ptr<T> &right);
	template<typename T> bool operator<=(const shared_ptr<T> &left, std::nullptr_t right);

	

    template<typename T>
    class shared_ptr {
    public:
        shared_ptr() : val(nullptr), counter(nullptr) {}

        shared_ptr(T *data) : val(data), counter(new size_t) {
            *counter = 1;
        }

        shared_ptr(const shared_ptr<T> &ptr) {
            val = ptr.val;
            counter = ptr.counter;
            if (counter != nullptr) {
                (*counter)++;
            }
        }

        shared_ptr(shared_ptr<T> &&ptr) {
            val = ptr.val;
            ptr.val = nullptr;
            counter = ptr.counter;
            ptr.counter = nullptr;
        }

		~shared_ptr() {
			reset();
		}
        shared_ptr<T> &operator=(const shared_ptr<T> &ptr) {
            reset();
            val = ptr.val;
            counter = ptr.counter;
            if (counter != nullptr) {
                *counter += 1;
            }
            return *this;

        }

        shared_ptr<T> &operator=(shared_ptr<T> &&ptr) {
            reset();
            val = ptr.val;
            ptr.val = nullptr;
            counter = ptr.counter;
            ptr.counter = nullptr;
            return *this;
        }

        T *operator->() const {
            return val;
        }

        T &operator*() const {
            return *val;
        }

		size_t count() {
			if (counter != nullptr) {
				return *counter;
			}
			return 0;
		}
		
		bool empty() {
			return counter == nullptr;
		}

		friend  bool operator== <>(const shared_ptr &left, const shared_ptr &right);
        friend bool operator!= <>(const shared_ptr &left, const shared_ptr &right);
        friend bool operator> <>(const shared_ptr &left, const shared_ptr &right);
	    friend bool operator< <>(const shared_ptr &left, const shared_ptr &right);
        friend bool operator< <>(const shared_ptr &left, const shared_ptr &right);
        friend bool operator>= <>(const shared_ptr &left, const shared_ptr &right);
        friend bool operator<= <>(const shared_ptr &left, const shared_ptr &right);
		 
		friend bool operator== <>(std::nullptr_t left, const shared_ptr &right);
		friend bool operator== <>(const shared_ptr &left, std::nullptr_t right);
        friend bool operator!= <>(std::nullptr_t left, const shared_ptr &right);
        friend bool operator!= <>(const shared_ptr &left, std::nullptr_t right);
        friend bool operator> <>(std::nullptr_t left, const shared_ptr &right);
        friend bool operator> <>(const shared_ptr &left, std::nullptr_t right);
        friend bool operator< <>(std::nullptr_t left, const shared_ptr &right);
        friend bool operator< <>(const shared_ptr &left, std::nullptr_t right);
        friend bool operator>= <>(std::nullptr_t left, const shared_ptr &right);
        friend bool operator>= <>(const shared_ptr &left, std::nullptr_t right);
        friend bool operator<= <>(std::nullptr_t left, const shared_ptr &right);
        friend bool operator<= <>(const shared_ptr &left, std::nullptr_t right);

    private:
		
        void reset() {
            if (counter != nullptr) {
                *counter -= 1;
                if (*counter == 0) {
                    delete val;
                    delete counter;
                }
            }
        }

        T *val;
        size_t *counter;
    };

	template<typename T>
	bool operator==(const shared_ptr<T> &left, const shared_ptr<T> &right) {
		return left.val == right.val;
	}

	template<typename T>
	bool operator!=(const shared_ptr<T> &left, const shared_ptr<T> &right) {
		return left.val != right.val;
	}

	template<typename T>
	bool operator>(const shared_ptr<T> &left, const shared_ptr<T> &right) {
		return left.val > right.val;
	}

	template<typename T>
	bool operator<(const shared_ptr<T> &left, const shared_ptr<T> &right) {
		return left.val < right.val;
	}

	template<typename T>
	bool operator>=(const shared_ptr<T> &left, const shared_ptr<T> &right) {
		return left.val >= right.val;
	}

	template<typename T>
	bool operator<=(const shared_ptr<T> &left, const shared_ptr<T> &right) {
		return left->val <= right.val;
	}

	template<typename T>
	bool operator==(std::nullptr_t left, const shared_ptr<T> &right) {
		return left == right.val;
	}

	template<typename T>
	bool operator==(const shared_ptr<T> &left, std::nullptr_t right) {
		return left.val == right;
	}

	template<typename T>
	bool operator!=(std::nullptr_t left, const shared_ptr<T> &right) {
		return left != right.val;
	}

	template<typename T>
	bool operator!=(const shared_ptr<T> &left, std::nullptr_t right) {
		return left.val != right;
	}

	template<typename T>
	bool operator>(std::nullptr_t left, const shared_ptr<T> &right) {
		return left > right.val;
	}

	template<typename T>
	bool operator>(const shared_ptr<T> &left, std::nullptr_t right) {
		return left.val > right;
	}

	template<typename T>
	bool operator<(std::nullptr_t left, const shared_ptr<T> &right) {
		return left < right.val;
	}

	template<typename T>
	bool operator<(const shared_ptr<T> &left, std::nullptr_t right) {
		return left.val < right;
	}


	template<typename T>
	bool operator>=(std::nullptr_t left, const shared_ptr<T> &right) {
		return left >= right.val;
	}

	template<typename T>
	bool operator>=(const shared_ptr<T> &left, std::nullptr_t right) {
		return left.val >= right;
	}

	template<typename T>
	bool operator<=(std::nullptr_t left, const shared_ptr<T> &right) {
		return left <= right.val;
	}

	template<typename T>
	bool operator<=(const shared_ptr<T> &left, std::nullptr_t right) {
		return left.val <= right;
	}

	template<typename T, typename... Args>
	shared_ptr<T> make_shared(Args &&...args) {
		return shared_ptr<T>(new T(std::forward<Args>(args)...));
	}
}

#endif
