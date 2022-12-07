#ifndef __LINK_H__
#define __LINK_H__

#include <cstddef>

namespace ds {

// Singly linked list node
template <typename E> class Link {
public:
  E element;  // Value for this node
  Link *next; // Pointer to next node in list

  // Constructors
  Link(const E &elemval, Link *nextval = NULL)
      : element(elemval), next(nextval) {}
  Link(Link *nextval = NULL) : next(nextval) {}
};

} // namespace ds

#endif // __LINK_H__
