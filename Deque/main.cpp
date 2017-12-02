#include <iostream>
#include <string>

class Deque{
private:
	int* _header;     //указатель на "передний" массив       
	int* _tailler;     //указатель на "задний" массив
	int _hLenght;     //длина "переднего" массива
	int _tLenght;     //длина "переднего" массива
	int _size;        //длина всей очереди
	int _hCount;      //количество элементов в "переднем" массиве
	int _tCount;      //количество элементов в "заднем" массиве
	int _allCount;    //общее количество элементов в очереди

public:
	Deque(int size);
	~Deque();
	void PushFront(int val);
	void PushBack(int val);
	int PopFront();
	int PopBack();
};

Deque::Deque(int size):                   //в конструктор передаем размер очереди
	 _header(nullptr),                    //инициализируем нулями указатели на "передний" и "задний" массивы
	 _tailler(nullptr), 
	 _hLenght((int)(size / 2)),           //задаем размеры "переднему" и "заднему" массивам как половину размера всей очереди
	 _tLenght(size - (int)(size / 2)), 
	 _size(size),                         //сохраняем размер очереди
	 _hCount(0),                          
	 _tCount(0),
	 _allCount(0) 
{
	_header = new int[_hLenght];          //создаем массивы рассчитаной ранее длины
	_tailler = new int[_tLenght];

}

Deque::~Deque() {
	delete[] _header;                    //при удалении очереди удаляем из динамической памяти массивы
	delete[] _tailler;
}

void Deque::PushFront(int val) {
	if (_allCount <= _size) {                //проверяем, чтобы количество элементов в обоих массивах было не больше чем размер очереди
		if(_hCount<0){                       //если очередь сдвинулась в сторону "заднего" массива, т.е. первый элемент находится в "заднем" массиве
			_tailler[abs(_hCount+1)] = val;  //добавляем элементы в него спереди.
			_hCount++;                       //увеличиваем количество элементов "переднего" массива
			_allCount = _hCount + _tCount;   //сохраняем новое количество всех элементов очереди
			return;                          //прерываем работу метода
		}
		if (_hCount < _hLenght) {            //при добавлении в "передний" массив проверяем чтобы количество элементов было не больше его длины
			_header[_hCount] = val;          //добавляем значение в "передний" массив
			_hCount++;                       //увеличиваем количество элементов "переднего" массива
		}
		else {                                               //если размер "переднего" массива превышен увеличиваем его размер
			int* temp = new int[(_hLenght * 2) + 1];         //создаем массив в два раза больше
			memmove(temp, _header, _hLenght * sizeof(int));  //побайтово копируем из старого в новый
			_hLenght = (_hLenght * 2) + 1;                   //сохраняем размер нового массива
			delete[]_header;                                 //удаляем старый массив
			_header = temp;                                  //в старый указатель записываем адрес на новый массив
			_header[_hCount] = val;                          //сохраняем значение в новом массиве
			_hCount++;                                       //увеличиваем количество элементов в "переднем" массивае
		}
		_allCount = _hCount + _tCount;                       //сохраняем новое количество всех элементов очереди
	}
	else {
		throw "Достигрут предел размера очереди!";          //если при добавлении элемента обнаруживается,		  
	}	                                                    //что размер очереди привышен, выбрасываем исключение
}

void Deque::PushBack(int val) {                             //принцип тот же только работаем с "задним" массивом
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
		throw "Достигрут предел размера очереди!";           
	}	                                                    
}

int Deque::PopFront() {
	if (_allCount != 0) {                  //если очеред не пуста
		int res;                           //создаем локальную переменную для хранения возвращаемого результата
		if (_hCount > 0) {                 //если в "переднем" массиве остались элементы читаем из него
			res = _header[_hCount-1];      //читаем значение по индексу = количество элементов в массиве-1
			_header[_hCount - 1] = NULL;   //обнуляем этот элемент
			_hCount--;                     //декрементируем количество элементов в "переднем" массиве
			_allCount = _hCount + _tCount; //обновляем количество элементов в очереди 
		}
		else {          //если количество элементов в "переднем" массиве закончилось вытаскиваем элементы из начала "заднего",
			res = _tailler[abs(_hCount)];   //беря отрицательные значения количества элементов "переднего" массива по модулю
			_tailler[abs(_hCount)] = NULL;
			_hCount--;
			_allCount = _hCount + _tCount;
		}
		return res;                          //возвращаем найденный результат
	}
	else {                                  //если количество элементов в очереди 0
		throw "Очередь пуста!";             //выбрасываем исключение
	}	
}

int Deque::PopBack() {                     //логика та же
	if (_allCount != 0) {                                
		int res;                                        //создаем локальную переменную для хранения возвращаемого результата
		if (_tCount > 0) {                                 //если в "переднем" массиве остались элементы читаем из него
			res = _tailler[_tCount - 1];                   //читаем значение по индексу = количество элементов в массиве-1
			_tailler[_tCount - 1] = NULL;                  //обнуляем этот элемент
			_tCount--;                                            //декрементируем количество элементов в "переднем" массиве
			_allCount = _hCount + _tCount; 
		}
		else {          //если количество элементов в "заднем" массиве закончилось вытаскиваем элементы из начала "переднего"
			res = _header[abs(_tCount)];   
			_header[abs(_tCount)] = NULL;
			_tCount--;
			_allCount = _hCount + _tCount;
		}
		return res;                          //возвращаем найденный результат
	}
	else {                                  //если количество элементов в очереди 0
		throw "Очередь пуста!";             //выбрасываем исключение
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