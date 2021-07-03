#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>
#include <map>
#include <memory>

//k

class Node;

typedef const Node* NodePtr;

class Node {
 protected:   // the type of token the node is.
  std::string type;

 public:
  virtual ~Node() {}

  virtual const std::string& getType() const {
    return type;
  };

  // Tell and node to print itself to the given stream.
  virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const = 0;
};


#endif
