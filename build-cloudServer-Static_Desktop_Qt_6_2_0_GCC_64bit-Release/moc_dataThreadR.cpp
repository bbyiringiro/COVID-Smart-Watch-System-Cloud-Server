/****************************************************************************
** Meta object code from reading C++ file 'dataThreadR.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../cloudServer/dataThreadR.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataThreadR.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dataThreadR_t {
    const uint offsetsAndSize[18];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_dataThreadR_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_dataThreadR_t qt_meta_stringdata_dataThreadR = {
    {
QT_MOC_LITERAL(0, 11), // "dataThreadR"
QT_MOC_LITERAL(12, 5), // "error"
QT_MOC_LITERAL(18, 0), // ""
QT_MOC_LITERAL(19, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(43, 11), // "socketerror"
QT_MOC_LITERAL(55, 4), // "Read"
QT_MOC_LITERAL(60, 3), // "Dis"
QT_MOC_LITERAL(64, 6), // "ProDis"
QT_MOC_LITERAL(71, 5) // "TODis"

    },
    "dataThreadR\0error\0\0QTcpSocket::SocketError\0"
    "socketerror\0Read\0Dis\0ProDis\0TODis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dataThreadR[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   47,    2, 0x0a,    3 /* Public */,
       6,    0,   48,    2, 0x0a,    4 /* Public */,
       7,    0,   49,    2, 0x0a,    5 /* Public */,
       8,    0,   50,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dataThreadR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dataThreadR *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->Read(); break;
        case 2: _t->Dis(); break;
        case 3: _t->ProDis(); break;
        case 4: _t->TODis(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dataThreadR::*)(QTcpSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataThreadR::error)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject dataThreadR::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_dataThreadR.offsetsAndSize,
    qt_meta_data_dataThreadR,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_dataThreadR_t
, QtPrivate::TypeAndForceComplete<dataThreadR, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTcpSocket::SocketError, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *dataThreadR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dataThreadR::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dataThreadR.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int dataThreadR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void dataThreadR::error(QTcpSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
