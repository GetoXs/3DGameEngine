#include "cSceneList.h"

cScene::cScene(Ogre::SceneManager* oSceneMgr): oSceneMgr(oSceneMgr),cObject(oSceneMgr->getRootSceneNode())
{
	objectList.clearList();
}

cScene::~cScene()
{
	oSceneMgr=NULL;
	objectList.clearList();
}

unsigned cScene::addObject(cObject* object)
{
	return objectList.addObject(object);
}
bool cScene::delObject(unsigned idObject)
{
	cMovableObject* obj = (cMovableObject*)this->objectList.getObject(idObject);
	if(obj==NULL)
		return false;
	//Kasowanie z Ogre'owego scene Mgr
	oSceneMgr->destroyMovableObject(obj->getMovObj());
	return this->objectList.delObject(obj->getId());
}











//NIEUZYWANE
/*
cSceneElem::cSceneElem():scene(NULL),next(NULL)
{}

cSceneElem::~cSceneElem()
{
	if(scene!=NULL)
		delete scene;
	if(next!=NULL)
		delete next;
}
cSceneList::cSceneList():head(NULL),render(NULL)
{}
unsigned cSceneList::addScene()
{
	cSceneElem *tmp = head;
	head = new cSceneElem();
	head->scene = new cScene();
	head->next = tmp;
	return head->scene->getId();
}
cSceneList::~cSceneList()
{
	if (head!=NULL)
		delete head;
	render=NULL;
}
*/