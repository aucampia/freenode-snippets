#include <string>
#include <iostream>
#include <memory>

namespace nester {

template < typename T >
class linked_list
{
private:
	class node
	{
	public:
		node()
		{
			std::cout << "node::node() : this = " << (void*) this << std::endl;
		}
		~node()
		{
			std::cout << "node::~node() : this = " << (void*) this << std::endl;
		}
		node* append_node()
		{
			return ( this->next = std::unique_ptr< node >( new node() ) ).get();
		}
		node* next_node()
		{
			return this->next.get();
		}
		const T& get_value() const
		{
			return value;
		}
		const T& set_value( const T& value )
		{
			this->value = value;
		}
	private:
		T value;
		std::unique_ptr< node > next;
	};
public:
	linked_list()
		:
			back( NULL )
	{
		
	}
	void insert( const T& value )
	{
		node& next = append_node();
		next.set_value( value );
	}
	std::ostream& dump( std::ostream& out ) const
	{
		out << "[ ";
		for ( node* tmp = this->front.get(); tmp != NULL; tmp = tmp->next_node() )
		{
			if ( tmp != this->front.get() ) out << ", ";
			out << tmp->get_value();
		}
		out << " ]";
	}
private:
	node& append_node()
	{
		if ( !this->front )
		{
			this->front = std::unique_ptr< node >( new node() );
			this->back = this->front.get();
		}
		else
		{
			this->back = this->back->append_node();
		}
		return *this->back;
	}
private:
	std::unique_ptr< node > front;
	node* back;
	size_t size;
};

template < typename T >
std::ostream& operator << ( std::ostream& out, const linked_list< T >& in )
{
	return in.dump( out );
}

}

int main()
{
	nester::linked_list< int > list;
	list.insert( 1 );
	list.insert( 2 );
	list.insert( 3 );
	std::cout << list << std::endl;
}
