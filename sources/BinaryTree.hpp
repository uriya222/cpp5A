#include <iostream>
#include <stack>

namespace ariel
{

    template <typename T>
    class BinaryTree
    {
        class Node
        {
        public:
            Node(const T &val) : val(val), left(nullptr), right(nullptr), father(nullptr) {}
            T val;
            Node *left;
            Node *right;
            Node *father;
        };

        Node *root;
        Node *find(const T &value)
        {

            if (root == nullptr)
            {
                return nullptr;
            }
            std::stack<Node *> nodeStack;
            nodeStack.push(root);
            while (!static_cast<bool>(nodeStack.empty()))
            {
                Node *n = nodeStack.top();
                if (n->val == value)
                {
                    return n;
                }
                nodeStack.pop();
                if (n->right)
                {
                    nodeStack.push(n->right);
                }
                if (n->left)
                {
                    nodeStack.push(n->left);
                }
            }
            return nullptr;
        }
        void delete_tree()
        {
            if (root == nullptr)
            {
                return;
            }
            std::stack<Node *> nodeStack;
            nodeStack.push(root);
            while (!static_cast<bool>(nodeStack.empty()))
            {
                Node *n = nodeStack.top();
                nodeStack.pop();
                if (n->right)
                {
                    nodeStack.push(n->right);
                }
                if (n->left)
                {
                    nodeStack.push(n->left);
                }
                delete n;
            }
        }

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(const BinaryTree &) = delete;
        BinaryTree(const BinaryTree &&) = delete;
        BinaryTree<T> &add_root(const T &val)
        {
            if (root == nullptr)
            {
                root = new Node(val);
            }
            else
            {
                root->val = val;
            }
            return *this;
        }
        BinaryTree<T> &add_left(const T &place, const T &add)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is not initialize");
            }
            Node *n = find(place);
            if (n == nullptr)
            {
                throw std::invalid_argument("no such value in the tree");
            }
            if ((n->left) != nullptr)
            {
                (n->left)->val = add;
            }
            else
            {
                Node *tmp = new Node(add);
                tmp->father = n;
                n->left = tmp;
            }
            return *this;
        }
        BinaryTree<T> &add_right(const T &place, const T &add)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is not initialize");
            }
            Node *n = find(place);
            if (n == nullptr)
            {
                throw std::invalid_argument("no such value in the tree");
            }
            if ((n->right) != nullptr)
            {
                (n->right)->val = add;
            }
            else
            {
                Node *tmp = new Node(add);
                tmp->father = n;
                n->right = tmp;
            }
            return *this;
        }

        BinaryTree<T> &operator=(const BinaryTree &) = delete;
        BinaryTree<T> &operator=(BinaryTree<T> &&) noexcept = default;

        ~BinaryTree()
        {
            delete_tree();
        }

        //===============================================================
        class pre_iterator
        {

        private:
            Node *node;
            void preorder_next()
            {
                if ((node->left) != nullptr)
                {
                    node = node->left;
                    return;
                }
                if ((node->right) != nullptr)
                {
                    node = node->right;
                    return;
                }
                Node *tmp = nullptr;
                do
                {
                    tmp = node;
                    node = node->father;
                    if (node == nullptr)
                    {
                        return;
                    }
                } while (node->right == nullptr || (tmp == node->right));
                node = node->right;
            }

        public:
            pre_iterator(Node *ptr = nullptr) : node(ptr) {}
            pre_iterator(const pre_iterator &it) : node(it.node) {}
            pre_iterator(const pre_iterator &&it) noexcept : node(it.node) {}
            pre_iterator &operator=(pre_iterator &&o) noexcept
            {
                if (this != &o)
                {
                    delete node;
                    node = o.node;
                    o.node = nullptr;
                }
                return *this;
            }
            ~pre_iterator() {}

            T &operator*() const
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("try to reach null pointer");
                }
                return node->val;
            }

            T *operator->() const
            {
                if (node == nullptr)
                {
                    return nullptr;
                }
                return &(node->val);
            }

            pre_iterator &operator++()
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("tree is not initiaized");
                }
                preorder_next();
                return *this;
            }

            pre_iterator operator++(int)
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("tree is not initiaized");
                }
                pre_iterator tmp = *this;
                preorder_next();
                return tmp;
            }

            bool operator==(const pre_iterator &it) const
            {
                return node == it.node;
            }

            bool operator!=(const pre_iterator &it) const
            {
                return node != it.node;
            }
            pre_iterator &operator=(const pre_iterator &it)
            {
                if (this == &it)
                {
                    return *this;
                }
                node = it.node;
                return *this;
            }
        };
        pre_iterator begin_preorder()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            pre_iterator i(root);
            return i;
        }
        pre_iterator end_preorder()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            return pre_iterator();
        }
        //===============================================================
        class in_iterator
        {

        private:
            Node *node;
            void inorder_next()
            {
                if ((node->right) != nullptr)
                {
                    node = node->right;
                    while ((node->left) != nullptr)
                    {
                        node = node->left;
                    }
                }
                else
                {
                    Node *tmp = nullptr;
                    do
                    {
                        tmp = node;
                        node = node->father;
                        if (node == nullptr)
                        {
                            break;
                        }
                    } while (tmp != node->left);
                }
            }

        public:
            in_iterator(Node *ptr = nullptr) : node(ptr) {}
            in_iterator(const in_iterator &it) : node(it.node) {}
            in_iterator(const in_iterator &&it) noexcept : node(it.node) {}
            in_iterator &operator=(in_iterator &&o) noexcept
            {
                if (this != &o)
                {
                    delete node;
                    node = o.node;
                    o.node = nullptr;
                }
                return *this;
            }
            ~in_iterator() {}

            T &operator*() const
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("try to reach null pointer");
                }
                return node->val;
            }

            T *operator->() const
            {
                if (node == nullptr)
                {
                    return nullptr;
                }
                return &(node->val);
            }

            in_iterator &operator++()
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("tree is not initiaized");
                }
                inorder_next();
                return *this;
            }

            in_iterator operator++(int)
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("tree is not initiaized");
                }
                in_iterator tmp = *this;
                inorder_next();
                return tmp;
            }

            bool operator==(const in_iterator &it) const
            {
                return node == it.node;
            }

            bool operator!=(const in_iterator &it) const
            {
                return node != it.node;
            }
            in_iterator &operator=(const in_iterator &it)
            {
                if (this == &it)
                {
                    return *this;
                }
                node = it.node;
                return *this;
            }
            void initial_begin()
            {
                while (node->left != nullptr)
                {
                    node = node->left;
                }
            }
        };
        in_iterator begin_inorder()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            in_iterator i(root);
            i.initial_begin();
            return i;
        }
        in_iterator end_inorder()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            return in_iterator();
        }
        in_iterator begin()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            in_iterator i(root);
            i.initial_begin();
            return i;
        }
        in_iterator end()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            return in_iterator();
        }
        //===============================================================
        class post_iterator
        {

        private:
            Node *node;
            void postorder_next()
            {
                Node *parent = node->father;
                if (parent == nullptr)
                {
                    node = nullptr;
                }
                else if ((parent->right) == node || (parent->right) == nullptr)
                {
                    node = parent;
                }
                else
                {
                    Node *sibiling = parent->right;
                    while (sibiling != nullptr)
                    {
                        parent = sibiling;
                        if ((sibiling->left) != nullptr)
                        {
                            sibiling = sibiling->left;
                        }
                        else
                        {
                            sibiling = sibiling->right;
                        }
                    }
                    node = parent;
                }
            }

        public:
            post_iterator(Node *ptr = nullptr) : node(ptr) {}
            post_iterator(const post_iterator &it) : node(it.node) {}
            post_iterator(const post_iterator &&it) noexcept : node(it.node) {}
            post_iterator &operator=(post_iterator &&o) noexcept
            {
                if (this != &o)
                {
                    delete node;
                    node = o.node;
                    o.node = nullptr;
                }
                return *this;
            }
            ~post_iterator() {}
            T &operator*() const
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("null pointer");
                }
                return node->val;
            }

            T *operator->() const
            {
                if (node == nullptr)
                {
                    return nullptr;
                }
                return &(node->val);
            }

            post_iterator &operator++()
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("tree is not initiaized");
                }
                postorder_next();
                return *this;
            }

            post_iterator operator++(int)
            {
                if (node == nullptr)
                {
                    throw std::invalid_argument("tree is not initiaized");
                }
                post_iterator tmp = *this;
                postorder_next();
                return tmp;
            }

            bool operator==(const post_iterator &it) const
            {
                return node == it.node;
            }

            bool operator!=(const post_iterator &it) const
            {
                return node != it.node;
            }
            post_iterator &operator=(const post_iterator &it)
            {
                if (this != &it)
                {
                    node = it.node;
                }
                return *this;
            }
            void initial_begin()
            {
                while (node->right != nullptr || node->left != nullptr)
                {
                    while (node->left != nullptr)
                    {
                        node = node->left;
                    }
                    if (node->right != nullptr)
                    {
                        node = node->right;
                    }
                }
            }
        };
        post_iterator begin_postorder()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            post_iterator i(root);
            i.initial_begin();
            return i;
        }
        post_iterator end_postorder()
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("tree is not initiaized");
            }
            return post_iterator();
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &out, BinaryTree<T> &tree)
    {
        for (auto it = tree.begin_inorder(); it != tree.end_inorder(); ++it)
        {
            out << (*it) << ",";
        }
        return out;
    }

}