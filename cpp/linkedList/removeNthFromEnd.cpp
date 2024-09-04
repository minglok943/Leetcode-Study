//19 Remove the Nth Node from End of list
#include <iostream>

using namespace std;
struct ListNode{
  int val;
  ListNode *next;
};

/*
 * Step 1: move first pointer n times 
 * 1 2 3 4 5
 * > >
 * Step 2: move first and second pointer until first->next = NULL
 * 1 2 3 4 5
 *     > > >
 * A A A
 *
 */    
ListNode* removeNthFromEnd(ListNode* head, int n){
  ListNode* first = head;
  ListNode* second = head;
  for(int i=n; i>0; i--){
    first = first->next;
  }
  if(first == NULL){
    //remove head
    return head->next;
  }else{
    ListNode* last;
    while(first != NULL){
      first = first->next;
      last = second;
      second = second->next;
    }
    last->next = second->next;

    /*
    * answer
    * while(first->next != NULL){
    *   first = first->next;
    *   second = second->next;
    * }
  *   second->next = second->next->next;
  */
  }
  return head;
}

int main (int argc, char *argv[]) {
  ListNode a{5};
  ListNode b{4, &a};
  ListNode c{3, &b};
  ListNode d{2, &c};
  ListNode e{1, &d};

  cout << "after 2: " << d.next->val << endl;
  ListNode removed = *removeNthFromEnd(&e, 2);
  cout << "after 3: " << c.next->val << endl;

  return 0;
}

