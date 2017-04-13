/****************************************************************************
** Meta object code from reading C++ file 'qpotentiostat.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GamryChronoAmperometrySimpleUI/qpotentiostat.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpotentiostat.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gamry__QPotentiostat_t {
    QByteArrayData data[14];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gamry__QPotentiostat_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gamry__QPotentiostat_t qt_meta_stringdata_Gamry__QPotentiostat = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Gamry::QPotentiostat"
QT_MOC_LITERAL(1, 21, 7), // "polling"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "detected"
QT_MOC_LITERAL(4, 39, 13), // "dataAvailable"
QT_MOC_LITERAL(5, 53, 40), // "std::vector<Gamry::CookInform..."
QT_MOC_LITERAL(6, 94, 17), // "experimentStarted"
QT_MOC_LITERAL(7, 112, 15), // "startExperiment"
QT_MOC_LITERAL(8, 128, 5), // "vInit"
QT_MOC_LITERAL(9, 134, 5), // "tInit"
QT_MOC_LITERAL(10, 140, 6), // "vFinal"
QT_MOC_LITERAL(11, 147, 6), // "tFinal"
QT_MOC_LITERAL(12, 154, 10), // "sampleRate"
QT_MOC_LITERAL(13, 165, 14) // "stopExperiment"

    },
    "Gamry::QPotentiostat\0polling\0\0detected\0"
    "dataAvailable\0std::vector<Gamry::CookInformationPoint>\0"
    "experimentStarted\0startExperiment\0"
    "vInit\0tInit\0vFinal\0tFinal\0sampleRate\0"
    "stopExperiment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gamry__QPotentiostat[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    1,   46,    2, 0x06 /* Public */,
       6,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    5,   50,    2, 0x0a /* Public */,
      13,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    8,    9,   10,   11,   12,
    QMetaType::Void,

       0        // eod
};

void Gamry::QPotentiostat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QPotentiostat *_t = static_cast<QPotentiostat *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->polling(); break;
        case 1: _t->detected(); break;
        case 2: _t->dataAvailable((*reinterpret_cast< std::vector<Gamry::CookInformationPoint>(*)>(_a[1]))); break;
        case 3: _t->experimentStarted(); break;
        case 4: _t->startExperiment((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 5: _t->stopExperiment(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QPotentiostat::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QPotentiostat::polling)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QPotentiostat::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QPotentiostat::detected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QPotentiostat::*_t)(std::vector<Gamry::CookInformationPoint> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QPotentiostat::dataAvailable)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QPotentiostat::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QPotentiostat::experimentStarted)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Gamry::QPotentiostat::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Gamry__QPotentiostat.data,
      qt_meta_data_Gamry__QPotentiostat,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Gamry::QPotentiostat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gamry::QPotentiostat::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Gamry__QPotentiostat.stringdata0))
        return static_cast<void*>(const_cast< QPotentiostat*>(this));
    return QObject::qt_metacast(_clname);
}

int Gamry::QPotentiostat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Gamry::QPotentiostat::polling()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Gamry::QPotentiostat::detected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Gamry::QPotentiostat::dataAvailable(std::vector<Gamry::CookInformationPoint> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Gamry::QPotentiostat::experimentStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
