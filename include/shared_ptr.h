#include <type_traits>
#ifndef _SHARED_PTR_
#define _SHARED_PTR_
#include <mutex>

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

        shared_ptr(T *data) : val(data), counter(new counter_block) {
        }

        shared_ptr(const shared_ptr<T> &ptr) {
        	if(ptr.counter != nullptr) {
        		ptr.counter->mutex.lock();
        		
        		ptr.counter->value++;
        		counter = ptr.counter;
        		val = ptr.val;

        		ptr.counter->mutex.unlock();
           } else {
           		counter = nullptr;
           		val = nullptr;
           }
        }

        shared_ptr(shared_ptr<T> &&ptr) {
        	if(ptr.counter != nullptr) {
        		ptr.counter->mutex.lock();
        		
        		counter = ptr.counter;
        		val = ptr.val;
        		ptr.counter = nullptr;
        		ptr.val = nullptr;

        		counter->mutex.unlock();
           } else {
           		counter = nullptr;
           		val = nullptr;
           }
        }


		~shared_ptr() {
			reset();
		}
        shared_ptr<T> &operator=(const shared_ptr<T> &ptr) {
            reset();

            if(ptr.counter != nullptr) {
            	ptr.counter->mutex.lock();

            	ptr.counter->value++;
        		counter = ptr.counter;
        		val = ptr.value;

            	ptr.counter->mutex.unlock();
            } else {
            	counter = nullptr;
            	val = nullptr;
            }
            return *this;
        }

        shared_ptr<T> &operator=(shared_ptr<T> &&ptr) {
           reset();

            if(ptr.counter != nullptr) {
            	ptr.counter->mutex.lock();

        		counter = ptr.counter;
        		val = ptr.value;
        		ptr.counter = nullptr;
        		ptr.val = nullptr;

            	counter->mutex.unlock();
            } else {
            	counter = nullptr;
            	val = nullptr;
            }
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
				size_t tmp = 0;

				counter->mutex.lock();

				tmp = counter->value;

				counter->mutex.unlock();

				return tmp;
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
       		if(counter != nullptr) {

       			counter->mutex.lock();

       			if(counter->value == 1) {

       				counter->mutex.unlock();

       				delete val;
       				delete counter;
       				val = nullptr;
       				counter = nullptr;

       			}else {
       				counter->value--;

       				counter->mutex.unlock();
       			}
       			
       		}
        }

        struct counter_block {

        	counter_block() : value(1){}
     
        	size_t value;
        	std::mutex mutex;
        };
       
        T *val;
        counter_block *counter;
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
