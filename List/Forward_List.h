#pragma once
#include <iostream>

template <typename T> class Forward_List
{
  public:
    Forward_List();
    ~Forward_List();
    int GetSize() const;

    void Print();
    void Push_Back(T Data);
    void Push_Front(T Data);
    void Insert(T Data, const int index);

    void Pop_Back();
    void Pop_Front();
    void RemoveAt(const int index);
    void Clear();

    T &operator[](const int index);

  private:
    template <typename T> struct Node
    {
        Node *pNext;
        T Data;
        Node(T Data = T(), Node *pNext = nullptr)
        {
            this->Data = Data;
            this->pNext = pNext;
        };
    };

    int Size;
    Node<T> *head;
};

template <typename T> inline Forward_List<T>::Forward_List()
{
    Size = 0;
    head = nullptr;
}

template <typename T> inline Forward_List<T>::~Forward_List()
{
    Clear();
}

template <typename T> inline void Forward_List<T>::Print()
{
    Node<T> *current = head;

    for (int i = 0; i < GetSize(); ++i)
    {
        std::cout << "List [" << i << "] = " << current->Data << "\t";
        current = current->pNext;
    }
}

template <typename T> inline void Forward_List<T>::Push_Back(T Data)
{
    // Ситуация 1: список пустой, нужно создать новый узел и присвоить head адрес этого узла
    if (!head)
        head = new Node<T>(Data);

    // Ситуация 2: список заполнен, нужно создать новую ноду и указать предыдущему указатель на эту узел
    else
    {
        Node<T> *current = head;
        while (current->pNext) // эквивалентно current->pNext != nullptr
        {
            current = current->pNext; // ищем узел, указывающий на null
        }
        current->pNext = new Node<T>(Data);
    }
    ++Size;
}

template <typename T> inline void Forward_List<T>::Push_Front(T Data)
{
    head = new Node<T>(Data, head);
    ++Size;
}

template <typename T> inline int Forward_List<T>::GetSize() const
{
    return Size;
}

template <typename T> inline void Forward_List<T>::Pop_Back()
{
    Node<T> *current = head;
    while (current->pNext)
    {
        current = current->pNext;
        if (!current->pNext) // эквивалентно current->pNext != nullptr
            delete current;
    }
}

template <typename T> inline void Forward_List<T>::Pop_Front()
{
    Node<T> *temp = head; // теперь temp и head имеют одинаковые указатели(указывают на 1 место)
    head = head->pNext;   // смещаем указатель head и присваиваем ему указатель на следующий элемент
    delete temp;          // удаляем старый head
    --Size;
}

template <typename T> inline void Forward_List<T>::RemoveAt(const int index)
{
    if (index == 0)
        Pop_Front();
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i) // идём до элемента, который находится до искомого индекса
        {
            prev = head->pNext;
        }
        Node<T> *toDelete = prev->pNext;
        prev->pNext = toDelete->pNext;
        delete toDelete;
        --Size;
    }
}

template <typename T> inline void Forward_List<T>::Clear()
{
    while (head)
        Pop_Front();
}

template <typename T> inline void Forward_List<T>::Insert(T Data, const int index)
{
    if (index > GetSize())
        return;                  // если индекс вставки больше размера списка, мы выходим из функции
    else if (index == GetSize()) // если индекс вставки равен размеру списка, мы вставляем элемент в конец списка
        Push_Back(Data);
    else if (index == 0) // если индекс вставки равен 0, т.е 0 значению, мы вставляем элемент в начало списка
        Push_Front(Data);
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i) // идём до элемента, который находится до искомого индекса
        {
            prev = head->pNext;
        }
        Node<T> *NewNode = new Node<T>(Data, prev->pNext);
        prev->pNext = NewNode;
        ++Size;
    }
}

template <typename T> inline T &Forward_List<T>::operator[](const int index)
{
    if (index >= Size) // если индекс больше размера, такого элемента мы не найдём
    {
        throw -1;
    }

    int counter = 0;
    Node<T> *current = this->head;
    while (current) // ищем элемент под индексом index
    {
        if (counter == index) // если индекс равен counter, мы нашли нужный нам элемент
        {
            return current->Data;
        }
        else
        {
            current = current->pNext;
            ++counter;
        }
    }
}
