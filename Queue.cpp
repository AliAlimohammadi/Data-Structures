/* Queue - Circular Array implementation in C++*/
#include <iostream>

using namespace std; 

#define MAX_SIZE 101    //maximum size of the array that will store Queue. 

// Creating a class named Queue.
class Queue
{
    private:
	    int arr[MAX_SIZE];
	    int front, rear; 
    public:
	    // Constructor - set front and rear as -1. 
	    // We are assuming that for an empty Queue, both front and rear will be -1.
	    Queue()
	    {
		    front = -1; 
		    rear = -1;
	    }
	
	    // To check wheter Queue is empty or not
	    bool IsEmpty() { return (front == -1 && rear == -1); }

	    // To check whether Queue is full or not
	    bool IsFull() { return (rear + 1) % MAX_SIZE == front ? true : false; }

	    // Inserts an element in queue at rear end
	    void Enqueue(int x)
	    {
		    cout << "Enqueuing " << x << endl;
		    
		    if(IsFull())
		    {
			    cout << "Error: Queue is Full.\n";
			    return;
		    }
		    
		    if (IsEmpty())
			    front = rear = 0;
		    else
		        rear = (rear + 1) % MAX_SIZE;
		    
		    arr[rear] = x;
	    }
	    
	    // Removes an element in Queue from front end.
	    int Dequeue()
	    {
		    int x = -1;
		    cout << "Dequeuing\n";
		    if(IsEmpty())
			    cout << "Error: Queue is Empty.\n";
		    else if (front == rear)
			    rear = front = -1;
		    else
		    {
		        x = arr[front];
		        front = (front + 1) % MAX_SIZE;
		    }
		    
		    return x;
	    }
	    
	    /*
	    Printing the elements in queue from front to rear.
	    This function is only to test the code.
	    This is not a standard function for Queue implementation.
	    */
	    void printQueue()
	    {
		    // Finding number of elements in queue  
		    int count = (rear + MAX_SIZE - front) % MAX_SIZE + 1;
		    cout << "Queue:\n";
		    for(int i = 0; i < count; i++)
		    {
			    int index = (front + i) % MAX_SIZE;   // Index of element while travesing circularly from front
			    cout << arr[index] << ' ';
		    }
		    cout << endl;
	    }
};

int main()
{
    Queue queue;
    queue.Enqueue(2);   queue.printQueue();
    queue.Enqueue(4);   queue.printQueue();
    queue.Enqueue(6);   queue.printQueue();
    queue.Dequeue();    queue.printQueue();
    queue.Enqueue(8);   queue.printQueue();
    return 0;
}