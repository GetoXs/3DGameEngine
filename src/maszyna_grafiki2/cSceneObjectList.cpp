#include "cSceneObjectList.h"

cSceneObjectElem::cSceneObjectElem():next(NULL), object(NULL)
{}
cSceneObjectElem::~cSceneObjectElem()
{
	if(object!=NULL)
		delete object;
	if(next!=NULL)
		delete next;
}
cSceneObjectList::cSceneObjectList(void):head(NULL), count(0)
{}
cSceneObjectList::~cSceneObjectList(void)
{
	count=0;
	if (head!=NULL)
		delete head;
}
unsigned cSceneObjectList::addObject(cObject* object)
{
	if(object==NULL)
		return 0;
	cSceneObjectElem* tmp = head;
	head = new cSceneObjectElem();
	head->object = object;
	head->next = tmp;
	count++;
	return head->object->getId();
}
void cSceneObjectList::clearList()
{
	if(head!=NULL)
		delete head;
	head=NULL;
	count=0;
}
bool cSceneObjectList::delObject(unsigned idObject)
{
	cSceneObjectElem* tmp2,* tmp1=head;
	if(head==NULL)
		return false;
	if(head->object->getId()==idObject)
	{
		head = head->next;
		delete tmp1;
		return true;
	}else	
		while(tmp1->next!=NULL)
		{
			if(tmp1->next->object->getId()==idObject)
			{
				tmp2=tmp1->next;
				tmp1->next=tmp2->next;
				delete tmp2;
				return true;
			}
			tmp1 = tmp1->next;
		}
	return false;	//not found
}
bool cSceneObjectList::isId(unsigned idObject)
{
	cSceneObjectElem* tmp=head;
	while(tmp!=NULL)
	{
		if(tmp->object->getId()==idObject)
			return true;
		tmp=tmp->next;
	}
	return false;
}
cObject* cSceneObjectList::getObject(unsigned idObject)
{
	cSceneObjectElem* tmp=head;
	while(tmp!=NULL)
	{
		if(tmp->object->getId()==(idObject))
			return tmp->object;
		tmp = tmp->next;
	}
	return NULL;
}