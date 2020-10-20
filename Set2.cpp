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
	ElemType data;//数据元素 
	struct Node *next;//下一个节点的地址
}Node,*PNode;//单个节点的结构体 

typedef struct List{
	PNode head;//集合的头节点
	PNode tail;//集合中的最后一个元素所在节点 
	int length;//集合中元素的个数
}List,*PList;

Status ListLength(List L,int &index);
Status InitList(List &L);//初始化线性表                                 //何凯艳 
Status DestroyList(List &L);//销毁线性表 								//何凯艳
Status ClearList(List &L);
Status ListEmpty(List L);//判断线性表是否为空                           //张伟 
Status GetElem(List L,int index,ElemType &e);//获取线性表index位置的元素//陈静 
Status LocateElem(List L,ElemType e);//判断e是否在L中， 不在返回false     //陈静 
Status Append(List &L,ElemType e);//添加e到线性表末尾               //邱润明
//Status SetAppend(List &L,ElemType e);//添加元素到集合中默认排序位置，默认按照字典顺序位置排序 
Status InsertElem(List &L,int index,ElemType e);//插入e到index位置      //邱润明 
Status removeElem(List &L,ElemType e);//删除线性表中e元素               //邱润明 
Status removeIndex(List &L,int index);//删除线性表中index号元素         //邱润明 
Status removalReapted(List &L);//去除线性表中重复元素                   //邱润明 
Status sort(List &L,bool Bool=true);//给线性表排序，默认升序            //张伟
Status printList(List L);

Status CreateSet(List &L,ElemType *s,int length);//创建集合                            //安嘉琪 
Status CreateSet(List &L);
Status DestroySet(List &L);//销毁集合                                   //安嘉琪 
Status Union(List L1,List L2,List &L3);//并集                           //安嘉琪 
Status Intersection(List L1,List L2,List &L3);//交集                    //陈静 
Status Complement(List L1,List L2,List &L3);//补集                      //何凯艳 
Status Difference(List L1,List L2,List &L3);//差集                      //张伟 
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
		sort(L);//排序 
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

//销毁集合 
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
	//数字排序
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
			//字符排序 
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
//printf("销毁成功");
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
//		if(e<L.head->next->data && L.head->next->data < L.tail->data){//头插 
//			newNode->next = L.head->next;
//			L.head->next = newNode;
//		}else{//尾插 
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
		//检查输入合法性
		if(former != 0 || later != str.length()-1 || count_former != 1 || count_later != 1){ 
			cout<<"输入有误:请重新输入:";
		}else{
			deal = new string[count_Elem];	
	
			str[0] = ',';
			str[str.length()-1] = ',';
			//提取元素 
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
	cout<<"集合输入示例：{1,2,3,4,8}或{\"word\",\"ppt\",\"append\"}或{'a','b','c','f'}"<<endl; 
	while(1){
Lab:	List set1;
		List set2;
		List set3;
		CreateSet(set3);
		cout<<"请输入集合A:"; 
		inputSet(set1);
		cout<<"请输入集合B:";
		inputSet(set2);
		
		cout<<"1.求交集:A∩B"<<endl;
		cout<<"2.求并集:AUB"<<endl;
		cout<<"3.求补集:!A（AUB为全集）"<<endl;
		cout<<"4.求补集:!B（AUB为全集）"<<endl;
		cout<<"5.求差集:A-B"<<endl;
		cout<<"6.求差集:B-A"<<endl;
		cout<<"7.重新输入集合"<<endl;
		cout<<"8.退出"<<endl;
		while(1){
			cout<<"请选择操作：";
			int ch;
			cin>>ch;
			switch(ch){
				case 1:Intersection(set1,set2,set3);cout<<set3;ClearList(set3);break;//交集 
				case 2:Union(set1,set2,set3);cout<<set3;ClearList(set3);break;//并集 
				case 3:Complement(set1,set2,set3);cout<<set3;ClearList(set3);break;//!A（AUB为全集）
				case 4:Complement(set2,set1,set3);cout<<set3;ClearList(set3);break;//!B（AUB为全集） 
				case 5:Difference(set1,set2,set3);cout<<set3;ClearList(set3);break;//A-B
				case 6:Difference(set2,set1,set3);cout<<set3;ClearList(set3);break;//B-A
				case 7:DestroySet(set1);DestroySet(set2);DestroySet(set3);goto Lab;//重新输入集合 
				case 8:DestroySet(set1);DestroySet(set2);DestroySet(set3);exit(0);//退出 
				default:cout<<"操作有误!"; break;
			}	
		}	
	}
	
	return 0;
}
	
	




