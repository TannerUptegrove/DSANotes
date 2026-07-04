#include <iostream>
#include <queue>
using namespace std;

//Because we pass in the priority queue by VALUE, manipulating it
//here does not effect it in the main function.
void DisplayPriorityQueue(priority_queue<int> q) {
	if (q.empty()) {
		cout << "\n The priority queue is empty...\n";
		return;
	}

	while (!q.empty()) {
		cout << q.top() << " ";
		q.pop();
	}
	cout << endl;
}

int main()
{
	priority_queue<int> q;
	q.push(10);
	q.push(50);
	q.push(18);
	q.push(20);
	q.push(98);
	q.push(100);
		
	DisplayPriorityQueue(q);
}