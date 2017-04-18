/****************************************************************************
** Meta object code from reading C++ file 'glviewwidget.h'
**
** Created: Tue Jul 24 16:23:55 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/glviewwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glviewwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLViewWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      36,   30,   13,   13, 0x0a,
      62,   56,   13,   13, 0x0a,
     100,   79,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLViewWidget[] = {
    "GLViewWidget\0\0cameraChanged()\0delta\0"
    "moveView(QVector3D)\0scale\0scaleView(qreal)\0"
    "anglex,angley,anglez\0rorateView(qreal,qreal,qreal)\0"
};

const QMetaObject GLViewWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLViewWidget,
      qt_meta_data_GLViewWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLViewWidget))
        return static_cast<void*>(const_cast< GLViewWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cameraChanged(); break;
        case 1: moveView((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 2: scaleView((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 3: rorateView((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
