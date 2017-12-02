#include <iostream>
#include <string>

class Deque{
private:
	int* _header;     //��������� �� "��������" ������       
	int* _tailler;     //��������� �� "������" ������
	int _hLenght;     //����� "���������" �������
	int _tLenght;     //����� "���������" �������
	int _size;        //����� ���� �������
	int _hCount;      //���������� ��������� � "��������" �������
	int _tCount;      //���������� ��������� � "������" �������
	int _allCount;    //����� ���������� ��������� � �������

public:
	Deque(int size);
	~Deque();
	void PushFront(int val);
	void PushBack(int val);
	int PopFront();
	int PopBack();
};

Deque::Deque(int size):                   //� ����������� �������� ������ �������
	 _header(nullptr),                    //�������������� ������ ��������� �� "��������" � "������" �������
	 _tailler(nullptr), 
	 _hLenght((int)(size / 2)),           //������ ������� "���������" � "�������" �������� ��� �������� ������� ���� �������
	 _tLenght(size - (int)(size / 2)), 
	 _size(size),                         //��������� ������ �������
	 _hCount(0),                          
	 _tCount(0),
	 _allCount(0) 
{
	_header = new int[_hLenght];          //������� ������� ����������� ����� �����
	_tailler = new int[_tLenght];

}

Deque::~Deque() {
	delete[] _header;                    //��� �������� ������� ������� �� ������������ ������ �������
	delete[] _tailler;
}

void Deque::PushFront(int val) {
	if (_allCount <= _size) {                //���������, ����� ���������� ��������� � ����� �������� ���� �� ������ ��� ������ �������
		if(_hCount<0){                       //���� ������� ���������� � ������� "�������" �������, �.�. ������ ������� ��������� � "������" �������
			_tailler[abs(_hCount+1)] = val;  //��������� �������� � ���� �������.
			_hCount++;                       //����������� ���������� ��������� "���������" �������
			_allCount = _hCount + _tCount;   //��������� ����� ���������� ���� ��������� �������
			return;                          //��������� ������ ������
		}
		if (_hCount < _hLenght) {            //��� ���������� � "��������" ������ ��������� ����� ���������� ��������� ���� �� ������ ��� �����
			_header[_hCount] = val;          //��������� �������� � "��������" ������
			_hCount++;                       //����������� ���������� ��������� "���������" �������
		}
		else {                                               //���� ������ "���������" ������� �������� ����������� ��� ������
			int* temp = new int[(_hLenght * 2) + 1];         //������� ������ � ��� ���� ������
			memmove(temp, _header, _hLenght * sizeof(int));  //��������� �������� �� ������� � �����
			_hLenght = (_hLenght * 2) + 1;                   //��������� ������ ������ �������
			delete[]_header;                                 //������� ������ ������
			_header = temp;                                  //� ������ ��������� ���������� ����� �� ����� ������
			_header[_hCount] = val;                          //��������� �������� � ����� �������
			_hCount++;                                       //����������� ���������� ��������� � "��������" ��������
		}
		_allCount = _hCount + _tCount;                       //��������� ����� ���������� ���� ��������� �������
	}
	else {
		throw "��������� ������ ������� �������!";          //���� ��� ���������� �������� ��������������,		  
	}	                                                    //��� ������ ������� ��������, ����������� ����������
}

void Deque::PushBack(int val) {                             //������� ��� �� ������ �������� � "������" ��������
	if (_allCount <= _size) {   
		if (_tCount<0) {                  
			_header[abs(_tCount + 1)] = val;  
			_tCount++;
			_allCount = _hCount + _tCount;
			return;                     
		}
		if (_tCount < _tLenght) {     
			_tailler[_tCount] = val;   
			_tCount++;                
		}
		else {                                                
			int* temp = new int[(_tLenght * 2)];              
			memmove(temp, _tailler, _tLenght * sizeof(int));  
			_tLenght *= 2;                                     
			delete[] _tailler;                                 
			_tailler = temp;                                 
			_tailler[_tCount] = val;                         
			_tCount++;                                     
		}
		_allCount = _hCount + _tCount;                     
	}
	else {
		throw "��������� ������ ������� �������!";           
	}	                                                    
}

int Deque::PopFront() {
	if (_allCount != 0) {                  //���� ������ �� �����
		int res;                           //������� ��������� ���������� ��� �������� ������������� ����������
		if (_hCount > 0) {                 //���� � "��������" ������� �������� �������� ������ �� ����
			res = _header[_hCount-1];      //������ �������� �� ������� = ���������� ��������� � �������-1
			_header[_hCount - 1] = NULL;   //�������� ���� �������
			_hCount--;                     //�������������� ���������� ��������� � "��������" �������
			_allCount = _hCount + _tCount; //��������� ���������� ��������� � ������� 
		}
		else {          //���� ���������� ��������� � "��������" ������� ����������� ����������� �������� �� ������ "�������",
			res = _tailler[abs(_hCount)];   //���� ������������� �������� ���������� ��������� "���������" ������� �� ������
			_tailler[abs(_hCount)] = NULL;
			_hCount--;
			_allCount = _hCount + _tCount;
		}
		return res;                          //���������� ��������� ���������
	}
	else {                                  //���� ���������� ��������� � ������� 0
		throw "������� �����!";             //����������� ����������
	}	
}

int Deque::PopBack() {                     //������ �� ��
	if (_allCount != 0) {                                
		int res;                                        //������� ��������� ���������� ��� �������� ������������� ����������
		if (_tCount > 0) {                                 //���� � "��������" ������� �������� �������� ������ �� ����
			res = _tailler[_tCount - 1];                   //������ �������� �� ������� = ���������� ��������� � �������-1
			_tailler[_tCount - 1] = NULL;                  //�������� ���� �������
			_tCount--;                                            //�������������� ���������� ��������� � "��������" �������
			_allCount = _hCount + _tCount; 
		}
		else {          //���� ���������� ��������� � "������" ������� ����������� ����������� �������� �� ������ "���������"
			res = _header[abs(_tCount)];   
			_header[abs(_tCount)] = NULL;
			_tCount--;
			_allCount = _hCount + _tCount;
		}
		return res;                          //���������� ��������� ���������
	}
	else {                                  //���� ���������� ��������� � ������� 0
		throw "������� �����!";             //����������� ����������
	}
}




int main() {
	setlocale(LC_CTYPE, "Russian");

	Deque *dq = new Deque(6);
	(*dq).PushFront(5);
	dq->PushBack(10);
	std::cout << (*dq).PopFront() << std::endl;
	std::cout << (dq->PopFront()) << std::endl;
	
	try {
		dq->PopBack();
	}
	catch (char* ex) {
		std::cout << ex << std::endl;
	}
	
	dq->PushFront(15);
	dq->PushFront(25);
	std::cout << (dq->PopBack()) << std::endl;
	
	delete dq;
	return 0;
}