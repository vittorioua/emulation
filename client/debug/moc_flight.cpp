/****************************************************************************
** Meta object code from reading C++ file 'flight.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../flight.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Flight_t {
    QByteArrayData data[9];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Flight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Flight_t qt_meta_stringdata_Flight = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Flight"
QT_MOC_LITERAL(1, 7, 10), // "flightData"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 12), // "flightNumber"
QT_MOC_LITERAL(4, 32, 5), // "Place"
QT_MOC_LITERAL(5, 38, 4), // "from"
QT_MOC_LITERAL(6, 43, 2), // "to"
QT_MOC_LITERAL(7, 46, 10), // "timeFlight"
QT_MOC_LITERAL(8, 57, 6) // "change"

    },
    "Flight\0flightData\0\0flightNumber\0Place\0"
    "from\0to\0timeFlight\0change"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Flight[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 4, QMetaType::Int,    3,    5,    6,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Flight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Flight *_t = static_cast<Flight *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flightData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Place(*)>(_a[2])),(*reinterpret_cast< Place(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->change(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Flight::*_t)(int , Place , Place , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Flight::flightData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Flight::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Flight.data,
      qt_meta_data_Flight,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Flight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Flight::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Flight.stringdata0))
        return static_cast<void*>(const_cast< Flight*>(this));
    return QObject::qt_metacast(_clname);
}

int Flight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Flight::flightData(int _t1, Place _t2, Place _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
