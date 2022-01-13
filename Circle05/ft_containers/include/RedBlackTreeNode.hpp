#ifndef REDBLACKTREENODE_HPP
#define REDBLACKTREENODE_HPP

namespace ft
{
    template <  class T >
    struct RBTreeNode
	{
		typedef	struct		RBTreeNode*					pointer;
		typedef	const		pointer						const_pointer;
		typedef	struct		RBTreeNode&					reference;
		typedef				T							value_type;
		typedef				value_type*					value_pointer;

		typedef	typename	value_type::first_type		key_type;

		pointer			parent;
		pointer			left;
		pointer			right;
		value_pointer	value;
		bool			red;

		explicit RBTreeNode(value_pointer src_value = NULL,
			pointer const& src_parent = NULL, pointer const& src_left = NULL, pointer const& src_right = NULL)
		: parent(src_parent), left(src_left), right(src_right), value(src_value), red(true)
		{}

		RBTreeNode(RBTreeNode const & src)
		{
			*this = src;
		}		

		reference	operator=(RBTreeNode const & rhs)
		{
			if (this != &rhs)
			{
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				value = rhs.value;
				red = rhs.red;
			}
			return *this;
		}

		key_type&		key() const { return value->first; }

		pointer			grandparent() { return parent->parent; }

		const_pointer	grandparent() const { return parent->parent; }

		pointer	uncle()
		{
			pointer	gp(grandparent());

			if (parent == gp->left)
				return gp->right;
			return gp->left;
		}

		const_pointer	uncle() const
		{
			pointer	gp(grandparent());

			if (parent == gp->left)
				return gp->right;
			return gp->left;
		}

		bool	operator==(RBTreeNode const & rhs) const
		{
			return (*value == *(rhs.value));
		}

		bool	operator!=(RBTreeNode const & rhs) const
		{
			return !(*value == *(rhs.value));
		}
    };

}

#endif