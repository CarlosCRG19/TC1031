/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *inicio, *previo;
        if(l1==NULL) return l2;
        if(l2==NULL) return l1;
        
        if(l1->val < l2->val){
            inicio = l1;
            l1= l1->next;
        }else{
            inicio=l2;
            l2=l2->next;
        }
        cout<<inicio->val;
        previo=inicio;
        while(l1!= NULL && l2 != NULL){
            if(l1->val < l2->val){
                previo->next=l1;
                previo= l1;
                l1= l1->next;
            }else{
                previo->next=l2;
                previo= l2;
                l2= l2->next;
            }
        }
        if(l1== NULL){
            previo->next=l2;
        }
        if(l2==NULL){
            previo->next=l1;
        }
        return inicio;
    }
};