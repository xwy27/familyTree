#include "familyTree.hpp"
//private:
//Node *root; 
//Notice: root can't be nullptr!
unsigned Node::count = 0;

familyTree::familyTree() : root(new Node(Detail("Me","","","",true),nullptr)) {} // 默认且唯一的构造函数：创建一个带有一个根节点的家谱树 *ZJ*
familyTree::~familyTree() // 析构函数，仅需delete根节点 *ZJ*
{
    delete root;
}
toReturn familyTree::addToParent(const Detail& detail, const unsigned& id) 
// 将一个包含Detail的节点设为目标节点的双亲节点
// 返回值通过调用printTree生成 *ZJ*
{   
    Node &son = getNode(id);
    Node* father = nullptr;
    
    if (son.parent == nullptr) {
        father = new Node(detail, nullptr);
        son.parent = father;
        father->children.push_back(son);
        if (root == &son) {
            root = father;
        }
    }
    else {
        father = son.parent;
        father->couple.push_back(Node(detail, nullptr));
    }
    
    return toReturn(printTree(), false);//在添加失败的时候还没有考虑
}
toReturn familyTree::addToCouple(const Detail& detail, const unsigned& id)
// 将一个包含Detail的节点设为目标节点的配偶节点
// 返回值通过调用printTree生成 *ZJ*
{
    Node &husband = getNode(id);
    Node wife(detail, &husband);
    husband.couple.push_back(wife);
    return toReturn(printTree(),false);//在添加失败的时候还没有考虑
}
toReturn familyTree::addToSublings(const Detail& detail, const unsigned& id)
// 将一个包含Detail的节点设为目标节点的兄弟节点
// 返回值通过调用printTree生成 *ZJ*
{
    Node &bigBrother = getNode(id);
    if (bigBrother.parent == nullptr) {
        return toReturn("You cannot add borther while you have no parent node.", true);
    }
    Node littleBrother(detail,bigBrother.parent);//儿子找到了爸爸
    bigBrother.parent->children.push_back(littleBrother);//爸爸找到了儿子
    return toReturn(printTree(),false);
}
toReturn familyTree::addToChildren(const Detail& detail, const unsigned& id)
// 将一个包含Detail的节点设为目标节点的子节点
// 返回值通过调用printTree生成 *ZJ*
{
    Node &father = getNode(id);
    if (father.parent != nullptr)
    for (auto iter = father.parent->couple.begin(); iter != father.parent->couple.end(); ++iter) {
        if (iter->id == id) {
            return addToChildren(detail, father.parent->id);
        }
    }
    Node son(detail,nullptr);
    son.parent = &father;
    father.children.push_back(son);//爸爸找到了儿子
    return toReturn(printTree(),false);
}

toReturn familyTree::deleteSubTree(const unsigned& id)
// 删除id指定节点为根的子树
// 返回值通过调用printTree生成 *ZJ*
{
        
        Node& aim = getNode(id);
        if(root == &aim){
           return toReturn("You cannot delete the root node", true);
        }
        vector<Node>::iterator iter;
        for(iter = aim.parent->children.begin(); iter != aim.parent->children.end();){
            if(iter->id == id)
            {
                iter = aim.parent->children.erase(iter);
                return toReturn(printTree(), false);
            }
            else
                iter++;
        }
        for(iter = aim.parent->couple.begin(); iter != aim.parent->couple.end(); ){
            if(iter->id == id)
            {
                iter = aim.parent->couple.erase(iter);
                return toReturn(printTree(), false);
            }
            else
                iter++;
        }
        return toReturn(printTree(), false);
}

Node* traverse(Node* person, const unsigned& id)
{
    if (person->id == id)
        return person;
    Node *temp;
    
    if (person->couple.size() != 0) {
        for (unsigned i = 0; i < person->couple.size(); ++i) {
            if ((temp = traverse(&(person->couple[i]), id)) != nullptr)
                return temp;
        }
    }

    if (person->children.size() != 0) {
        for (unsigned i = 0; i < person->children.size(); ++i) {
            if ((temp = traverse(&(person->children[i]), id)) != nullptr)
                return temp;
        }
    }

    return nullptr;
}

Node& familyTree::getNode(const unsigned& id)
// 获取id指定节点的引用，若未找到，则 throw "NODE_NOT_FOUND"
// 使用时需要try & catch *ZJ*
{
    auto temp = traverse(root, id);
    if (temp == nullptr)
        return *root;
    return *temp;
}

string familyTree::nodeToString(Node &root) {
	vector<Node>::iterator itr = root.children.begin();
	string ans = "";
	if (itr == root.children.end()) {
		ans = ans + "<li>" + "<span id=\"" + to_string(root.id) 
			+ "\" class=\"" + ((root.detail.isMale) ? "Male" : "Female") + "\">" 
			+ root.detail.firstName + " " + root.detail.lastName + "</span>";

         for (itr = root.couple.begin(); itr != root.couple.end(); ++itr) {
			ans = ans + "<span id=\"" + to_string(itr->id) 
				+ "\" class=\"" + ((itr->detail.isMale) ? "Male" : "Female") + "\">" 
				+ (itr->detail).firstName + " " + (itr->detail).lastName + "</span>";
		}

        ans += "</li>";
	} else {
		ans = ans + "<li>" + "<span id=\"" + to_string(root.id) 
			+ "\" class=\"" + ((root.detail.isMale) ? "Male" : "Female") + "\">" 
			+ root.detail.firstName + " " + root.detail.lastName + "</span>";

		for (itr = root.couple.begin(); itr != root.couple.end(); ++itr) {
			ans = ans + "<span id=\"" + to_string(itr->id) 
				+ "\" class=\"" + ((itr->detail.isMale) ? "Male" : "Female") + "\">" 
				+ (itr->detail).firstName + " " + (itr->detail).lastName + "</span>";
		}

        ans += "<ul>";
		for (itr = root.children.begin(); itr != root.children.end(); ++itr) {
			ans += nodeToString(*itr);
        }
        
		ans += "</ul></li>";
	}
	return ans;
}

string familyTree::printTree() {
	string ans = "<ul>" + nodeToString(*root) + "</ul>";
	return ans;
}
