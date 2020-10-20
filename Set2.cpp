#include <iostream>
#include <algorithm>
#include <sstream>

#define ERROR 0
#define	OK 1
#define TRUE 1
#define	FALSE 0
#define	OVERFLOW -2
using namespace std;
typedef int Status;
typedef string ElemType;
typedef struct Node {
	ElemType data;//����Ԫ�� 
	struct Node *next;//��һ���ڵ�ĵ�ַ
}Node,*PNode;//�����ڵ�Ľṹ�� 

typedef struct List{
	PNode head;//���ϵ�ͷ�ڵ�
	PNode tail;//�����е����һ��Ԫ�����ڽڵ� 
	int length;//������Ԫ�صĸ���
}List,*PList;

Status ListLength(List L,int &index);
Status InitList(List &L);//��ʼ�����Ա�                                 //�ο��� 
Status DestroyList(List &L);//�������Ա� 								//�ο���
Status ClearList(List &L);
Status ListEmpty(List L);//�ж����Ա��Ƿ�Ϊ��                           //��ΰ 
Status GetElem(List L,int index,ElemType &e);//��ȡ���Ա�indexλ�õ�Ԫ��//�¾� 
Status LocateElem(List L,ElemType e);//�ж�e�Ƿ���L�У� ���ڷ���false     //�¾� 
Status Append(List &L,ElemType e);//���e�����Ա�ĩβ               //������
//Status SetAppend(List &L,ElemType e);//���Ԫ�ص�������Ĭ������λ�ã�Ĭ�ϰ����ֵ�˳��λ������ 
Status InsertElem(List &L,int index,ElemType e);//����e��indexλ��      //������ 
Status removeElem(List &L,ElemType e);//ɾ�����Ա���eԪ��               //������ 
Status removeIndex(List &L,int index);//ɾ�����Ա���index��Ԫ��         //������ 
Status removalReapted(List &L);//ȥ�����Ա����ظ�Ԫ��                   //������ 
Status sort(List &L,bool Bool=true);//�����Ա�����Ĭ������            //��ΰ
Status printList(List L);

Status CreateSet(List &L,ElemType *s,int length);//��������                            //������ 
Status CreateSet(List &L);
Status DestroySet(List &L);//���ټ���                                   //������ 
Status Union(List L1,List L2,List &L3);//����                           //������ 
Status Intersection(List L1,List L2,List &L3);//����                    //�¾� 
Status Complement(List L1,List L2,List &L3);//����                      //�ο��� 
Status Difference(List L1,List L2,List &L3);//�                      //��ΰ 
Status Copy(List L1,List &L2);
Status strDeal(string *deal,int &length);
bool isNum(string str);

Status Copy(List L1,List &L2){
	if(!L1.head){
		return ERROR;
	}
	PNode current = L1.head->next;
	while(current){
		Append(L2,current->data);
		current = current->next;
	}
	
	return OK;
}

Status Complement(List L1,List L2,List &L3){
	PNode node_l2 = L2.head;
	
	for(int i = 1;i <= L2.length;i++){
		node_l2 = node_l2->next;
		if(!LocateElem(L1,node_l2->data)){
			Append(L3,node_l2->data);
		}
	}
	sort(L3);
	return OK;
}

Status Difference(List L1,List L2,List &L3){
	PNode node_l1 = L1.head;
	
	for(int i = 1;i <= L1.length;i++){
		node_l1 = node_l1->next;
		if(!LocateElem(L2,node_l1->data)){
			Append(L3,node_l1->data);
		}
	}
	sort(L3);
	return OK;
}

Status Intersection(List L1,List L2,List &L3){
	PNode node_b = L2.head;
	
	for(int i = 1;i <= L2.length;i++){
		node_b = node_b->next;
		if(LocateElem(L1,node_b->data)){
			Append(L3,node_b->data);
		}
	}
	sort(L3);
	return OK;
}

Status Union(List L1,List L2,List &L3){
	PNode node_l2 = L2.head;
	Copy(L1,L3);
	
	for(int i = 1;i<= L2.length;i++){
		node_l2 = node_l2->next;
		if(!LocateElem(L3,node_l2->data)){
			Append(L3,node_l2->data);
		}
	}
	sort(L3);
	return OK;
	
}

Status CreateSet(List &L,ElemType *s,int length){
	if(InitList(L)){
		for(int i=0;i<length;i++){
			if(!LocateElem(L,s[i])){
				Append(L,s[i]);
			}
		}
		sort(L);//���� 
		return OK;
	}	
	
	return ERROR;
}

Status CreateSet(List &L){
	if(InitList(L)){
		return OK;
	}
	
	return ERROR;
}

//���ټ��� 
Status DestroySet(List &L){
	DestroyList(L);
}

ostream& operator<<(ostream& output,List &L){
	printList(L);
	return output;
}

float stringToNum(const string& str)  
{  
    istringstream iss(str);  
    float num;  
    iss >> num;  
    return num;      
}

Status sort(List &L,bool Bool){
	int flag = 1;
	ElemType temp;
	PNode current;
	
	current = L.head->next;
	for(int i = 1;i < L.length;i++){
		if(!isNum(current->data)){
			flag = 0;
			break;
		}
		current = current->next;
	} 
	//��������
	if(flag){
		if(Bool){		
			for(int i = L.length;i>=2;i--){
				current = L.head->next;
				for(int j = 1;j < i;j++){
					if(stringToNum(current->data) > stringToNum(current->next->data)){
						temp = current->data;
						current->data=current->next->data;
						current->next->data = temp;
					}
					current = current->next;
				}	
			}
		}else{
			for(int i = L.length;i>=2;i--){
				current = L.head->next;
				for(int j = 1;j < i;j++){
					if(stringToNum(current->data) < stringToNum(current->next->data)){
						temp = current->data;
						current->data=current->next->data;
						current->next->data = temp;
					}
					current = current->next;
				}	
			}
		}
	}else{
			//�ַ����� 
		if(Bool){		
			for(int i = L.length;i>=2;i--){
				current = L.head->next;
				for(int j = 1;j < i;j++){
					if(current->data > current->next->data){
						temp = current->data;
						current->data=current->next->data;
						current->next->data = temp;
					}
					current = current->next;
				}	
			}
		}else{
			for(int i = L.length;i>=2;i--){
				current = L.head->next;
				for(int j = 1;j < i;j++){
					if(current->data < current->next->data){
						temp = current->data;
						current->data=current->next->data;
						current->next->data = temp;
					}
					current = current->next;
				}	
			}
		}
		
	}

	
	return OK;
}

bool isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}

Status removeReated(List &L){
	if(!L.head){
		return ERROR;
	}
	
	PNode current = L.head->next;
	
	for(int i = 1;i <= L.length;i++){
		PNode temp = current;	
		for(int j = i+1;j < L.length;j++){
			if(current->data == temp->next->data){
				PNode f = temp->next;
				temp->next = f->next;
				delete f;
				L.length--;
			}
			
			temp = temp->next;
		}
		
		current = current->next;
	}
	
	return OK;
}
Status ListLength(List L,int &index){
	if(!L.head){
		return ERROR;
	}
	return L.length;
}
Status InitList(List &L){
	L.head = L.head = new Node;//L.head = (PNode)malloc(sizeof(Node));
	if(!L.head){
		return ERROR;
	}
	
	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;
	
	return OK;
}                              
Status DestroyList(List &L){
   if(!L.head){
      return ERROR;
   }
   PNode current = L. head;
   while(current){
      PNode f = current;
      current = current->next;
      delete f;
   }
//   PNode p;
//   while(L.head != L.tail){
//		p = L.head;
//		L.head = L.head->next;
//		free(p);
//	} 
	
//	free(L.head);
//printf("���ٳɹ�");
	return OK;
}
Status ClearList(List &L){
   if(!L.head){
      return ERROR;
   }
   PNode current = L. head;
   while(current != L.tail){
      PNode f = current;
      current = current->next;
      delete f;
   }
   L.head = L.tail;
   L.length = 0;
   return OK;
}
Status ListEmpty(List &L){
	if(!L.head){
		return TRUE;
	}
	
	return FALSE;
}
Status GetElem(List L,int index,ElemType &e){
	if(!L.head || index < 1 || index > L.length){
		return ERROR;
	}
	PNode current = L.head;
	int i = 0;
	while(i != index){
		current = current->next;
		i++;
	}
	
	e = current->data;
	
	return OK;
}
Status LocateElem(List L,ElemType e){
	if(!L.head){
		return FALSE;
	}
	
	PNode current = L.head->next;
	while(current){
		if(current->data == e){
			return TRUE;
		}
		current = current->next;
	}
	
	return FALSE;
}
//Status SetAppend(List &L,ElemType e){
//	if(!L.head || LocateElem(L,e)){ 
//		return ERROR;
//	}
//	
//	PNode newNode = new Node;//(PNode)malloc(sizeof(Node));
//	newNode->data = e;
//	if(L.length == 0){
//		newNode->next = NULL;
//		L.head->next = newNode;
//		L.tail = newNode;
//	}else{
//		PNode current = L.head->next;
//	
//		while(current != L.tail){
//			if((current->data < e && e < current->next->data) || (current->data > e && e > current->next->data)){
//				newNode->next = current->next;
//				current->next= newNode;
//				L.length++;
//				return OK;
//			}
//			current = current->next;
//		}
//	
//		if(e<L.head->next->data && L.head->next->data < L.tail->data){//ͷ�� 
//			newNode->next = L.head->next;
//			L.head->next = newNode;
//		}else{//β�� 
//			newNode->next = NULL;
//			L.tail->next = newNode;
//			L.tail = newNode;
//		} 
//	}
//	
//	L.length++;
//	return OK;
//}

Status Append(List &L,ElemType e){
	if(!L.head){
		return ERROR;
	}
	
	PNode newNode = new Node;
	newNode->data = e;
	newNode->next = NULL;
	
	L.tail->next = newNode;
	L.tail = newNode;
	L.length++;
	return OK;
}
Status InsertElem(List &L,int index,ElemType e){
	if(!L.head){
		return ERROR;
	}
	
	if(index < 1 || index > L.length+1){
		return OVERFLOW;
	}
	int i = 1;
	
	PNode current = L.head;
	while(i != index){
		current = current->next;
		i++;
	}
	
	PNode newNode = new Node;
	
	newNode->data = e;
	newNode->next=current->next;
	current->next = newNode;
	
	if(index == L.length+1){
		L.tail = newNode;
	}
	
	L.length++;
	return OK;
}
Status removeIndex(List &L,int index)
{   
	if(!L.head || L.length == 0){
		return ERROR;
	}
	
	if(index < 1 || index > L.length){
		return OVERFLOW;
	}
	PNode current = L.head;
	int i = 0;
	while(++i != index){
		current = current->next;
	}
	
	PNode f = current->next;
	current->next = f->next;
	delete f; 
	L.length--;
	
	return OK;
}

Status removeElem(List &L,ElemType e){
	if(!L.head || L.length == 0){
		return ERROR;
	}
	
	PNode current = L.head;
	
	while(current){
		current = current->next;
			
		if(current->data == e){
			PNode f = current->next;
			current = f;
			
			delete f;
			L.length--;
			return OK;
		}
	}
	
	return OVERFLOW;

}
Status printList(List L){
	if(!L.head){
		return ERROR;
	}
	
	cout << "{";
	if(!L.length){
		cout<<"}"<<endl;
		return OK; 
	}
	
	PNode current = L.head->next;

	for(int i = 1;i < L.length;i++){
		cout<<current->data<<",";
		current = current->next;
	}

	cout<<current->data<<"}"<<endl;	
	return OK;
}

void inputSet(List &set){
	ElemType *deal;
	int length;
	while(1){
		string str;
		cin>>str;
		
		if(str.length()==2){
			deal = new string[0];
			length = 0;
			break;
		}
		
		int former = str.find("{");
		int later = str.find("}");
		int count_former = count(str.begin(),str.end(),'{');
		int count_later = count(str.begin(),str.end(),'}');
		int count_Elem = count(str.begin(),str.end(),',')+1;
		//�������Ϸ���
		if(former != 0 || later != str.length()-1 || count_former != 1 || count_later != 1){ 
			cout<<"��������:����������:";
		}else{
			deal = new string[count_Elem];	
	
			str[0] = ',';
			str[str.length()-1] = ',';
			//��ȡԪ�� 
			for(int current = 0,next,i=0;current < str.length() && i < count_Elem;i++){
				next = str.find_first_of(',',current+1);
				deal[i] = str.substr(current+1,next-current-1);
				current = next;
			} 
			length = count_Elem;
			
			break;
		}
	}
	
	CreateSet(set,deal,length);
	delete[] deal;// 
}

int main(){
	cout<<"��������ʾ����{1,2,3,4,8}��{\"word\",\"ppt\",\"append\"}��{'a','b','c','f'}"<<endl; 
	while(1){
Lab:	List set1;
		List set2;
		List set3;
		CreateSet(set3);
		cout<<"�����뼯��A:"; 
		inputSet(set1);
		cout<<"�����뼯��B:";
		inputSet(set2);
		
		cout<<"1.�󽻼�:A��B"<<endl;
		cout<<"2.�󲢼�:AUB"<<endl;
		cout<<"3.�󲹼�:!A��AUBΪȫ����"<<endl;
		cout<<"4.�󲹼�:!B��AUBΪȫ����"<<endl;
		cout<<"5.��:A-B"<<endl;
		cout<<"6.��:B-A"<<endl;
		cout<<"7.�������뼯��"<<endl;
		cout<<"8.�˳�"<<endl;
		while(1){
			cout<<"��ѡ�������";
			int ch;
			cin>>ch;
			switch(ch){
				case 1:Intersection(set1,set2,set3);cout<<set3;ClearList(set3);break;//���� 
				case 2:Union(set1,set2,set3);cout<<set3;ClearList(set3);break;//���� 
				case 3:Complement(set1,set2,set3);cout<<set3;ClearList(set3);break;//!A��AUBΪȫ����
				case 4:Complement(set2,set1,set3);cout<<set3;ClearList(set3);break;//!B��AUBΪȫ���� 
				case 5:Difference(set1,set2,set3);cout<<set3;ClearList(set3);break;//A-B
				case 6:Difference(set2,set1,set3);cout<<set3;ClearList(set3);break;//B-A
				case 7:DestroySet(set1);DestroySet(set2);DestroySet(set3);goto Lab;//�������뼯�� 
				case 8:DestroySet(set1);DestroySet(set2);DestroySet(set3);exit(0);//�˳� 
				default:cout<<"��������!"; break;
			}	
		}	
	}
	
	return 0;
}
	
	




