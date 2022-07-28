#include <typeinfo>

class TypeInfo {
public:
  TypeInfo();
  TypeInfo(const std::type_info&);
  bool before(const TypeInfo&) const;
  const std::type_info& Get() const;
  const char* name() const;
private:
  const std::type_info* pInfo_;
};

bool operator==(const TypeInfo&, const TypeInfo&);
bool operator!=(const TypeInfo&, const TypeInfo&);
bool operator<=(const TypeInfo&, const TypeInfo&);
bool operator>=(const TypeInfo&, const TypeInfo&);
bool operator<(const TypeInfo&, const TypeInfo&);
bool operator>(const TypeInfo&, const TypeInfo&);
