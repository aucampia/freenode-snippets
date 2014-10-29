#include <string>
#include <iostream>
#include <memory>
#include <cassert>

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
			assert( !this->m_next );
			return ( this->m_next = std::unique_ptr< node >( new node() ) ).get();
		}
		node* next_node() const
		{
			return this->m_next.get();
		}
		void pop_back()
		{
			this->m_next = std::unique_ptr< node >();
		}

		const T& get_value() const
		{
			return this->m_value;
		}
		const T& set_value( const T& value )
		{
			this->m_value = value;
		}

	private:
		T m_value;
		std::unique_ptr< node > m_next;
	};
public:
	linked_list()
		:
			m_size( 0 ),
			m_back( NULL )
	{
		
	}
	void push_back( const T& value )
	{
		node& next = append_node();
		next.set_value( value );
	}
	void pop_back()
	{
		//std::cout << "this->m_size = " << this->m_size << std::endl;
		assert( this->m_size > 0 );
		if ( this->m_front.get() != this->m_back )
		{
			node* second_last = this->m_front.get();
			while ( second_last->next_node() != this->m_back )
			{
				second_last = second_last->next_node();
			}
			second_last->pop_back();
			this->m_back = second_last;
		}
		else
		{
			this->m_front = NULL;
			this->m_back = NULL;
		}
		this->m_size--;
	}
	size_t size() const
	{
		return this->m_size;
	}
	bool empty() const
	{
		return !this->m_front;
	}
	std::ostream& dump( std::ostream& out ) const
	{
		out << "[ ";
		for ( node* tmp = this->m_front.get(); tmp != NULL; tmp = tmp->next_node() )
		{
			if ( tmp != this->m_front.get() ) out << ", ";
			out << tmp->get_value();
		}
		out << " ]";
	}
private:
	node& append_node()
	{
		if ( !this->m_front )
		{
			this->m_front = std::unique_ptr< node >( new node() );
			this->m_back = this->m_front.get();
		}
		else
		{
			this->m_back = this->m_back->append_node();
		}
		this->m_size++;
		return *this->m_back;
	}
private:
	std::unique_ptr< node > m_front;
	node* m_back;
	size_t m_size;
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
	for ( int i = 0; i < 10; i++ )
	{
		list.push_back( i );
	}
	std::cout << list << std::endl;
	std::cout << list.size() << std::endl;
	std::cout << "list.empty() = " << list.empty() << std::endl;
	while( !list.empty() )
	{
		list.pop_back();
		std::cout << "list.empty() = " << list.empty() << std::endl;
	}
	std::cout << list << std::endl;
	list.push_back( 1 );
	list.push_back( 2 );
	list.push_back( 3 );
	std::cout << list << std::endl;
}
