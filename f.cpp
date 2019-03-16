#include <iostream>
#include <utility>

using namespace std;
int g_construct=0;
int g_copyconstruct=0;
int g_destruct=0;

class A
{
public:
    A() : m_ptr(new int(5))
	{
		cout << "construct" << endl;
	}

	A(const A& a): m_ptr(new int(*(a.m_ptr)))
	{
		cout << "copy construct" << endl;
	}
	
	A(A&& a): m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr;
		cout << "move construct" << endl;
	}

	~A()
	{	
		cout << "deconstruct" << endl;		
		if(m_ptr != nullptr)
		{			
			delete(m_ptr);	
		}
	}
			
private:
    int* m_ptr;
};

A getA()
{
	return A();
}

void process(int& a)
{
	cout << "lvalue:" << a <<endl;
}

void process(int&& a)
{
	cout << "rvalue:" << a << endl;
}

template<typename T>
void p(T&& a)
{
	process(std::forward<T>(a));	
}

int main() {
    A&& a = getA();
	
	int b = 5;
	
	process(5);
	process(b);

    return 0;
}


