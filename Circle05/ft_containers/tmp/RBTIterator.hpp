# ifndef RBTITERATOR_HPP
#define RBTITERATOR_HPP

namespace ft
{
    template <class T>
    class RBTIterator
 	{
         

	public :

		typedef typename	T::value_type				value_type;

    	typedef 			value_type*					pointer;
    	typedef 			value_type const *			const_pointer;
    	typedef 			value_type&					reference;
    	typedef 			value_type const &			const_reference;

        typedef	            T*		                    node_pointer;
    	typedef 			std::ptrdiff_t				difference_type;
	
    protected :
		node_pointer	_ptr;
    
    public:
		explicit RBTIterator(T* ptr = NULL)
			:_ptr(ptr)
		{}

		RBTIterator(RBTIterator const & src)
		{
			*this = src;
		}

		virtual	~RBTIterator()	{}

		RBTIterator&	operator=(RBTIterator const & rhs)
		{
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		reference	operator*()
		{
			return *(_ptr->value);
		}

		const_reference	operator*() const
		{
			return *(_ptr->value);
		}

		pointer	operator->()
		{
			return _ptr->value;
		}

		const_pointer	operator->() const
		{
			return _ptr->value;
		}

		RBTIterator operator++(int)
		{
			RBTIterator 	tmp(*this);

			operator++();
			return tmp;
		}

		RBTIterator& operator++()//value는 pair포인터
		{//현재 들어온 ptr이 5라고 가정
			if (!_ptr->value)//현재 밸류가 없는경우 end_node
				_ptr = _ptr->left; //ptr을 좌측값(작은값)으로 이동? 좌측자식 3
			if (_ptr->right->value) //우측자식(큰값) 값이 있는경우 우측자식 7
			{
				_ptr = _ptr->right;//그 자식으로 포인터를 옮김 5를 7로 옮김
				while (_ptr->left->value) //포인터를 옮기기전과 옮긴후 5와 7사이에 사이값이 있을 수 있으므로 
					_ptr = _ptr->left; //5와 가장 가까운값을 탐색 5 < ? < 7
			}
			else //우측 자식의 값이 없는경우
			{
				node_pointer	tmp(_ptr); //현재위치 복사생성

				while (_ptr->value && tmp != _ptr->left)//밸류가 있는 상태에서 //왜 반복문을 쓰는지? 의문6
				{//부모의 위치로 올라감
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return *this;
		}

		RBTIterator operator--(int)
		{
			RBTIterator 	tmp(*this);

			operator--();
			return tmp;
		}

		RBTIterator& operator--()
		{
			if (!_ptr->value)
				_ptr = _ptr->right;
			if (_ptr->left->value)
			{
				_ptr = _ptr->left;
				while (_ptr->right->_value)
					_ptr = _ptr->right;
			}
			else
			{
				node_pointer	tmp(_ptr);

				while (_ptr->value && tmp != _ptr->right)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return *this;
		}

		bool operator==(RBTIterator const &rhs) const
		{
			return (_ptr == rhs._ptr);
		}

		bool operator!=(RBTIterator const &rhs) const
		{
			return !(operator==(rhs));
		}
        
        node_pointer    get_node() { return _ptr; }
	};

}


#endif