/****************************************************************************
** Meta object code from reading C++ file 'model.h'
**
** Created: Wed Mar 20 15:51:56 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/model.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mymodel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,    8,    9,    8, 0x0a,
      39,   33,    8,    8, 0x0a,
      54,   33,    8,    8, 0x0a,
      70,   33,    8,    8, 0x0a,
      87,   33,    8,    8, 0x0a,
     104,   33,    8,    8, 0x0a,
     122,   33,    8,    8, 0x0a,
     140,   33,    8,    8, 0x0a,
     159,   33,    8,    8, 0x0a,
     175,   33,    8,    8, 0x0a,
     200,   33,    8,    8, 0x0a,
     223,  221,    8,    8, 0x0a,
     247,  245,    8,    8, 0x0a,
     273,  268,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mymodel[] = {
    "mymodel\0\0double\0getfocalLength()\0angle\0"
    "dabiPitch(int)\0dabiRotate(int)\0"
    "xiaobiPitch(int)\0yuntaiPitch(int)\0"
    "yuntaiRotate(int)\0shouwanPitch(int)\0"
    "shouwanRotate(int)\0zhibiPitch(int)\0"
    "qianjinxiangjiPitch(int)\0shouzhuaMediate(int)\0"
    "x\0updateview_xz(double)\0y\0"
    "updateview_y(double)\0size\0updatesize(double)\0"
};

const QMetaObject mymodel::staticMetaObject = {
    { &GLViewWidget::staticMetaObject, qt_meta_stringdata_mymodel,
      qt_meta_data_mymodel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mymodel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mymodel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mymodel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mymodel))
        return static_cast<void*>(const_cast< mymodel*>(this));
    return GLViewWidget::qt_metacast(_clname);
}

int mymodel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GLViewWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { double _r = getfocalLength();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 1: dabiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: dabiRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: xiaobiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: yuntaiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: yuntaiRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: shouwanPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: shouwanRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: zhibiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: qianjinxiangjiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: shouzhuaMediate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: updateview_xz((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: updateview_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: updatesize((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
