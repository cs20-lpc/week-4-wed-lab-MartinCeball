#include <string>
#include <iostream>

template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr) { 
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj) {
    if (copyObj.head == nullptr) {
        this->head = nullptr;
        this->length = 0;
        return;
    }

    this->head = new Node(copyObj.head->value);
    
    Node* currentThis = this->head;
    Node* currentOther = copyObj.head->next;

    while (currentOther != nullptr) {
        currentThis->next = new Node(currentOther->value);
        currentThis = currentThis->next;
        currentOther = currentOther->next;
    }

    this->length = copyObj.length;
}

template <typename T>
void LinkedList<T>::append(const T& elem) {
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    }
    else {
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
    }
    this->length++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    this->length = 0;
}

template <typename T>
T LinkedList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw std::string("getElement: error, position out of bounds");
    }
    
    Node* curr = head;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }
    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const {
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) {
        throw std::string("insert: error, position out of bounds");
    }

    if (position == 0) {
        head = new Node(elem, head);
    }
    else {
        Node* current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        current->next = new Node(elem, current->next);
    }
    this->length++;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    if (position < 0 || position >= this->length) {
        throw std::string("remove: error, position out of bounds");
    }

    Node* toDelete = nullptr;

    if (position == 0) {
        toDelete = head;
        head = head->next;
    } 
    else {
        Node* current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }
    delete toDelete;
    this->length--;
}

template <typename T>
void LinkedList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw std::string("replace: error, position out of bounds");
    }

    Node* curr = head;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }
    curr->value = elem;
}

template <typename T>
std::ostream& operator<<(std::ostream& outStream, const LinkedList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename LinkedList<T>::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << std::endl;
    }
    return outStream;
}

