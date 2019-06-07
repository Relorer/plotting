#pragma once
template<typename Type>
class Vect
{
public:
	Vect();
	~Vect();
	Type& operator[](const int index);
	Vect(const Vect& another);
	Vect(Vect&& another);
	Vect& operator=(const Vect<Type>& another);
	virtual int getSize();
	virtual void pushFront(Type data);
protected:
	void increase(const int reserve);
	int size;
	int reserve;
	Type* vect;
};

template<typename Type>
Vect<Type>::Vect()
{
	this->size = 0;
	this->reserve = 20;
	this->vect = new Type[reserve];
}

template<typename Type>
Vect<Type>::~Vect()
{
	delete[] this->vect;
}

template<typename Type>
Type& Vect<Type>::operator[](const int index)
{
	if (index >= reserve) increase(index - reserve + 1);
	this->size = index >= size ? index + 1 : size;
	return this->vect[index];
}

template<typename Type>
Vect<Type>::Vect(const Vect<Type> & another)
{
	this->reserve = another.reserve;
	this->size = another.size;
	this->vect = new Type[reserve];
	for (int i = 0; i < size; i++) {
		this->vect[i] = another.vect[i];
	}
}

template<typename Type>
Vect<Type>::Vect(Vect<Type> && another)
{
	this->reserve = another.reserve;
	this->size = another.size;
	this->vect = another.vect;
	another.vect = nullptr;
}

template<typename Type>
Vect<Type>& Vect<Type>::operator=(const Vect<Type> & another)
{
	if (&another == this) return *this;
	if (this->vect != nullptr) delete[] this->vect;
	this->size = another.size;
	this->reserve = another.reserve;
	this->vect = new Type[reserve];
	for (int i = 0; i < size; i++) {
		this->vect[i] = another.vect[i];
	}
	return *this;
}

template<typename Type>
int Vect<Type>::getSize()
{
	return this->size;
}

template<typename Type>
void Vect<Type>::pushFront(Type data)
{
	this->operator[](size) = data;
}

template<typename Type>
void Vect<Type>::increase(const int reserve)
{
	Type* resVect = new Type[this->reserve + reserve];
	this->reserve += reserve;
	for (int i = 0; i < this->size; i++) {
		resVect[i] = this->vect[i];
	}
	delete[] this->vect;
	this->vect = resVect;
	resVect = nullptr;
}
