#ifndef point_hpp
#define point_hpp

class Pointer: public Node{
  private:
    const Node* point_to;
  public:
    Pointer(const Node* point_in): point_to(point_in){
      type = "Pointer";
    }

    const Node* getPointer() const{
      return point_to;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << std::endl;
     if(point_to != nullptr){
       outputstream << point_to;
     }
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};



#endif
