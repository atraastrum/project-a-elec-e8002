/****************************************************************************
** Meta object code from reading C++ file 'gamrywidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GamryExperimentControlAndVisualizationClassTestUI/gamrywidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamrywidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gamry__GamryWidget_t {
    QByteArrayData data[19];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gamry__GamryWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gamry__GamryWidget_t qt_meta_stringdata_Gamry__GamryWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Gamry::GamryWidget"
QT_MOC_LITERAL(1, 19, 7), // "polling"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "detected"
QT_MOC_LITERAL(4, 37, 17), // "experimentStarted"
QT_MOC_LITERAL(5, 55, 19), // "experimentComplited"
QT_MOC_LITERAL(6, 75, 16), // "emitpollingevent"
QT_MOC_LITERAL(7, 92, 17), // "emitdetectedevent"
QT_MOC_LITERAL(8, 110, 21), // "emitexperimentStarted"
QT_MOC_LITERAL(9, 132, 10), // "updatePlot"
QT_MOC_LITERAL(10, 143, 40), // "std::vector<Gamry::CookInform..."
QT_MOC_LITERAL(11, 184, 4), // "data"
QT_MOC_LITERAL(12, 189, 15), // "startExperiment"
QT_MOC_LITERAL(13, 205, 5), // "vInit"
QT_MOC_LITERAL(14, 211, 5), // "tInit"
QT_MOC_LITERAL(15, 217, 6), // "vFinal"
QT_MOC_LITERAL(16, 224, 6), // "tFinal"
QT_MOC_LITERAL(17, 231, 10), // "sampleRate"
QT_MOC_LITERAL(18, 242, 14) // "stopExperiment"

    },
    "Gamry::GamryWidget\0polling\0\0detected\0"
    "experimentStarted\0experimentComplited\0"
    "emitpollingevent\0emitdetectedevent\0"
    "emitexperimentStarted\0updatePlot\0"
    "std::vector<Gamry::CookInformationPoint>\0"
    "data\0startExperiment\0vInit\0tInit\0"
    "vFinal\0tFinal\0sampleRate\0stopExperiment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gamry__GamryWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      12,    5,   74,    2, 0x0a /* Public */,
      18,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   13,   14,   15,   16,   17,
    QMetaType::Void,

       0        // eod
};

void Gamry::GamryWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GamryWidget *_t = static_cast<GamryWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->polling(); break;
        case 1: _t->detected(); break;
        case 2: _t->experimentStarted(); break;
        case 3: _t->experimentComplited(); break;
        case 4: _t->emitpollingevent(); break;
        case 5: _t->emitdetectedevent(); break;
        case 6: _t->emitexperimentStarted(); break;
        case 7: _t->updatePlot((*reinterpret_cast< std::vector<Gamry::CookInformationPoint>(*)>(_a[1]))); break;
        case 8: _t->startExperiment((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 9: _t->stopExperiment(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GamryWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GamryWidget::polling)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GamryWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GamryWidget::detected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GamryWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GamryWidget::experimentStarted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GamryWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GamryWidget::experimentComplited)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Gamry::GamryWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Gamry__GamryWidget.data,
      qt_meta_data_Gamry__GamryWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Gamry::GamryWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gamry::GamryWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Gamry__GamryWidget.stringdata0))
        return static_cast<void*>(const_cast< GamryWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Gamry::GamryWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Gamry::GamryWidget::polling()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Gamry::GamryWidget::detected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Gamry::GamryWidget::experimentStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Gamry::GamryWidget::experimentComplited()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
