

// Template class used for basic single group operation on segments using
// a tree structure.
// Operations are determined by the '+' operator of the T class
// Neutral element is determined by T(0) constructor

// The group does not need to be commutative. In case of non-commutative
// groups, the operations are applied from the left.

template<class T>
class Tree
{
private:
  struct Node
  {
    int ps, pe;
    Node *lson, *rson;
    T value;
    Node(int ps, int pe, T elem);
    ~Node();

    void add(int start, int stop, T elem);
    T get(int x, T elem);

    void pushDown();
  };

  Node *tree;

public:
  Tree(int size);
  ~Tree();

  void add(int start, int stop, T elem);
  T get(int x);
};

// IMPLEMENTATION

template<class T>
Tree<T>::Node::Node(int ps, int pe, T elem)
{
  this->ps = ps;
  this->pe = pe;
  lson = nullptr;
  rson = nullptr;
  value = elem;
}

template<class T>
Tree<T>::Node::~Node()
{
  if(lson != nullptr)
  {
    delete lson;
    delete rson;
  }
}

template<class T>
void Tree<T>::Node::add(int start, int stop, T elem)
{
  if(start <= ps && stop >= pe)
  {
    value = elem + value;
    return;
  }
  if(start > pe || stop < ps)
  {
    return;
  }
  pushDown();
  lson->add(start, stop, elem);
  rson->add(start, stop, elem);
}

template<class T>
T Tree<T>::Node::get(int x, T elem)
{
  elem = elem + value;
  if (lson == nullptr)
    return elem;
  else if (x < (ps + pe + 1)/2)
    return lson->get(x, elem);
  return rson->get(x, elem);
}

template<class T>
void Tree<T>::Node::pushDown()
{
  if (lson == nullptr)
  {
    lson = new Node(ps, (ps + pe + 1)/2 - 1, value);
    rson = new Node((ps + pe + 1)/2, pe, value);
  }
  else
  {
    lson->value = value + lson->value;
    rson->value = value + rson->value;
  }
  value = T(0);
}


template<class T>
Tree<T>::Tree(int size)
{
  tree = new Node(0, size - 1, T(0));
}

template<class T>
Tree<T>::~Tree<T>()
{
  delete tree;
}

template<class T>
void Tree<T>::add(int start, int stop, T elem)
{
  tree->add(start, stop, elem);
}

template<class T>
T Tree<T>::get(int x)
{
  return tree->get(x, T(0));
}
