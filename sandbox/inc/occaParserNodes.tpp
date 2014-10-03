namespace occa {
  namespace parserNamespace {
    //---[ Node ]-----------------------------------
    template <class TM>
    node<TM>::node() :
      left(NULL),
      right(NULL),
      up(NULL) {}

    template <class TM>
    node<TM>::node(const TM &t) :
      left(NULL),
      right(NULL),
      up(NULL),

      value(t) {}

    template <class TM>
    node<TM>::node(const node<TM> &n) :
      left(n.left),
      right(n.right),
      up(n.up),
      down(n.down),

      value(n.value) {}

    template <class TM>
    node<TM>& node<TM>::operator = (const node<TM> &n){
      left  = n.left;
      right = n.right;
      up    = n.up;
      down  = n.down;

      value = n.value;
    }

    template <class TM>
    node<TM>* node<TM>::pop(){
      if(left != NULL)
        left->right = right;

      if(right != NULL)
        right->left = left;

      return this;
    }

    template<class TM>
    node<TM>* node<TM>::push(node <TM> *n){
      node *rr = right;

      right = n;

      right->left  = this;
      right->right = rr;

      if(rr)
        rr->left = right;

      return right;
    }

    template <class TM>
    node<TM>* node<TM>::push(const TM &t){
      return push(new node(t));
    }

    template <class TM>
    node<TM>* node<TM>::pushDown(node<TM> *n){
      n->up = this;

      down.push_back(n);

      return n;
    }

    template<class TM>
    node<TM>* node<TM>::pushDown(const TM &t){
      return pushDown(new node(t));
    }

    template<class TM>
    void node<TM>::print(const std::string &tab){
      node *nodePos = this;

      while(nodePos){
        std::cout  << tab << nodePos->value << '\n';

        const int downCount = (nodePos->down).size();

        if(downCount)
          printf("--------------------------------------------\n");

        for(int i = 0; i < downCount; ++i){
          (nodePos->down[i])->print(tab + "  ");
          printf("--------------------------------------------\n");
        }

        nodePos = nodePos->right;
      }
    }

    template <class TM>
    void node<TM>::printPtr(const std::string &tab){
      node *nodePos = this;

      while(nodePos){
        std::cout << tab << *(nodePos->value) << '\n';

        const int downCount = (nodePos->down).size();

        if(downCount)
          printf("--------------------------------------------\n");

        for(int i = 0; i < downCount; ++i){
          (nodePos->down[i])->printPtr(tab + "  ");
          printf("--------------------------------------------\n");
        }

        nodePos = nodePos->right;
      }
    }

    template <class TM>
    void popAndGoRight(node<TM> *&n){
      node<TM> *left  = n->left;
      node<TM> *right = n->right;

      if(left != NULL)
        left->right = right;

      if(right != NULL)
        right->left = left;

      delete n;

      n = right;
    }

    template <class TM>
    void popAndGoLeft(node<TM> *&n){
      node<TM> *left  = n->left;
      node<TM> *right = n->right;

      if(left != NULL)
        left->right = right;

      if(right != NULL)
        right->left = left;

      delete n;

      n = left;
    }

    template <class TM>
    node<TM>* firstNode(node<TM> *n){
      if((n == NULL) ||
         (n->left == NULL))
        return n;

      node<TM> *end = n;

      while(end->left)
        end = end->left;

      return end;
    }

    template <class TM>
    node<TM>* lastNode(node<TM> *n){
      if((n == NULL) ||
         (n->right == NULL))
        return n;

      node<TM> *end = n;

      while(end->right)
        end = end->right;

      return end;
    }
    //==============================================
  };
};
