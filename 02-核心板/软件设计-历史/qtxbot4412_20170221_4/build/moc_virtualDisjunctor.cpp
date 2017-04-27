/****************************************************************************
** Meta object code from reading C++ file 'virtualDisjunctor.h'
**
** Created: Mon Jun 24 17:03:52 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/virtualDisjunctor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtualDisjunctor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VirtualDisjunctor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      29,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   18,   18,   18, 0x0a,
      55,   18,   18,   18, 0x0a,
      66,   18,   18,   18, 0x0a,
      79,   18,   18,   18, 0x0a,
     100,   18,   18,   18, 0x0a,
     123,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VirtualDisjunctor[] = {
    "VirtualDisjunctor\0\0pressed()\0released()\0"
    "setValue(bool)\0setPress()\0setRelease()\0"
    "setPressIco(QString)\0setReleaseIco(QString)\0"
    "resetValue()\0"
};

const QMetaObject VirtualDisjunctor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VirtualDisjunctor,
      qt_meta_data_VirtualDisjunctor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VirtualDisjunctor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VirtualDisjunctor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VirtualDisjunctor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualDisjunctor))
        return static_cast<void*>(const_cast< VirtualDisjunctor*>(this));
    return QWidget::qt_metacast(_clname);
}

int VirtualDisjunctor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pressed(); break;
        case 1: released(); break;
        case 2: setValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setPress(); break;
        case 4: setRelease(); break;
        case 5: setPressIco((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: setReleaseIco((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: resetValue(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void VirtualDisjunctor::pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VirtualDisjunctor::released()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
