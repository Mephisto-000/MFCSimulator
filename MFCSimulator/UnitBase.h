#pragma once
class UnitBase
{

private:
	class Node {
	public:
		CPoint ptUnitLocation;
		int iUnitHeight;
		int iUnitWidth;
		
		Node* prior;
		Node* next;
	};

	Node* head;
	int iLength = 0;

public:

	UnitBase();

	void Show();

	void Create(int n);






};

