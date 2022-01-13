#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "Pair.hpp"
#include "RedBlackTree.hpp"
#include "RBTIterator.hpp"
#include <utility> //pair구현해야함
#include <functional> //less 구현해야함
#include <map>

namespace ft
{

    //std::map<int, int> a; 
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > //구현해야함
    class Map //compare와 alloc은 템플릿 초기화에 의해 따로 값을 넣지않아도 됨. main에서는 템플릿에 자료형만 두개 넣어서 생성시킬예정.
    {
        
        // Member type//
        public:
            typedef Key                                                         key_type;
            typedef T                                                           mapped_type;

            typedef ft::pair<const key_type, mapped_type>                       value_type;            
            typedef Compare                                                     key_compare;
            typedef Alloc                                                       allocator_type;
            typedef RBTree<value_type, key_compare, allocator_type>             rbtree;
            typedef ptrdiff_t                                                   difference_type;
            typedef size_t                                                      size_type;

            typedef typename allocator_type::reference                          reference;
            typedef typename allocator_type::const_reference                    const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;

            typedef typename RBTree<value_type, key_compare, Alloc>::iterator         iterator;
            typedef typename RBTree<value_type, key_compare, Alloc>::const_iterator   const_iterator;
       //     typedef typename ft::reverse_iterator<T, false>                     reverse_iterator;
        //    typedef typename ft::reverse_iterator<T, true>                      const_reverse_iterator;
        

        //----------private Member---------//

        private:
            rbtree          tree;
            key_compare     comp;
            allocator_type  alloc;


        //--------Member Function---------//

        public:
            // Canonical form //
            explicit Map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());

            // Iterators //
            iterator	begin() ;
            const_iterator	begin() const ;
            iterator	end() ;
            const_iterator	end() const ;

            // Capacity //

            // Element access //

            // Modifiers //
            ft::pair<iterator, bool> insert(const value_type &val);

            // Observers //

            // Operations //
            iterator	find(const key_type& k);

            // Allocator //

    };
    
    // Canonical form //
    template < class Key, class T, class Compare, class Alloc>
    Map<Key, T, Compare, Alloc>::Map(const key_compare& comp,
        const allocator_type& alloc) : tree(comp, alloc), comp(comp), alloc(alloc) {} //트리에 컴페어와, 할당타입값 전달

    // Iterators //
    template<class Key, class T, class Compare, class Alloc>
    typename Map<Key, T, Compare, Alloc>::iterator
    	Map<Key, T, Compare, Alloc>::begin() { return tree.begin(); } //node_pointer를 이터레이터 객체화 시킨 뒤, 반환

    template<class Key, class T, class Compare, class Alloc>
    typename Map<Key, T, Compare, Alloc>::const_iterator	
        Map<Key, T, Compare, Alloc>::begin() const { return tree.begin(); }

    template<class Key, class T, class Compare, class Alloc>
    typename Map<Key, T, Compare, Alloc>::iterator	
        Map<Key, T, Compare, Alloc>::end() { return tree.end(); }

    template<class Key, class T, class Compare, class Alloc>
    typename Map<Key, T, Compare, Alloc>::const_iterator	
        Map<Key, T, Compare, Alloc>::end() const { return tree.end(); }


    // Capacity //
    template<class Key, class T, class Compare, class Alloc>
    ft::pair<typename Map<Key, T, Compare, Alloc>::iterator, bool> 
        Map<Key, T, Compare, Alloc>::insert(const value_type &val)
    {
        iterator   first(find(val.first)); //삽입하고자하는 키의 값을 찾은 뒤, 복사생성
        bool                                    second(false);
        pointer                                 new_val(NULL);

        if (first == tree.end()) //삽입하고자하는 값이 없는경우만 들어옴
        {
            new_val = alloc.allocate(1); //1만큼 메모리에 할당
            alloc.construct(new_val, val); //할당 후, new_val의 위치에 val의 객체(pair)를 생성 //construct구조 의문1
            second = tree.insert(new_val);//new_val에 있는 객체(pair)를 tree에 삽입 //근데 false값을 받는 부분이없네 
            //tree.insert(new_val);//new_val에 있는 객체(pair)를 tree에 삽입 //근데 false값을 받는 부분이없네
            first = find(val.first); //삽입한 뒤, 삽입된 위치 포인터 반환
            //second = true; //insert의 값을 받아줘도 괜찮을 것같다는 생각이 들음 insert의 값 true false가 놀음.
        }
        return (ft::make_pair(first, second));//멤버 pair::first 반복되는 요소 또는 맵에서 동등한 키를 가진 요소를 가리키도록 설정됩니다.
    }// pair의 pair::second 요소는 새 요소를 삽입한 경우 true로 설정되고 동등한 키가 이미 있는 경우 false로 설정됩니다.

    //Operation
    template<class Key, class T, class Compare, class Alloc>
    typename Map<Key, T, Compare, Alloc>::iterator 
        Map<Key, T, Compare, Alloc>::find(const key_type& k) { return (tree.find(k)); } //tree에서 k에 해당하는 노드포인터를 찾아 이터레이터객체화 시킨 뒤, 반환

}

#endif
