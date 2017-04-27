/****************************************************************************
** Meta object code from reading C++ file 'mythreadport.h'
**
** Created: Wed Mar 20 15:52:07 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mythreadport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mythreadport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SendThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SendThread[] = {
    "SendThread\0"
};

const QMetaObject SendThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SendThread,
      qt_meta_data_SendThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SendThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SendThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SendThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SendThread))
        return static_cast<void*>(const_cast< SendThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SendThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ReceiveThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      40,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ReceiveThread[] = {
    "ReceiveThread\0\0dataReceived(QByteArray)\0"
    "dataReceived1(QByteArray)\0"
};

const QMetaObject ReceiveThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ReceiveThread,
      qt_meta_data_ReceiveThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReceiveThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReceiveThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReceiveThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReceiveThread))
        return static_cast<void*>(const_cast< ReceiveThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ReceiveThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dataReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: dataReceived1((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ReceiveThread::dataReceived(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ReceiveThread::dataReceived1(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
