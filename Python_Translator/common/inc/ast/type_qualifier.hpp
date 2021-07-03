#ifndef type_qualifier_hpp
#define type_qualifier_hpp


class TypeQualifier: public Node{
  private:
    const char* types;
  public:
    TypeQualifier(const char* name_in): types(name_in){
      type = "TypeQualifier";
    }

    const std::string getTypes() const{
      std::string str(types);
      return str;
    }

    virtual std::ostream& print(std::ostream& outputstream, std::string IndentationLevel) const override //overloading operator to print contents of object.
    {
     outputstream << IndentationLevel << type << " [ " << types <<  std::endl;
     outputstream << std::endl << IndentationLevel << "]";
     return outputstream;
    }
};

#endif
