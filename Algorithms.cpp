#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

class Node {
public:
	char value;
	Node* next;

	Node() {
		value = '\0';
		next = nullptr;
	}
};

class LinkedList { //single linked list
public:
	Node* head;

	LinkedList(); // Constructor
	
	void insert(const char character);
	void printAll();
	void convert(LinkedList& resultList);
	void StepByStep(LinkedList& resultList);
	void deleteList();
	~LinkedList() {
		deleteList();
	}
};

void LinkedList::deleteList() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}


class CharStack {
public:
	Node* top;
	CharStack() : top(nullptr) {}
	void push(char value) {
		Node* newNode = new Node();
		newNode->value = value;
		newNode->next = top;
		top = newNode;
	}

	char pop() {
		if (top == nullptr) { return '\0'; } // Indicates an empty stack
		Node* temp = top;
		char value = top->value;
		top = top->next;
		delete temp;
		return value;
	}

	void print() {
		bool space = false;
		Node* temp = top;  // Use a temporary pointer to traverse the stack
		CharStack reverse;

		while (temp != nullptr) { 
			if (temp->value == '-') {
				cout << temp->value;
			}
			else if (temp->value == 'N') {
				temp = temp->next->next->next;
			}
			else if (temp->value == ' ') {
				temp = temp->next;
				if (temp == nullptr) break;
				if (temp->value == '-') {
					cout << temp->value;
					temp = temp->next;
					if (temp == nullptr) break;
					while (temp != nullptr && isdigit(temp->value)) {
						reverse.push(temp->value);
						temp = temp->next;
					}
				}
				else {
					while (temp != nullptr && isdigit(temp->value)) {
						reverse.push(temp->value);
						temp = temp->next;
					}
					if (temp == nullptr) {
						break; 
					}

					if (space == false) {
						reverse.push(temp->value);
					}
					space = true;
				}
				while (!reverse.isEmpty()) {
					cout << reverse.pop();
				}
				cout << ' ';

			}
			else if (temp->value == '|') {
				temp = temp->next; // Move past the '|'
				if (temp == nullptr) {
					break; // Safeguard against a null pointer dereference
				}
				while (temp != nullptr && isdigit(temp->value)) { // Ensure temp is not null before accessing temp->value
					reverse.push(temp->value);
					temp = temp->next;
				}

				while (!reverse.isEmpty()) {
					cout << reverse.pop();
				}
				space = true;
				cout << ' ';
			}

			else {
				cout << temp->value << ' ';
				space = true;
			}
			if (temp != nullptr) {
				temp = temp->next;
			}

		}
		cout << endl;  // Add a newline at the end
		
	}

	char peek() {
		return top ? top->value : '\0'; // Return '\0' if stack is empty
	}

	bool isEmpty() {
		return top == nullptr;
	}

	~CharStack() {
		while (!isEmpty()) {
			pop(); // Pop should handle deletion of the top node.
		}
	}
};


LinkedList::LinkedList() {
	head = nullptr;
}


void LinkedList::insert(const char character) {
	Node* newNode = new Node();
	newNode->value = character;

	if (head == nullptr) { // first node
		head = newNode;
	}
	else {
		Node* temp = head;
		while (temp->next != nullptr) { // to find the last node, by keep jumping the next pointers of the nodes
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

void lineInput(LinkedList& LL) {
	char character, prevCharacter = '\0';
	bool isPrevDigit = false;
	cin >> character;
	while (character != '.') {
		if (isdigit(character)) {
			if (!isPrevDigit) { // Start of a new number
				LL.insert('|'); 
				isPrevDigit = true;
			}
		}
		else {
			if (isPrevDigit) { // End of a number
				LL.insert('|'); 
				isPrevDigit = false;
			}
		}
		LL.insert(character);
		prevCharacter = character;
		cin >> character;
	}
	if (isdigit(prevCharacter)) { // If the last character was a digit, close the marker
		LL.insert('|');
	}
}

void LinkedList::printAll() {
	Node* current = head;
	while (current != nullptr) {
		cout << current->value;
		current = current->next;
	}
}

void LinkedList::StepByStep(LinkedList& resultList) {
	CharStack stack;
	CharStack reverse;
	char type;
	Node* current = head;
	int a, b, c, n, temp, hello, power = 1, digits = 0, result = 0;
	bool negative = false;
	while (current != nullptr) {

		if (isspace(current->value)) {
			current = current->next;
		}
		if (current == nullptr) break;
		if (isdigit(current->value)) {
			if (current->next == nullptr) break;
			if (isdigit(current->next->value)) {
				stack.push('|');
				while (isdigit(current->value)) {
					stack.push(current->value);
					current = current->next;
				}
				stack.push('|');
			}
			else {
				stack.push(current->value);
			}

		}
		else {
			if (current == nullptr) break;
			cout << current->value << " ";
			if (!stack.isEmpty()) {
				stack.print();
			}

			a = 0, b = 0, power = 1;

			if (stack.peek() == '-') {
				c = stack.pop() - '0';
				a = stack.pop() - '0';
				a = -a;
			} 
			else if (stack.peek() == ' ') {
				stack.pop();
				if (stack.peek() == '-') {
					negative = true;
					stack.pop();
				}
				while (isdigit(stack.peek())) {
					temp = (stack.pop() - '0') * power;
					a += temp;

					power *= 10;
				}
				stack.pop();
				if (negative) {
					a = -a;
					negative = false;
				}
			}
			else if (stack.peek() == '|') {
				stack.pop();
				while (isdigit(stack.peek())) {
					temp = (stack.pop() - '0') * power;
					a += temp;

					power *= 10;
				}
				stack.pop();
			}
			else {
				a = stack.pop() - '0';
			}

			power = 1;
			
			if (!stack.isEmpty()) {
				if (stack.peek() == '-') {
					c = stack.pop() - '0';
					b = stack.pop() - '0';
					b = -b;
				}
				else if (stack.peek() == ' ') {
					stack.pop();
					if (stack.peek() == '-') {
						negative = true;
						stack.pop();
					}
					while (isdigit(stack.peek())) {
						temp = (stack.pop() - '0') * power;
						b += temp;

						power *= 10;
					}
					stack.pop();
					if (negative) {
						b = -b;
						negative = false;
					}
				}
				else if (stack.peek() == '|') {
					stack.pop();
					while (isdigit(stack.peek())) {
						temp = (stack.pop() - '0') * power;
						b += temp;

						power *= 10;
					}
					stack.pop();
				}
				else {
					b = stack.pop() - '0';
				}
			}
			
			// MATH
			type = current->value;
			switch (type) {
			case '+':
				result = b + a;
				break;
			case '-':
				result = b - a;
				break;
			case '/':
				if (a == 0) {
					cout << "ERROR" << endl;
					return;
				}
				result = b / a;
				break;
			case '*': 
				result = b * a;
				break;
			case 'N':				
				result = -a;
				n = b;
				stack.push(' ');
				int digits = (n == 0) ? 1 : static_cast<int>(log10(n)) + 1;
				int divisor = static_cast<int>(pow(10, digits - 1));
				if (divisor == 0) break;
				while (digits != 0) {
					char digit = (n / divisor) + '0';
					stack.push(digit);

					// Remove the leading digit from the number
					n %= divisor;
					divisor /= 10;

					digits--;
				}
				stack.push(' ');
			} 

			if (b == 0 && current->value == 'N' && isdigit(a)) {
				stack.push('N');
			}

			if (result < 0) {
				n = abs(result);
				if (n > 9) {
					stack.push(' ');
					int digits = (n == 0) ? 1 : static_cast<int>(log10(n)) + 1;
					int divisor = static_cast<int>(pow(10, digits - 1));
					while (digits != 0) {
						char digit = (n / divisor) + '0';
						stack.push(digit);

						// Remove the leading digit from the number
						n %= divisor;
						divisor /= 10;

						digits--;
					}
					stack.push('-');
					stack.push(' ');

				}
				else {
					stack.push(abs(result) + '0');
					stack.push('-');
				}
			} else if (result > 9) {
				stack.push(' ');
				int digits = (result == 0) ? 1 : static_cast<int>(log10(result)) + 1;
				hello = result;
				int divisor = static_cast<int>(pow(10, digits - 1));
				while (digits != 0) {
					char digit = (hello / divisor) + '0';
					stack.push(digit);

					// Remove the leading digit from the number
					hello %= divisor;
					divisor /= 10;

					digits--;
				}
				stack.push(' ');

			}
			else {
				stack.push(result + '0');
			}


		}
		current = current->next;
	}
	cout << result << endl;

}



void LinkedList::convert(LinkedList& resultList) {
	CharStack opStack; // Operator stack

	Node* current = head;
	while (current != nullptr) {
		if (current->value == '|') {
			current = current->next;
			while (current->value != '|') {
				resultList.insert(current->value);
				current = current->next;
			}
			resultList.insert(' ');
		}
		else if (current->value == 'N') {
			opStack.push(current->value);
		}
		else if (current->value == '+' || current->value == '-') {
			while (!opStack.isEmpty() && (opStack.peek() == '+' || opStack.peek() == '-' || opStack.peek() == '*' || opStack.peek() == '/')) {
				resultList.insert(opStack.pop());
				resultList.insert(' ');
			}
			opStack.push(current->value);
		}
		else if (current->value == '*' || current->value == '/') {
			while (!opStack.isEmpty() && (opStack.peek() == '*' || opStack.peek() == '/')) {
				resultList.insert(opStack.pop());
				resultList.insert(' ');
			}
			opStack.push(current->value);
		}
		else if (current->value == '(') {
			opStack.push(current->value);
		}
		else if (current->value == ')') {
			// Pop until finding '('
			while (!opStack.isEmpty() && opStack.peek() != '(') {
				resultList.insert(opStack.pop());
				resultList.insert(' ');
			}
			opStack.pop(); // Remove '(' from the stack
		}
		
		current = current->next;
	}
	while (!opStack.isEmpty()) {
		resultList.insert(opStack.pop());
		if (!opStack.isEmpty()) {
			resultList.insert(' ');
		}
	}
}

int main() {
	int n;
	cin >> n;

	LinkedList LL;
	LinkedList resultList;
	LinkedList steps;

	for (int i = 0; i < n; i++) {
		lineInput(LL);
		resultList = LinkedList(); 
		LL.convert(resultList);

		resultList.printAll(); 
		cout << endl; 
		resultList.StepByStep(resultList);
		LL.deleteList();
		resultList.deleteList();
	}
	return 0;
}