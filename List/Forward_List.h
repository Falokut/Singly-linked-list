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
    // �������� 1: ������ ������, ����� ������� ����� ���� � ��������� head ����� ����� ����
    if (!head)
        head = new Node<T>(Data);

    // �������� 2: ������ ��������, ����� ������� ����� ���� � ������� ����������� ��������� �� ��� ����
    else
    {
        Node<T> *current = head;
        while (current->pNext) // ������������ current->pNext != nullptr
        {
            current = current->pNext; // ���� ����, ����������� �� null
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
        if (!current->pNext) // ������������ current->pNext != nullptr
            delete current;
    }
}

template <typename T> inline void Forward_List<T>::Pop_Front()
{
    Node<T> *temp = head; // ������ temp � head ����� ���������� ���������(��������� �� 1 �����)
    head = head->pNext;   // ������� ��������� head � ����������� ��� ��������� �� ��������� �������
    delete temp;          // ������� ������ head
    --Size;
}

template <typename T> inline void Forward_List<T>::RemoveAt(const int index)
{
    if (index == 0)
        Pop_Front();
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i) // ��� �� ��������, ������� ��������� �� �������� �������
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
        return;                  // ���� ������ ������� ������ ������� ������, �� ������� �� �������
    else if (index == GetSize()) // ���� ������ ������� ����� ������� ������, �� ��������� ������� � ����� ������
        Push_Back(Data);
    else if (index == 0) // ���� ������ ������� ����� 0, �.� 0 ��������, �� ��������� ������� � ������ ������
        Push_Front(Data);
    else
    {
        Node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i) // ��� �� ��������, ������� ��������� �� �������� �������
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
    if (index >= Size) // ���� ������ ������ �������, ������ �������� �� �� �����
    {
        throw -1;
    }

    int counter = 0;
    Node<T> *current = this->head;
    while (current) // ���� ������� ��� �������� index
    {
        if (counter == index) // ���� ������ ����� counter, �� ����� ������ ��� �������
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
