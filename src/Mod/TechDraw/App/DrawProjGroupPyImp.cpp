
#include "PreCompiled.h"

#include <App/DocumentObject.h>

#include "DrawProjGroup.h"
#include "DrawProjGroupItem.h"

// inclusion of the generated files (generated out of DrawProjGroupPy.xml)
#include <Mod/TechDraw/App/DrawProjGroupPy.h>
#include <Mod/TechDraw/App/DrawProjGroupPy.cpp>
#include <Mod/TechDraw/App/DrawProjGroupItemPy.h>

using namespace TechDraw;

// returns a string which represents the object e.g. when printed in python
std::string DrawProjGroupPy::representation(void) const
{
    return std::string("<DrawProjGroup object>");
}

PyObject* DrawProjGroupPy::addProjection(PyObject* args)
{
    const char* projType;

    if (!PyArg_ParseTuple(args, "s", &projType)) {
        throw Py::Exception();
    }

    DrawProjGroup* projGroup = getDrawProjGroupPtr();
    App::DocumentObject* docObj = projGroup->addProjection(projType);
    TechDraw::DrawProjGroupItem* newProj = dynamic_cast<TechDraw::DrawProjGroupItem *>( docObj );

    return new DrawProjGroupItemPy(newProj);
}

PyObject* DrawProjGroupPy::removeProjection(PyObject* args)
{
    const char* projType;

    if (!PyArg_ParseTuple(args, "s", &projType)) {
        throw Py::Exception();
    }

    DrawProjGroup* projGroup = getDrawProjGroupPtr();
    int i = projGroup->removeProjection(projType);

    return PyInt_FromLong((long) i);;
}

PyObject* DrawProjGroupPy::purgeProjections(PyObject* /*args*/)
{
    DrawProjGroup* projGroup = getDrawProjGroupPtr();
    int i = projGroup->purgeProjections();

    return PyInt_FromLong((long) i);;
}

PyObject* DrawProjGroupPy::getItemByLabel(PyObject* args)
{
    const char* projType;

    if (!PyArg_ParseTuple(args, "s", &projType)) {
        throw Py::Exception();
    }

    DrawProjGroup* projGroup = getDrawProjGroupPtr();
    App::DocumentObject* docObj = projGroup->getProjObj(projType);
    TechDraw::DrawProjGroupItem* newProj = dynamic_cast<TechDraw::DrawProjGroupItem *>( docObj );

    return new DrawProjGroupItemPy(newProj);
}

PyObject* DrawProjGroupPy::setViewOrientation(PyObject* args)
{
    const char* projType;
    PyObject* pcObj;
    if (!PyArg_ParseTuple(args, "Os", &pcObj,&projType))
        throw Py::Exception();

    App::DocumentObject* obj = static_cast<App::DocumentObjectPy*>(pcObj)->getDocumentObjectPtr();
    if (obj->getTypeId().isDerivedFrom(TechDraw::DrawProjGroupItem::getClassTypeId())) {
        TechDraw::DrawProjGroupItem* view = static_cast<TechDraw::DrawProjGroupItem*>(obj);
        TechDraw::DrawProjGroup* projGroup = getDrawProjGroupPtr();
        projGroup->setViewOrientation( view, projType );

    } else {
        Base::Console().Message("'%s' is not a DrawProjGroup Item, it will be ignored.\n", obj->Label.getValue());
    }

    return Py_None;
}


PyObject *DrawProjGroupPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int DrawProjGroupPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
