#include "type_info.h"

TypeInfo::TypeInfo() : pInfo_(nullptr) {}

TypeInfo::TypeInfo(const std::type_info& info) : pInfo_(&info) {}

bool TypeInfo::before(const TypeInfo& info) const {
  return pInfo_->before(*info.pInfo_);
}

bool operator==(const TypeInfo& lhs, const TypeInfo& rhs) {
  return lhs.Get()==rhs.Get();
}

bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs) {
  return lhs.Get()!=rhs.Get();
}

bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs) {
  return !(lhs.Get()>rhs.Get());
}

bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs) {
  return !(lhs.Get()<rhs.Get());
}

bool operator>(const TypeInfo& lhs, const TypeInfo& rhs) {
  return lhs.Get()>rhs.Get();
}

bool operator<(const TypeInfo& lhs, const TypeInfo& rhs) {
  return lhs.Get()<rhs.Get();
}
