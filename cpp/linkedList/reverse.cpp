#include <iostream>

using namespace std;
struct ListNode{
  int val;
  ListNode *next;
};

ListNode* reverse(ListNode* head){
  ListNode* prev = NULL;
  ListNode* current = head;
  ListNode* next = NULL;
  while(current != NULL){
    next = current->next; //store original next
    current -> next = prev;

    prev = current;
    current = next;
  }
  head = prev;
  return head;
}
int main (int argc, char *argv[]) {
  ListNode a{5};
  ListNode b{4, &a};
  ListNode c{3, &b};
  ListNode d{2, &c};
  ListNode e{1, &d};

  cout << "after 2: " << d.next->val << endl;

  ListNode reversed = *reverse(&e);
  cout << "reversed: " << reversed.val << endl;
  cout << "rev next: " << reversed.next->val << endl;

  return 0;
}
