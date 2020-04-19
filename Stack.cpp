#include <iostream>

using namespace std; 

#define MAX 1000    // Maximum size of Stack

class Stack
{
    private:
        int top;
    
    public:
        int arr[MAX]; 
  
        Stack() { top = -1; }
        
        bool push(int x)
        {
            if (top >= (MAX - 1))
            {
                cout << "Stack Overflow\n";
                return false;
            }
            
            arr[++top] = x;
            cout << x << " pushed into the stack.\n";
            return true;
        }
        
        int pop()
        {
            if (top < 0)
            {
                cout << "Stack Underflow\n"; 
                return 0; 
            }
            
            return arr[top--];
        }
        
        bool isEmpty() { return top < 0; }
};

int main()
{
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << stack.pop() << " popped from stack.\n";
    return 0;
}