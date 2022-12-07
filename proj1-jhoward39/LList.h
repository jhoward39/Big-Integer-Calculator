#ifndef __LLIST_H__
#define __LLIST_H__

#include "Link.h"
#include "List.h"
#include <iostream>

namespace ds {

// Linked list implementation
template <typename E> class LList : public List<E> {
private:
  Link<E> *head; // Pointer to list header
  Link<E> *tail; // Pointer to last element
  Link<E> *curr; // Access to current element
  int cnt;       // Size of list

  void init() { // Initialization helper method
    curr = tail = head = new Link<E>;
    cnt = 0;
  }

  void removeall() { // Return link nodes to free store
    while (head != NULL) {
      curr = head;
      head = head->next;
      delete curr;
    }
  }

public:
  LList() { init(); }

  LList(const LList<E> &other) {
    init();
    for (Link<E> *otherCurr = other.head->next; otherCurr != NULL;
         otherCurr = otherCurr->next) {
      append(otherCurr->element);
    }
  }

  // Destructor
  ~LList() { removeall(); }

  // Clear list
  void clear() {
    removeall();
    init();
  }

  // Insert "it" at current position
  void insert(const E &it) {
    curr->next = new Link<E>(it, curr->next);
    if (tail == curr)
      tail = curr->next; // New tail
    cnt++;
  }

  // Append "it" to list
  void append(const E &it) {
    tail = tail->next = new Link<E>(it, NULL);
    cnt++;
  }

  // Remove and return current element
  E remove() {
    assert(curr->next != NULL);
    E it = curr->next->element; // Remember value
    Link<E> *temp = curr->next; // Remember link node
    if (tail == curr->next)
      tail = curr;                 // Reset tail
    curr->next = curr->next->next; // Remove from list
    delete temp;                   // Reclaim space
    cnt--;                         // Decrement the count
    return it;
  }

  // Place curr at list start
  void moveToStart() { curr = head; }

  // Place curr at list end
  void moveToEnd() { curr = tail; }

  // Move curr one step left; no change if already at front
  void prev() {
    if (curr == head)
      return; // No previous element
    Link<E> *temp = head;
    // March down list until we find the previous element
    while (temp->next != curr)
      temp = temp->next;
    curr = temp;
  }

  // Move curr one step right; no change if already at end
  void next() {
    if (curr != tail)
      curr = curr->next;
  }

  // Return length
  int length() const { return cnt; }

  // Return the position of the current element
  int currPos() const {
    Link<E> *temp = head;
    int i;
    for (i = 0; curr != temp; i++)
      temp = temp->next;
    return i;
  }

  // Move down list to "pos" position
  void moveToPos(int pos) {
    assert((pos >= 0) && (pos <= cnt));
    curr = head;
    for (int i = 0; i < pos; i++)
      curr = curr->next;
  }

  // Return current element
  const E &getValue() const {
    assert(curr->next != NULL);
    return curr->next->element;
  }

  // Return element at `pos`
  const E &getValueAt(int pos) const {
    assert((pos >= 0) && (pos < cnt));
    Link<E> *tmp = head;
    for (int i = 0; i < pos; i++)
      tmp = tmp->next;
    return tmp->next->element;
  }
};

} // namespace ds

#endif // __LLIST_H__