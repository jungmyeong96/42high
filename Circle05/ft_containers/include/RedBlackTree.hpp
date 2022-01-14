#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include "RBTIterator.hpp"
#include "RedBlackTreeNode.hpp"

namespace ft
{
    template <class T, class Compare, class Alloc>
    class RBTree
    {
        public:
            //Node 값 안에 넣는 Pair 데이터
            typedef T                                               value_type;
            typedef Compare                                         value_compare;
            typedef Alloc											allocator_type;

            //Node 값
            typedef ft::RBTreeNode< T >                             node_type;
		    typedef typename std::allocator< node_type >	        node_allocator_type; //이게 뭘까

            //typedef typename Alloc::reference						reference;
            //typedef typename Alloc::const_reference			    const_reference;

            typedef typename allocator_type::pointer			    pointer;
            typedef typename allocator_type::const_pointer		    const_pointer;
            typedef typename node_allocator_type::pointer			node_pointer;
            typedef typename node_allocator_type::const_pointer		node_const_pointer;

            typedef RBTIterator< node_type >						iterator;
            typedef RBTIterator<const node_type>					const_iterator;

            typedef typename	value_type::first_type				key_type;
            typedef typename	value_type::second_type				mapped_type;
		    typedef 		    Compare								key_compare;

            // typedef reverse_iterator<const_iterator>				const_reverse_iterator;
            // typedef reverse_iterator<iterator>						reverse_iterator;
            // typedef ptrdiff_t										difference_type;
             typedef size_t											size_type;

        private:
            node_pointer			end_node;
			node_pointer			root;

			key_compare				comp;

		    allocator_type	        value_alloc;
			node_allocator_type		node_alloc;

//***public_method***//

        public:
//constructor
			explicit        RBTree(const key_compare& compare = key_compare(), 
                                    const allocator_type& v_alloc = allocator_type(),
                                    const node_allocator_type& n_alloc = node_allocator_type()); //map의 생성자와 동일한 방식으로 트리생성자 생성

//iterator
			iterator	    begin();
			const_iterator	begin() const ;           
            iterator	    end();
            const_iterator	end() const;
			iterator	    find(const key_type& k);
        	const_iterator	find(const key_type& k) const;
            node_pointer	pos_find(const key_type& k)	const;

//infos
            bool	        empty() const;
            size_type       size() const;
            size_type       check_size(node_pointer ptr) const;//
            size_type       max_size() const;
            size_type	    count(const key_type& k) const;

//ElementAccess
            mapped_type&    operator[](const key_type& k);


//Modifiers:
            bool            insert(pointer value);
            void	        erase(iterator to_remove);
            void	        clear();
            

//***private_method***//

        private:
            node_pointer	node_insert(pointer value);
            node_pointer	new_minimum(pointer value);
            node_pointer	new_maximum(pointer value);
			node_pointer    node_init(pointer value, node_pointer new_parent, bool is_left = 0);

			node_pointer	root_init(pointer value);
            bool	        check_balance(node_pointer ptr);
			bool	        ll_rotation(node_pointer ptr);
            bool	        lr_rotation(node_pointer ptr);
            bool	        rl_rotation(node_pointer ptr);
            bool	        rr_rotation(node_pointer ptr);
			void	        l_rotation(node_pointer ptr);
            void	        r_rotation(node_pointer ptr);

            void	        root_erase();
			void	        node_erase(node_pointer ptr);
            void	        node_clear(node_pointer ptr);
            void            node_destroy(node_pointer ptr);
            void            relink(node_pointer ptr);
    		node_pointer	unlink(node_pointer ptr, bool is_left);

    };

//constructor
    template <class T, class Compare, class Alloc>
    RBTree<T, Compare, Alloc>::RBTree(const key_compare& compare, const allocator_type& v_alloc,
    const node_allocator_type& n_alloc) //map의 생성자와 동일한 c식으로 트리생성자 생성
    :comp(compare), value_alloc(v_alloc), node_alloc(n_alloc) //key값을 비교하기위한 전달받은 comp와 value(pair)와 node를 할당하기 위한 할당자를 초기화
    {
        end_node = node_alloc.allocate(1);
        node_alloc.construct(end_node, node_type());//노드의 디폴트는 전부다 null
        root = end_node; //생성초기에는 root가 end_node를 가리키고있도록 만들었습니다. operate =
        end_node->right = end_node;
        end_node->left = end_node;
        end_node->parent = end_node;
        end_node->red = false; //초기화 되지않는 end_node의 value(pair)포인터는 null
    };

//infos
    template <class T, class Compare, class Alloc>
    bool	RBTree<T, Compare, Alloc>::empty() const { return root == end_node; }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::size_type       
        RBTree<T, Compare, Alloc>::size() const //insert할 때 하나씩 더해줄까?
    {
        return (check_size(root));
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::size_type       
        RBTree<T, Compare, Alloc>::check_size(node_pointer ptr) const
    {
        size_type	size;

        size = 1; 
        if (!ptr->value)// 재귀 베이스 컨디션
            return 0;
        size += check_size(ptr->left);
        size += check_size(ptr->right);
        return size;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::size_type       
        RBTree<T, Compare, Alloc>::max_size() const
    {
        return (node_alloc.max_size());
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::size_type       
        RBTree<T, Compare, Alloc>::count(const key_type& k) const
    {
        if (pos_find(k) != end_node)
            return 1;
        return 0;
    }

//ElementAccess
    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::mapped_type&            //k 가 컨테이너에 있는 요소의 키와 일치 하면 함수는 매핑된 값에 대한 참조를 반환합니다. 
        RBTree<T, Compare, Alloc>::operator[](const key_type& k)// k 가 컨테이너에 있는 요소의 키와 일치하지 않으면 함수는 해당 키가 있는 새 요소를 삽입하고 매핑된 값에 대한 참조를 반환합니다
    {
        node_pointer    ptr(pos_find(k)); 
        value_type*     new_value(NULL); //empty parentheses interpreted as a function declaration [-Wvexing-parse] 에러

        if (ptr != end_node)
            return ptr->value->second;
        new_value = value_alloc.allocate(1); //sizeof(value_type) 
        value_alloc.construct(new_value, make_pair(k, mapped_type()));
        insert(new_value);
        return (new_value->second);
    }    

//iterators:

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::iterator	
        RBTree<T, Compare, Alloc>::begin()
    {
        iterator	it(end_node->left);

        return it;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::const_iterator	
        RBTree<T, Compare, Alloc>::begin() const
    {
        const_iterator	it(end_node->left);

        return it;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::iterator	
        RBTree<T, Compare, Alloc>::end()
    {
        iterator	it(end_node);

        return it;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::const_iterator	
        RBTree<T, Compare, Alloc>::end() const
    {
        const_iterator	it(end_node);

        return it;
    }

   template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::iterator	
        RBTree<T, Compare, Alloc>::find(const key_type& k)
    {
        iterator	pos(pos_find(k));

        return pos;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::const_iterator	
        RBTree<T, Compare, Alloc>::find(const key_type& k) const
    {
        const_iterator	pos(pos_find(k));

        return pos;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::node_pointer	
        RBTree<T, Compare, Alloc>::pos_find(const key_type& k)	const
    {
        node_pointer	ptr(root);//루트노드 생성
        bool			is_left;

        while (ptr != end_node)//노드의 처음부터 끝까지 탐색
        {
            if ((is_left = comp(k, ptr->key())) == comp(ptr->key(), k)) //같은 것을 찾은상황
                return ptr;
            if (is_left)
                ptr = ptr->left;//찾고자하는 k가 더 작으면 왼쪽으로
            else
                ptr = ptr->right;//찾고자하는 k가 더 크면 오른쪽으로
        }
        return ptr;//끝까지 못 찾을 경우 end_node로 리턴
    };

//Modifiers:

    template <class T, class Compare, class Alloc>
    bool    RBTree<T, Compare, Alloc>::insert(pointer value) //pair 
    {
        if (pos_find(value->first) != end_node) //만약 삽입하고자하는 값이 있는경우 false리턴
            return false;
        if (empty())//최초의 노드를 삽입하는 경우 구분
            return check_balance(root_init(value));
        return check_balance(node_insert(value));
    };

    template <class T, class Compare, class Alloc>
    void	RBTree<T, Compare, Alloc>::erase(iterator to_remove) //이중블랙이 하나도 구현되지않음 구조를 다시짜야할듯
    {
        node_pointer	ptr(to_remove.get_node());

        if (ptr == root)
            return root_erase();
        return node_erase(ptr);
    }  

    template <class T, class Compare, class Alloc>
    void	RBTree<T, Compare, Alloc>::clear()
    {
        if (empty()) //root 와 end_node가 같은경우
            return ;
        if (root->left != end_node)
            node_clear(root->left);
        if (root->right != end_node)
            node_clear(root->right);
        node_destroy(root);
        root = end_node;//초기 생성자의 상태와 동일시 시켜줌.
        end_node->right = end_node;
        end_node->left = end_node;
        end_node->parent = end_node;
    }

//***private_method***//

    template <class T, class Compare, class Alloc> 
    typename RBTree<T, Compare, Alloc>::node_pointer	
        RBTree<T, Compare, Alloc>::node_insert(pointer value) //pair 값
    {
        node_pointer	new_parent; //새로운 부모노드
        node_pointer	ptr(root);// 루트 복사생성 
        bool			is_left; //?

        if (comp(value->first, end_node->left->key()))//삽입하고자하는 pair 키 값과 end_node의 왼쪽값 비교 // root_init한뒤 첫 node_insert면 결국 root의 키값과 비교하는 것이겠네요
            return new_minimum(value); //최소값
        if (comp(end_node->right->key(), value->first))//end_node의 우측값과 삽입하고자하는 pair 키 값 비교 
            return new_maximum(value); //최대값
        //node_insert의 if() 최대최소구문에 걸리지않음.
        while (ptr != end_node)//root에서부터 end에 도달할 때까지 탐색
        {            //ptr(최초 root)포인터의 키값과 삽입하고자하는 value값의 key를 비교하며 탐색 후, value가 작으면 ptr을 ptr->left로 반대의 경우에는 ptr->right로 옮김
            new_parent = ptr; //end_node만나기 직전 부모포인터를 저장
            is_left = comp(value->first, ptr->key());
            if (is_left)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        return node_init(value, new_parent, is_left);
    };

    template <class T, class Compare, class Alloc> 
    typename RBTree<T, Compare, Alloc>::node_pointer	
        RBTree<T, Compare, Alloc>::new_minimum(pointer value)// 새key와 end_node의 left키 ('0'<-0)  비교후 새key가 작은경우
    {
        RBTree<T, Compare, Alloc>::node_pointer	parent(end_node->left); // 비교했던 부모는 end_node의 좌측값
        RBTree<T, Compare, Alloc>::node_pointer	new_node(node_alloc.allocate(1));

        node_alloc.construct(new_node, node_type(value));//새 node생성
        new_node->parent = parent;//노드입장) 새노드의 부모를 비교했던 말단의 좌측값으로 연결
        parent->left = new_node; //endleft 즉,부모입장) 새로연결되는 노드를 자식으로 받음
        new_node->right = end_node; //새노드의 우측
        new_node->left = end_node; //새노드의 좌측은 end_node값을 가짐
        end_node->left = new_node; //end_node의 좌측은 새노드의 값을 가짐?
        return new_node; //새노드반환
    }

    template <class T, class Compare, class Alloc> 
    typename RBTree<T, Compare, Alloc>::node_pointer	
        RBTree<T, Compare, Alloc>::new_maximum(pointer value)
    {
        node_pointer	parent(end_node->right);
        node_pointer	new_node(node_alloc.allocate(1));

        node_alloc.construct(new_node, node_type(value));
        new_node->parent = parent;
        parent->right = new_node;
        new_node->right = end_node;
        new_node->left = end_node;
        end_node->right = new_node;
        return new_node;
    }

    template <class T, class Compare, class Alloc> 
    typename RBTree<T, Compare, Alloc>::node_pointer 
        RBTree<T, Compare, Alloc>::node_init(pointer value, node_pointer new_parent, bool is_left)
    {
        node_pointer	new_node(node_alloc.allocate(1)); //새 삽입값 할당

        node_alloc.construct(new_node, node_type(value)); //새 삽입값 노드형태 생성
        new_node->left = end_node; //새 삽입값
        new_node->right = end_node;
        new_node->parent = new_parent;
        if (is_left)//자식이 좌측인지 우측인지 확인
            new_parent->left = new_node;
        else
            new_parent->right = new_node;
        return new_node;
    }

    template <class T, class Compare, class Alloc> 
    typename RBTree<T, Compare, Alloc>::node_pointer	
        RBTree<T, Compare, Alloc>::root_init(pointer value) //초기 root는 end_node 였음 
    {
        root = node_alloc.allocate(1);
        node_alloc.construct(root, node_type(value));//삽입하고자하는 pair형태를 노드형태로 변환해 생성
        root->parent = end_node; //root의 부모를 포함한 모든 leaf값들은 end_node라는 nil을 가리킴
        root->right = end_node;
        root->left = end_node;
        end_node->left = root; //nil을 표현하는 end_node의 부모와 자식값들은 root를 가리키도록 설정
        end_node->right = root;//end_node는 최대 최소값을 좌, 우로 나눠 저장하는 역할을 하도록 쓰입니다.
        end_node->parent = root;
        return root; //방금 삽입한 최초의 root를 반환
    }
    /*               초기 root_init의 상태
                           End
                            |
                           root 5 (R)
                          /    \
                       end    end
    */
   /*                초기 end_node의 상태
                           Root
                            |
                            end 5 (B) 
                          /    \
                       Root    root
   */

    template <class T, class Compare, class Alloc> 
    bool	RBTree<T, Compare, Alloc>::check_balance(node_pointer ptr)
    {//root값 또는 node_init의 리턴값을 전달받음
        if (ptr == root) //파라미터가 루트인 경우 red->black
            ptr->red = false; 
        else if (ptr->parent->red) //현재 ptr이 레드
        {
            node_pointer	grandparent(ptr->grandparent());// 할아버지 등판

            if (ptr->uncle()->red) //삼촌이 붉은색일 경우엔 재색칠과정
            {
                ptr->uncle()->red = false;
                ptr->parent->red = false;
                grandparent->red = true;
                return	check_balance(grandparent);//할아버지기준으로 색 재검사
            }// 아래 조건은 삼촌이 검정인 상태
            else if (grandparent->left != end_node && ptr == grandparent->left->left)        //end는 항상 최소 최대값을 담아 놓기에 grandparent->left != end_node 조건이 없으면
                return ll_rotation(ptr); //내 위치가 할아버지의 좌좌손자인 동시에 내 부모가 말단이 아닐 때  //위의 경우 부득이하게 grandparent->end->left (최솟값)을 가리키게 되므로 
            else if (grandparent->left != end_node && ptr == grandparent->left->right)       //부모의 노드가 end_node가 아닌지 검사해주는 조건이 필요합니다.
                return lr_rotation(ptr); //내 위치가 할아버지의 좌우손자인 동시에 내 부모가 말단이 아닐 때
            else if (grandparent->right != end_node && ptr == grandparent->right->right)
                return rr_rotation(ptr); //내 위치가 할아버지의 우우손자인 동시에 내 부모가 말단이 아닐 때
            else if (grandparent->right != end_node && ptr == grandparent->right->left)
                return rl_rotation(ptr); //내 위치가 할아버지의 우좌손자인 동시에 내 부모가 말단이 아닐 때
        }
        return true;//전달받은 값이 루트인경우 색깔만 블랙으로 바꿔주고 끝
    }

    template <class T, class Compare, class Alloc>
    bool	RBTree<T, Compare, Alloc>::ll_rotation(node_pointer ptr)
    {
        std::cout << "ll!"<< std::endl;
        node_pointer	grandparent(ptr->grandparent());
        bool			tmp(grandparent->red);//아마 블랙이었겠지? 일단 저장
                                                                    //    부모
        r_rotation(grandparent); //부모 기준으로 조부모가 시계방향회전     //  손자    조부모
        grandparent->red = ptr->parent->red; //할아버지는 부모의색, 부모는 할아버지의 색을로 바꿈
        ptr->parent->red = tmp;
        return check_balance(ptr); //좌좌 손자기준으로 재검사 
    }

    template <class T, class Compare, class Alloc>
    bool	RBTree<T, Compare, Alloc>::lr_rotation(node_pointer ptr)
    {
        std::cout << "lr!"<< std::endl; //조부모 -> 자식 -> 부모
        l_rotation(ptr->parent); // 자식이 부모 반시계방향으로 회전 (자식의 좌측값을 부모의 우측에 붙이고 그 부모를 자식이 좌측으로 가짐)
        return ll_rotation(ptr);// 일렬로 좌측 red인상태
    }

    template <class T, class Compare, class Alloc>
    bool	RBTree<T, Compare, Alloc>::rr_rotation(node_pointer ptr)
    {
        std::cout << "rr!"<< std::endl;
        node_pointer	grandparent(ptr->grandparent());
        bool			tmp(grandparent->red);
                                                                   //    부모
        l_rotation(grandparent); //부모 기준으로 조부모가 반시계방향회전   //  조부모    손자
        grandparent->red = ptr->parent->red; //색변경
        ptr->parent->red = tmp;
        return check_balance(ptr);
    }

    template <class T, class Compare, class Alloc>
    bool	RBTree<T, Compare, Alloc>::rl_rotation(node_pointer ptr)
    {
        std::cout << "rl!"<< std::endl; //조부모 -> 자식 -> 부모
        r_rotation(ptr->parent);// 자식이 부모 시계방향으로 회전 (자식의 우측값을 부모의 좌측에 붙이고 그 부모를 자식이 우측으로 가짐)
        return rr_rotation(ptr);// 일렬로 우측 red인상태
    }

    template <class T, class Compare, class Alloc>
    void	RBTree<T, Compare, Alloc>::r_rotation(node_pointer ptr)
    {
        node_pointer	left(ptr->left);

        left->parent = ptr->parent;
        if (ptr->parent != end_node)// ptr의 부모가 end_node인지 확인
            ptr == ptr->parent->left ?	ptr->parent->left = left :	ptr->parent->right = left;//기존 할아버지(ptr)위치에 있던 값의 부모 입장에서 ptr이 좌측인지 우측인지 따져서 ptr을 left주소로 바꿔 이어줌
        else
            root = left;
        //루트값을 재설정
        left->right->parent = ptr; //가장 말단의 값부터 바꿔줌 ptr의 좌측자식인 left에 딸린 우측자식입장에서 보는 부모를 left에서 ptr로 재설정 (부모부터 바꾸면 값을 잃어버림)
        ptr->left = left->right; //ptr의 왼쪽값에 즉 원래 left였던 값 대신 left의 오른쪽 자식인 left->right(최대한 ptr과 가까운 값)으로 바꿔줌
        left->right = ptr; //ptr의 좌측자식이었던 left가 원래 부모ptr을 오른쪽 자식으로 가짐.
        ptr->parent = left; //ptr도 left를 부모포인터로 인식시킴
        return ;
    }

    template <class T, class Compare, class Alloc>
    void	RBTree<T, Compare, Alloc>::l_rotation(node_pointer ptr)
    {
        node_pointer	right(ptr->right);//전달받은 ptr은 부모 right값은 ptr의 오른쪽자식 

        right->parent = ptr->parent;
        if (ptr->parent != end_node)//루트가 아니면 ptr 위치에 있던 값의 부모입장에서 ptr이 좌측인지 우측인지 따져서 주소바꿔 이어줌
            ptr == ptr->parent->left ?	ptr->parent->left = right :	ptr->parent->right = right;
        else
            root = right;
        right->left->parent = ptr; //가장 말단의 값 부터 바꿔줌 right에 딸린 우측 자식 입장에서 보는 부모를 right에서 ptr로 재설정
        ptr->right = right->left; //ptr의 오른쪽 값에 즉 원래 right였던 값 대신 right의 왼쪽 자식인 (최대한 ptr과 가장 가까운값)end(*) 으로 바꿔줌
        right->left = ptr; // ptr의 우측자식이었던 right가 원래 부모ptr을 좌측자식으로 가짐
        ptr->parent = right;//ptr도 left를 부모포인터로 인식시킴
        return ;
    }

    template <class T, class Compare, class Alloc>
    void    RBTree<T, Compare, Alloc>::root_erase() //root기준 삭제알고리즘 적용
    {
        node_pointer	new_root;
        node_pointer	orphan;
         //루트에 자식이 한쪽 노드만 달려있는경우 // 초기는 end의 자식과 부모가 root를 가리킴
        if (root == end_node->left) //root의 값이 최소값이면, root의 right를 최소로 변경
            end_node->left = root->right;
        if (root == end_node->right) //root의 값이 최대값이면, root의 left를 최대로 변경
            end_node->right = root->left; 
        if (root->right == end_node && root->left == end_node) //루트에 자식이없는 경우 즉, 루트만 있는 경우 해당
            return clear();
        //루트의 두 자식중에서 딸린 자식이 더 많은 쪽이 새로운 후계자가 되도록설정
        if (root->right == end_node || check_size(root->right) < check_size(root->left))
        {
            new_root = root->left;
            orphan = root->right;
        }
        else
        {
            new_root = root->right;
            orphan = root->left;
        }
        node_destroy(root); //뭔가 이상함
        root = new_root;
        root->parent = end_node;
        end_node->parent = root; //end가 저장하는 정보 변경
        relink(orphan);
    }

    template <class T, class Compare, class Alloc>
    void    RBTree<T, Compare, Alloc>::node_erase(node_pointer ptr)
    {
        node_pointer	parent(ptr->parent);
        node_pointer	orphan(end_node);

        if (ptr == end_node->left) //최대 최소값 수정
            end_node->left = parent;
        if (ptr == end_node->right)
            end_node->right = parent;
        if (ptr->left == end_node && ptr->right == end_node)
        {
            if (ptr == parent->left)
                parent->left = end_node;
            else
                parent->right = end_node;
        }
        else
            orphan = unlink(ptr, (ptr->right == end_node || check_size(ptr->right) < check_size(ptr->left)));
		node_destroy(ptr);
		relink(orphan);
    }

    template <class T, class Compare, class Alloc>
    void    RBTree<T, Compare, Alloc>::node_clear(node_pointer ptr)
    {
        if (ptr->left != end_node)
            node_clear(ptr->left);
        if (ptr->right != end_node)
            node_clear(ptr->right);
        node_destroy(ptr);
    }

    template <class T, class Compare, class Alloc>
    void    RBTree<T, Compare, Alloc>::node_destroy(node_pointer ptr)
    {
        value_alloc.destroy(ptr->value);
        value_alloc.deallocate(ptr->value, 1);
        node_alloc.destroy(ptr);
        node_alloc.deallocate(ptr, 1);
    }

    template <class T, class Compare, class Alloc>
    void    RBTree<T, Compare, Alloc>::relink(node_pointer orphan)
    {
        if (!empty() && orphan != end_node)
        {
            node_pointer	parent;
            node_pointer	ptr(root);
            bool			is_left;
            //기존 부모와 연결하려면 정보가 있어야하는데 고아정보밖에없음.
            while (ptr != end_node) //새로 배정받은 루트에서부터 단절된 고아노드가 들어갈 최적의 위치 파악
            {
                parent = ptr;
                is_left = comp(orphan->key(), ptr->key());
                if (is_left)
                    ptr = ptr->left;
                else
                    ptr = ptr->right;
            }
            orphan->parent = parent;
            if (is_left)
                parent->left = orphan;
            else
                parent->right = orphan;
        }
        return ;
    }

    template <class T, class Compare, class Alloc>
    typename RBTree<T, Compare, Alloc>::node_pointer
        RBTree<T, Compare, Alloc>::unlink(node_pointer ptr, bool is_left)
    {
        node_pointer	tmp;
        if (is_left)
            tmp = ptr->left;
        else
            tmp = ptr->right;
        ptr == ptr->parent->left ?
            ptr->parent->left = tmp : ptr->parent->right = tmp;
        tmp->parent = ptr->parent;
        if (is_left)
            return ptr->right;
        return ptr->left;
    }

} // namespace ft

#endif