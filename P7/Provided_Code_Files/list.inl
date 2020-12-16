template<typename T>
Node<T>::Node(const T& data, Node* n)
    : data{data}
    , next{n}
{
}

// TODO: Insert at least some of the definitions of List methods here.
template<typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
    numItems = 0;
}

template<typename T>
List<T>::List(const List<T>& other) {
    numItems = 0;
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        Node<T>* copy = new Node<T>(temp->getData(), nullptr);
        if (numItems == 0) {
            tail = copy;
            head = copy;
        } else {
            tail->setNext(copy);
            tail = copy;
        }
        temp = temp->getNext();
        numItems++;
    }
    if (numItems == 0) {
        head = nullptr;
        tail = nullptr;
    }
}


template<typename T>
List<T>::~List() {
    Node<T>* prev = nullptr;
    Node<T>* temp = head;
    while (temp != nullptr) {
        if (prev != nullptr) {
            delete prev;
        }
        prev = temp;
        temp = temp->getNext();
    }
    delete prev;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    int origNumItems = this->length();
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        this->pushBack(temp->getData());
        temp = temp->getNext();
    }
    for (int i = 0; i < origNumItems; i++) {
        this->remove(this->head->getData());
    }
    return *this;
}

template<typename T>
unsigned List<T>::length() const {
    return numItems;
}

template<typename T>
void List<T>::pushFront(const T& data) {
    Node<T>* temp = new Node<T>(data, head);
    if (numItems == 0) {
        tail = temp;
        head = temp;
    } else {
        head = temp;
    }
    numItems++;
    return;
}

template<typename T>
void List<T>::pushBack(const T& data) {
    Node<T>* temp = new Node<T>(data, nullptr);
    if (numItems == 0) {
        tail = temp;
        head = temp;
    } else {
        tail->setNext(temp);
        tail = temp;
    }
    numItems++;
    return;
}

template<typename T>
void List<T>::operator+=(const T& data) {
    this->pushBack(data);
    return;
}

template<typename T>
T& List<T>::operator[](unsigned index) {
    if (index < 0 || index >= numItems) {
        throw std::out_of_range{"Index out of range"};
    }
    size_t i = 0;
    Node<T>* temp = head;
    while (i != index) {
        temp = temp->getNext();
        i++;
    }
    return temp->getData();
}

template<typename T>
const T& List<T>::operator[](unsigned index) const {
    if (index < 0 || index >= numItems) {
        throw std::out_of_range{"Index out of range"};
    }
    size_t i = 0;
    Node<T>* temp = head;
    while (i != index) {
        temp = temp->getNext();
        i++;
    }
    return temp->getData();
}

template<typename T>
bool List<T>::contains(const T& data) const {
    Node<T>* temp = head;
    while (temp != nullptr) {
        if (temp->getData() == data) {
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

template<typename T>
bool List<T>::remove(const T& data) {
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    bool foundNode = false;
    while (current != nullptr) {
        if (current->getData() == data) {
            foundNode = true;
            break;
        }
        prev = current;
        current = current->getNext();
    }
    if (foundNode) {
        if (numItems == 1) { // if current is the only node in list
            head = nullptr;
            tail = nullptr;
        } else if (prev == nullptr) { // if current is the head
            head = current->getNext();
        } else if (current->getNext() == nullptr) { // if current is the tail
            prev->setNext(nullptr);
            tail = prev;
        } else { // if current is in the middle
            prev->setNext(current->getNext());
        }
        delete current;
        numItems--;
        return true;
    }
    return false;
}

template<typename T>
void List<T>::operator-=(const T& data) {
    remove(data);
    return;
}

