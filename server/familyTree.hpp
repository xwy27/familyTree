#ifndef FAMILY_TREE_H
#define FAMILY_TREE_H
#include <string>
#include <vector>
using namespace std;

struct Detail {
  string firstName;
  string lastName;
  string birthDay;
  string deadDay;
  bool isMale;

  // Constructors
  Detail(const Detail& data) : firstName(data.firstName), lastName(data.lastName), birthDay(data.birthDay),
    deadDay(data.deadDay), isMale(data.isMale) {}
  Detail(const string& firstName, const string& lastName, const string& birthDay, const string& deadDay, bool isMale) :
    firstName(firstName), lastName(lastName), birthDay(birthDay), deadDay(deadDay), isMale(isMale) {} 
  Detail& operator=(const Detail& detailIn) {
    firstName = detailIn.firstName;
    lastName = detailIn.lastName;
    birthDay = detailIn.birthDay;
    deadDay = detailIn.deadDay;
    isMale = detailIn.isMale;
    return *this;
  }
};

struct Node {
  static unsigned count;
  unsigned id;
  Detail detail;
  Node *parent;
  vector<Node> couple;
  vector<Node> children;

  // Constructors
  Node(const Node& nodeIn) : parent(nodeIn.parent), couple(nodeIn.couple), children(nodeIn.children), id(nodeIn.id),
    detail(nodeIn.detail) {}
  Node& operator=(const Node& nodeIn) {
    parent = nodeIn.parent;
    couple = nodeIn.couple;
    children = nodeIn.children;
    detail = nodeIn.detail;
    id = nodeIn.id;
    return *this;
  }
  Node(const Detail& detail, Node* parent = nullptr) : id(count++), parent(parent), detail(detail) {}
};

struct toReturn {
  bool isError;
  string data; // 若 isError 为 false 则为打印树的结果，若为 true 则为错误信息
  toReturn(const string& data, bool isError = false) : data(data), isError(isError) {}
};

class familyTree {

public:
  familyTree(); // 默认且唯一的构造函数：创建一个带有一个根节点的家谱树 *ZJ*
  ~familyTree(); // 析构函数，仅需delete根节点 *ZJ*
  
  toReturn addToParent(const Detail& detail, const unsigned& id); // 将一个包含Detail的节点设为目标节点的双亲节点
  // 返回值通过调用printTree生成 *ZJ*
  toReturn addToCouple(const Detail& detail, const unsigned& id); // 将一个包含Detail的节点设为目标节点的配偶节点
  // 返回值通过调用printTree生成 *ZJ*
  toReturn addToSublings(const Detail& detail, const unsigned& id); // 将一个包含Detail的节点设为目标节点的兄弟节点
  // 返回值通过调用printTree生成 *ZJ*
  toReturn addToChildren(const Detail& detail, const unsigned& id); // 将一个包含Detail的节点设为目标节点的子节点
  // 返回值通过调用printTree生成 *ZJ*

  toReturn deleteSubTree(const unsigned& id); // 删除id指定节点为根的子树
  // 返回值通过调用printTree生成 *ZJ*

  Node& getNode(const unsigned& id); // 获取id指定节点的引用，若未找到，则 throw "NODE_NOT_FOUND"
  // 使用时需要try & catch *ZJ*

  string printTree(); // 将树打印为字符串，须符合规定的格式 *WY*
  string nodeToString(Node &root);

private:
  Node *root; // Notice: root can't be nullptr!

};


#endif